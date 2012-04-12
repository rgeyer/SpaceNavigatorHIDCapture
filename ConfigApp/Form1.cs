using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ConfigApp.Properties;
using System.Xml;
using System.Xml.Serialization;
using System.Reflection;
using System.Collections;

namespace ConfigApp
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();

            // Start TreeView Image List
            ImageList imageList = new ImageList();
            imageList.ColorDepth = ColorDepth.Depth32Bit;
            imageList.ImageSize = new Size(16, 16);
            imageList.TransparentColor = Color.Transparent;
            
            imageList.Images.Add(Resources.closed_folder);      //0
            imageList.Images.Add(Resources.open_folder);        //1
            imageList.Images.Add(Resources.xml);                //2
            imageList.Images.Add(Resources.hid);                //3
            imageList.Images.Add(Resources.mouse);              //4
            imageList.Images.Add(Resources.button);             //5
            imageList.Images.Add(Resources.cmd);                //6
            imageList.Images.Add(Resources.window);             //7
            imageList.Images.Add(Resources.window_message);     //8
            imageList.Images.Add(Resources.hidCommand);         //9
            imageList.Images.Add(Resources.axis);               //10

            _treeView.ImageList = imageList;
            // End TreeView Image List

            _treeView.Nodes[0].ImageIndex = 0;
            _treeView.Nodes[0].SelectedImageIndex = 1;
        }

        private void AddFileNode(string filename)
        {
            XmlDocument _xmlDoc = new XmlDocument();
            _xmlDoc.Load(filename);

            snConfig retVal = null;
            XmlSerializer serializer = new XmlSerializer(typeof(snConfig));
            StringReader stringReader = new StringReader(_xmlDoc.DocumentElement.OuterXml);
            XmlTextReader xmlReader = new XmlTextReader(stringReader);
            retVal = serializer.Deserialize(xmlReader) as snConfig;

            TreeNode nodeToAdd = new TreeNode(filename);
            nodeToAdd.ImageIndex = 2;
            nodeToAdd.SelectedImageIndex = 2;
            nodeToAdd.Tag = retVal;
            nodeToAdd.Name = retVal.GetType().Name;

            AddChildNodes(retVal, nodeToAdd);

            _treeView.Nodes[0].Nodes.Add(nodeToAdd);
            _treeView.Nodes[0].Expand();
        }

        private void RefreshTreeView(object sender, EventArgs e)
        {
            foreach (TreeNode file in _treeView.Nodes[0].Nodes)
            {
                file.Nodes.Clear();
                AddChildNodes(file.Tag, file);
            }
        }

        private void AddChildNodes(object parentObj, TreeNode parentNode)
        {
            MenuItem deleteItem = new MenuItem("Delete");
            deleteItem.Tag = parentNode;
            deleteItem.Click += new EventHandler(deleteItem_Click);

            // If the parent node has a name property, set the tree node to that name
            if (parentObj.GetType().GetProperty("name") != null)
                parentNode.Text = parentObj.GetType().InvokeMember("name", BindingFlags.GetProperty, null, parentObj, null) as String;

            // Lets check what type of object the parent is, and set it's icon appropriately
            Type parentObjType = parentObj.GetType();
            if (parentObjType == typeof(hidDevice))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 3;
            if (parentObjType == typeof(device))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 4;
            if (parentObjType == typeof(keyPress) || parentObjType == typeof(button))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 5;
            if (parentObjType == typeof(execute))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 6;
            if (parentObjType == typeof(sendCommandWindowMessage) || parentObjType == typeof(sendCopyDataWindowMessage))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 8;
            if (parentObjType == typeof(hidCommand))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 9;
            if (parentObjType == typeof(axe))
                parentNode.ImageIndex = parentNode.SelectedImageIndex = 10;

            foreach (PropertyInfo property in parentObj.GetType().GetProperties())
            {
                // Create a context menu!
                ContextMenu cMenu = new ContextMenu();
                MenuItem menuItem = new MenuItem("Add");

                Type propertyType = property.PropertyType;                

                ICollection<Type> custAttrs = new List<Type>();

                foreach (object custAttr in property.GetCustomAttributes(true))
                {
                    MenuItem newAddItem = new MenuItem();
                    if (custAttr is XmlElementAttribute)
                    {
                        newAddItem.Text = ((XmlElementAttribute)custAttr).Type.Name;
                        newAddItem.Tag = parentObj;
                        newAddItem.Name = property.Name;
                        newAddItem.Click += new EventHandler(newAddItem_Click);
                        menuItem.MenuItems.Add(newAddItem);
                    }
                    if (custAttr is XmlArrayItemAttribute)
                    {
                        newAddItem.Text = propertyType.GetGenericArguments()[0].Name;
                        newAddItem.Tag = parentObj;
                        newAddItem.Name = property.Name;
                        newAddItem.Click += new EventHandler(newAddItem_Click);
                        menuItem.MenuItems.Add(newAddItem);
                    }
                    custAttrs.Add(custAttr.GetType());
                }
                cMenu.MenuItems.Add(menuItem);
                if ((custAttrs.Contains(typeof(XmlElementAttribute))  && propertyType.IsArray) || custAttrs.Contains(typeof(XmlArrayItemAttribute)))
                {
                    TreeNode childNode = new TreeNode(property.Name);
                    childNode.Name = property.PropertyType.Name;
                    childNode.Tag = parentObj;
                    childNode.ContextMenu = cMenu;
                    IEnumerable childArray = parentObj.GetType().InvokeMember(property.Name, BindingFlags.GetProperty, null, parentObj, null) as IEnumerable;
                    if (childArray != null)
                    {
                        foreach (object childObj in childArray)
                        {
                            TreeNode tier2Child = new TreeNode(childObj.GetType().Name);
                            tier2Child.Name = childObj.GetType().Name;
                            tier2Child.Tag = childObj;
                            AddChildNodes(childObj, tier2Child);
                            childNode.Nodes.Add(tier2Child);
                        }
                    }
                    parentNode.Nodes.Add(childNode);
                    if (!childNode.IsExpanded)
                        childNode.Expand();
                    if (!parentNode.IsExpanded)
                        parentNode.Expand();
                }
                else if (propertyType.IsGenericType)
                {
                    if (parentNode.ContextMenu == null)
                        parentNode.ContextMenu = cMenu;
                    else if (parentNode.ContextMenu != cMenu)
                        parentNode.ContextMenu.MenuItems[0].MergeMenu(cMenu.MenuItems[0]);
                    IEnumerable childArray = parentObj.GetType().InvokeMember(property.Name, BindingFlags.GetProperty, null, parentObj, null) as IEnumerable;
                    if (childArray != null)
                    {
                        foreach (object childObj in childArray)
                        {
                            TreeNode tier2Child = new TreeNode(childObj.GetType().Name);
                            tier2Child.Name = childObj.GetType().Name;
                            tier2Child.Tag = childObj;
                            AddChildNodes(childObj, tier2Child);
                            parentNode.Nodes.Add(tier2Child);
                        }
                    }
                    if (!parentNode.IsExpanded)
                        parentNode.Expand();
                }
                else if (custAttrs.Contains(typeof(XmlElementAttribute)) && !propertyType.IsArray)
                {
                    // This doesn't seem to ever get hit
                    TreeNode childNode = new TreeNode(property.Name);
                    childNode.Name = property.PropertyType.Name;
                    childNode.ContextMenu = cMenu;
                    object childObj = parentObj.GetType().InvokeMember(property.Name, BindingFlags.GetProperty, null, parentObj, null);
                    childNode.Tag = childObj;
                    AddChildNodes(childObj, childNode);
                    parentNode.Nodes.Add(childNode);
                    if (!childNode.IsExpanded)
                        childNode.Expand();
                    if (!parentNode.IsExpanded)
                        parentNode.Expand();
                }
                else if (!custAttrs.Contains(typeof(XmlAttributeAttribute)) && !custAttrs.Contains(typeof(XmlIgnoreAttribute)))
                {
                    TreeNode childNode = new TreeNode(property.Name);
                    childNode.ContextMenu = cMenu;
                    object childObj = parentObj.GetType().InvokeMember(property.Name, BindingFlags.GetProperty, null, parentObj, null);
                    childNode.Name = childObj.GetType().Name;
                    childNode.Tag = childObj;
                    AddChildNodes(childObj, childNode);
                    parentNode.Nodes.Add(childNode);
                    if (!childNode.IsExpanded)
                        childNode.Expand();
                    if (!parentNode.IsExpanded)
                        parentNode.Expand();
                }
            }
            if(parentNode.ContextMenu == null)
                parentNode.ContextMenu = new ContextMenu();
            parentNode.ContextMenu.MenuItems.Add(deleteItem);
        }

        void deleteItem_Click(object sender, EventArgs e)
        {
            MenuItem item = sender as MenuItem;
            if (item != null)
            {
                String propertyName = String.Empty;
                TreeNode selNode = item.Tag as TreeNode;
                object parentObject = selNode.Parent.Tag;                
                object childObject = selNode.Tag;
                foreach (PropertyInfo info in parentObject.GetType().GetProperties())
                {
                    foreach (Type typ in info.PropertyType.GetGenericArguments())
                    {
                        if (typ == childObject.GetType() || typ == childObject.GetType().BaseType)
                        {
                            System.Diagnostics.Trace.WriteLine(String.Format("Child object matches property {0} type is {1}", info.Name, typ.ToString()));
                            propertyName = info.Name;
                        }
                    }
                }
                if (parentObject != null && parentObject.GetType().GetProperty(propertyName) != null)
                {
                    object propertyObject = parentObject.GetType().InvokeMember(propertyName, BindingFlags.GetProperty, null, parentObject, null);
                    propertyObject.GetType().InvokeMember("Remove", BindingFlags.InvokeMethod, null, propertyObject, new object[] { childObject });
                    RefreshTreeView(sender, e);
                }
            }
        }

        private void newAddItem_Click(object sender, EventArgs e)
        {
            MenuItem item = sender as MenuItem;
            if (item != null)
            {
                object newObj = Activator.CreateInstance(Type.GetType(item.Text));
                object parentObject = item.Tag;
                object propertyObject = parentObject.GetType().InvokeMember(item.Name, BindingFlags.GetProperty, null, parentObject, null);
                propertyObject.GetType().InvokeMember("Add", BindingFlags.InvokeMethod, null, propertyObject, new object[] { newObj });
                RefreshTreeView(this, new EventArgs());
            }
        }

        private void newDevice_Click(object sender, EventArgs e)
        {
            if (sender is MenuItem && ((MenuItem)sender).Tag is TreeNode)
            {
                TreeNode parentNode = ((MenuItem)sender).Tag as TreeNode;
                TreeNode nodeToAdd = new TreeNode();
                XmlNode xmlNode = ((XmlNode)parentNode.Tag).OwnerDocument.CreateElement("device");                
                xmlNode.Attributes.Append(xmlNode.OwnerDocument.CreateAttribute("type"));
                xmlNode.Attributes["type"].InnerText = ((MenuItem)sender).Text;
                parentNode.Nodes.Add(nodeToAdd);
                if (!parentNode.IsExpanded)
                    parentNode.Expand();
                _treeView.Refresh();
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".xml";
            dlg.Filter = "XML Configuration File|*.xml";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                AddFileNode(dlg.FileName);
            }
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.DefaultExt = ".xml";
            dlg.Filter = "XML Configuration File|*.xml";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(dlg.FileName, Resources.config);
                AddFileNode(dlg.FileName);
            }
        }

        private void _treeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Tag is XmlNode || e.Node.Tag == null)
                _propertyGrid.SelectedObject = null;
            else if (e.Node.Tag != null && e.Node.Name == e.Node.Tag.GetType().Name)
                _propertyGrid.SelectedObject = e.Node.Tag;
            else
                _propertyGrid.SelectedObject = null;

            TreeNode parentNode = _treeView.SelectedNode;
            if (parentNode.Tag == null)
                return;
            Type parentTagType = parentNode.Tag.GetType();

            while (parentTagType != typeof(snConfig) && parentNode.Parent != null)
            {
                parentNode = parentNode.Parent;
                if(parentNode.Tag != null)
                    parentTagType = parentNode.Tag.GetType();
            }

            _propertyGrid.Tag = parentNode.Tag;

        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<String> fileNames = new List<String>();
            foreach (TreeNode file in _treeView.Nodes[0].Nodes)
            {
                fileNames.Add(file.Text);
            }

            SaveFilePick dlg = new SaveFilePick();
            dlg.FileList = fileNames;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                foreach (TreeNode file in _treeView.Nodes[0].Nodes)
                {
                    if (dlg.FileList.Contains(file.Text))
                    {
                        string retVal = string.Empty;
                        TextWriter writer = new StringWriter();
                        XmlSerializer serializer = new XmlSerializer(file.Tag.GetType());
                        serializer.Serialize(writer, file.Tag);
                        File.WriteAllText(file.Text, writer.ToString(), Encoding.Unicode);
                    }
                }
            }
        }

        private void _propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            RefreshTreeView(this, new EventArgs());
        }
    }
}