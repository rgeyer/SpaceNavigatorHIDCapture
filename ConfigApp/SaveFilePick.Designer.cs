namespace ConfigApp
{
    partial class SaveFilePick
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this._fileList = new System.Windows.Forms.ListView();
            this._whichLbl = new System.Windows.Forms.Label();
            this._cancelBtn = new System.Windows.Forms.Button();
            this._okBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _fileList
            // 
            this._fileList.CheckBoxes = true;
            this._fileList.Location = new System.Drawing.Point(12, 32);
            this._fileList.Name = "_fileList";
            this._fileList.Size = new System.Drawing.Size(268, 97);
            this._fileList.TabIndex = 0;
            this._fileList.UseCompatibleStateImageBehavior = false;
            this._fileList.View = System.Windows.Forms.View.List;
            // 
            // _whichLbl
            // 
            this._whichLbl.AutoSize = true;
            this._whichLbl.Location = new System.Drawing.Point(12, 9);
            this._whichLbl.Name = "_whichLbl";
            this._whichLbl.Size = new System.Drawing.Size(157, 13);
            this._whichLbl.TabIndex = 1;
            this._whichLbl.Text = "Which file do you wish to save?";
            // 
            // _cancelBtn
            // 
            this._cancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this._cancelBtn.Location = new System.Drawing.Point(205, 135);
            this._cancelBtn.Name = "_cancelBtn";
            this._cancelBtn.Size = new System.Drawing.Size(75, 23);
            this._cancelBtn.TabIndex = 2;
            this._cancelBtn.Text = "Cancel";
            this._cancelBtn.UseVisualStyleBackColor = true;
            // 
            // _okBtn
            // 
            this._okBtn.Location = new System.Drawing.Point(124, 135);
            this._okBtn.Name = "_okBtn";
            this._okBtn.Size = new System.Drawing.Size(75, 23);
            this._okBtn.TabIndex = 3;
            this._okBtn.Text = "Save File(s)";
            this._okBtn.UseVisualStyleBackColor = true;
            this._okBtn.Click += new System.EventHandler(this._okBtn_Click);
            // 
            // SaveFilePick
            // 
            this.AcceptButton = this._okBtn;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this._cancelBtn;
            this.ClientSize = new System.Drawing.Size(292, 179);
            this.Controls.Add(this._okBtn);
            this.Controls.Add(this._cancelBtn);
            this.Controls.Add(this._whichLbl);
            this.Controls.Add(this._fileList);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SaveFilePick";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Which file?";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView _fileList;
        private System.Windows.Forms.Label _whichLbl;
        private System.Windows.Forms.Button _cancelBtn;
        private System.Windows.Forms.Button _okBtn;
    }
}