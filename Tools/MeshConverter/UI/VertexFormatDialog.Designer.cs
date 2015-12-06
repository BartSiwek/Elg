namespace MeshConverter.UI
{
    partial class VertexFormatDialog
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
            this.m_format_label_ = new System.Windows.Forms.Label();
            this.m_format_combobox_ = new System.Windows.Forms.ComboBox();
            this.m_ok_button_ = new System.Windows.Forms.Button();
            this.m_cancel_button_ = new System.Windows.Forms.Button();
            this.helpProvider1 = new System.Windows.Forms.HelpProvider();
            this.m_semantic_name_label_ = new System.Windows.Forms.Label();
            this.m_semantic_index_label_ = new System.Windows.Forms.Label();
            this.m_semantic_name_text_box_ = new System.Windows.Forms.TextBox();
            this.m_semantic_index_numeric_up_down_ = new System.Windows.Forms.NumericUpDown();
            this.m_defaults_button_ = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.m_semantic_index_numeric_up_down_)).BeginInit();
            this.SuspendLayout();
            // 
            // m_format_label_
            // 
            this.m_format_label_.AutoSize = true;
            this.m_format_label_.Location = new System.Drawing.Point(12, 61);
            this.m_format_label_.Name = "m_format_label_";
            this.m_format_label_.Size = new System.Drawing.Size(42, 13);
            this.m_format_label_.TabIndex = 0;
            this.m_format_label_.Text = "Format:";
            // 
            // m_format_combobox_
            // 
            this.m_format_combobox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_format_combobox_.FormattingEnabled = true;
            this.m_format_combobox_.Location = new System.Drawing.Point(60, 58);
            this.m_format_combobox_.Name = "m_format_combobox_";
            this.m_format_combobox_.Size = new System.Drawing.Size(212, 21);
            this.m_format_combobox_.TabIndex = 1;
            // 
            // m_ok_button_
            // 
            this.m_ok_button_.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.m_ok_button_.Location = new System.Drawing.Point(18, 85);
            this.m_ok_button_.Name = "m_ok_button_";
            this.m_ok_button_.Size = new System.Drawing.Size(75, 23);
            this.m_ok_button_.TabIndex = 2;
            this.m_ok_button_.Text = "OK";
            this.m_ok_button_.UseVisualStyleBackColor = true;
            // 
            // m_cancel_button_
            // 
            this.m_cancel_button_.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.m_cancel_button_.Location = new System.Drawing.Point(105, 85);
            this.m_cancel_button_.Name = "m_cancel_button_";
            this.m_cancel_button_.Size = new System.Drawing.Size(75, 23);
            this.m_cancel_button_.TabIndex = 3;
            this.m_cancel_button_.Text = "Cancel";
            this.m_cancel_button_.UseVisualStyleBackColor = true;
            // 
            // m_semantic_name_label_
            // 
            this.m_semantic_name_label_.AutoSize = true;
            this.m_semantic_name_label_.Location = new System.Drawing.Point(12, 9);
            this.m_semantic_name_label_.Name = "m_semantic_name_label_";
            this.m_semantic_name_label_.Size = new System.Drawing.Size(83, 13);
            this.m_semantic_name_label_.TabIndex = 4;
            this.m_semantic_name_label_.Text = "Semantic name:";
            // 
            // m_semantic_index_label_
            // 
            this.m_semantic_index_label_.AutoSize = true;
            this.m_semantic_index_label_.Location = new System.Drawing.Point(12, 34);
            this.m_semantic_index_label_.Name = "m_semantic_index_label_";
            this.m_semantic_index_label_.Size = new System.Drawing.Size(82, 13);
            this.m_semantic_index_label_.TabIndex = 5;
            this.m_semantic_index_label_.Text = "Semantic index:";
            // 
            // m_semantic_name_text_box_
            // 
            this.m_semantic_name_text_box_.Location = new System.Drawing.Point(101, 6);
            this.m_semantic_name_text_box_.Name = "m_semantic_name_text_box_";
            this.m_semantic_name_text_box_.Size = new System.Drawing.Size(171, 20);
            this.m_semantic_name_text_box_.TabIndex = 6;
            // 
            // m_semantic_index_numeric_up_down_
            // 
            this.m_semantic_index_numeric_up_down_.Location = new System.Drawing.Point(197, 32);
            this.m_semantic_index_numeric_up_down_.Name = "m_semantic_index_numeric_up_down_";
            this.m_semantic_index_numeric_up_down_.Size = new System.Drawing.Size(75, 20);
            this.m_semantic_index_numeric_up_down_.TabIndex = 7;
            // 
            // m_defaults_button_
            // 
            this.m_defaults_button_.Location = new System.Drawing.Point(192, 85);
            this.m_defaults_button_.Name = "m_defaults_button_";
            this.m_defaults_button_.Size = new System.Drawing.Size(75, 23);
            this.m_defaults_button_.TabIndex = 8;
            this.m_defaults_button_.Text = "Default";
            this.m_defaults_button_.UseVisualStyleBackColor = true;
            this.m_defaults_button_.Click += new System.EventHandler(this.m_defaults_button__Click);
            // 
            // FormatSelectionDialog
            // 
            this.AcceptButton = this.m_ok_button_;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.m_cancel_button_;
            this.ClientSize = new System.Drawing.Size(284, 115);
            this.Controls.Add(this.m_defaults_button_);
            this.Controls.Add(this.m_semantic_index_numeric_up_down_);
            this.Controls.Add(this.m_semantic_name_text_box_);
            this.Controls.Add(this.m_semantic_index_label_);
            this.Controls.Add(this.m_semantic_name_label_);
            this.Controls.Add(this.m_cancel_button_);
            this.Controls.Add(this.m_ok_button_);
            this.Controls.Add(this.m_format_combobox_);
            this.Controls.Add(this.m_format_label_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormatSelectionDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Select format";
            ((System.ComponentModel.ISupportInitialize)(this.m_semantic_index_numeric_up_down_)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_format_label_;
        private System.Windows.Forms.ComboBox m_format_combobox_;
        private System.Windows.Forms.Button m_ok_button_;
        private System.Windows.Forms.Button m_cancel_button_;
        private System.Windows.Forms.HelpProvider helpProvider1;
        private System.Windows.Forms.Label m_semantic_name_label_;
        private System.Windows.Forms.Label m_semantic_index_label_;
        private System.Windows.Forms.TextBox m_semantic_name_text_box_;
        private System.Windows.Forms.NumericUpDown m_semantic_index_numeric_up_down_;
        private System.Windows.Forms.Button m_defaults_button_;
    }
}