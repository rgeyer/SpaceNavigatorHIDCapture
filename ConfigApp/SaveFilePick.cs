using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ConfigApp.Properties;

namespace ConfigApp
{
    public partial class SaveFilePick : Form
    {
        public SaveFilePick()
        {
            InitializeComponent();

            // Start TreeView Image List
            ImageList imageList = new ImageList();
            imageList.ColorDepth = ColorDepth.Depth32Bit;
            imageList.ImageSize = new Size(16, 16);
            imageList.TransparentColor = Color.Transparent;

            imageList.Images.Add(Resources.xml);

            _fileList.SmallImageList = imageList;
            _fileList.LargeImageList = imageList;
            // End TreeView Image List
        }

        public ICollection<String> FileList
        {
            set
            {
                foreach (String file in value)
                {
                    ListViewItem lvi = new ListViewItem(file, 0);
                    _fileList.Items.Add(lvi);
                }
            }
            get
            {
                List<String> retVal = new List<String>();
                foreach (int idx in _fileList.CheckedIndices)
                {
                    retVal.Add(_fileList.Items[idx].Text);
                }
                return retVal;
            }
        }

        private void _okBtn_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}