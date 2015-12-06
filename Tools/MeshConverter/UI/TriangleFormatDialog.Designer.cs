namespace MeshConverter.UI
{
    partial class TriangleFormatDialog
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
            this.m_ok_button_ = new System.Windows.Forms.Button();
            this.m_cancel_button_ = new System.Windows.Forms.Button();
            this.m_format_label_ = new System.Windows.Forms.Label();
            this.m_defaults_button_ = new System.Windows.Forms.Button();
            this.m_format_combobox_ = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // m_ok_button_
            // 
            this.m_ok_button_.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.m_ok_button_.Location = new System.Drawing.Point(8, 39);
            this.m_ok_button_.Name = "m_ok_button_";
            this.m_ok_button_.Size = new System.Drawing.Size(75, 23);
            this.m_ok_button_.TabIndex = 0;
            this.m_ok_button_.Text = "OK";
            this.m_ok_button_.UseVisualStyleBackColor = true;
            // 
            // m_cancel_button_
            // 
            this.m_cancel_button_.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.m_cancel_button_.Location = new System.Drawing.Point(105, 39);
            this.m_cancel_button_.Name = "m_cancel_button_";
            this.m_cancel_button_.Size = new System.Drawing.Size(75, 23);
            this.m_cancel_button_.TabIndex = 1;
            this.m_cancel_button_.Text = "Cancel";
            this.m_cancel_button_.UseVisualStyleBackColor = true;
            // 
            // m_format_label_
            // 
            this.m_format_label_.AutoSize = true;
            this.m_format_label_.Location = new System.Drawing.Point(12, 15);
            this.m_format_label_.Name = "m_format_label_";
            this.m_format_label_.Size = new System.Drawing.Size(42, 13);
            this.m_format_label_.TabIndex = 2;
            this.m_format_label_.Text = "Format:";
            // 
            // m_defaults_button_
            // 
            this.m_defaults_button_.Location = new System.Drawing.Point(202, 39);
            this.m_defaults_button_.Name = "m_defaults_button_";
            this.m_defaults_button_.Size = new System.Drawing.Size(75, 23);
            this.m_defaults_button_.TabIndex = 3;
            this.m_defaults_button_.Text = "Defaults";
            this.m_defaults_button_.UseVisualStyleBackColor = true;
            this.m_defaults_button_.Click += new System.EventHandler(this.m_defaults_button__Click);
            // 
            // m_format_combobox_
            // 
            this.m_format_combobox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_format_combobox_.FormattingEnabled = true;
            this.m_format_combobox_.Location = new System.Drawing.Point(60, 12);
            this.m_format_combobox_.Name = "m_format_combobox_";
            this.m_format_combobox_.Size = new System.Drawing.Size(212, 21);
            this.m_format_combobox_.TabIndex = 4;
            // 
            // TriangleFormatDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 73);
            this.Controls.Add(this.m_format_combobox_);
            this.Controls.Add(this.m_defaults_button_);
            this.Controls.Add(this.m_format_label_);
            this.Controls.Add(this.m_cancel_button_);
            this.Controls.Add(this.m_ok_button_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TriangleFormatDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Select format";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button m_ok_button_;
        private System.Windows.Forms.Button m_cancel_button_;
        private System.Windows.Forms.Label m_format_label_;
        private System.Windows.Forms.Button m_defaults_button_;
        private System.Windows.Forms.ComboBox m_format_combobox_;
    }
}