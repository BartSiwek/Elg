namespace MeshConverter.UI
{
    partial class MainForm
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
            this.components = new System.ComponentModel.Container();
            this.m_menu_strip_ = new System.Windows.Forms.MenuStrip();
            this.m_file_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_open_mesh_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_export_mesh_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_tool_strip_menu_item_separator_ = new System.Windows.Forms.ToolStripSeparator();
            this.m_exit_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_open_mesh_dialog_ = new System.Windows.Forms.OpenFileDialog();
            this.m_postprocess_group_box_ = new System.Windows.Forms.GroupBox();
            this.m_postprocess_checked_list_box_ = new System.Windows.Forms.CheckedListBox();
            this.m_reload_button_ = new System.Windows.Forms.Button();
            this.m_log_text_box_ = new System.Windows.Forms.RichTextBox();
            this.m_node_tree_menu_strip_ = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.m_select_all_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_deselect_all_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_node_tree_tool_strip_menu_item_separator_ = new System.Windows.Forms.ToolStripSeparator();
            this.m_expand_all_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_collapse_all_tool_strip_menu_item_ = new System.Windows.Forms.ToolStripMenuItem();
            this.m_export_mesh_dialog_ = new System.Windows.Forms.SaveFileDialog();
            this.m_node_tree_view_ = new Aga.Controls.Tree.TreeViewAdv();
            this.m_node_tree_view_check_box_ = new Aga.Controls.Tree.NodeControls.NodeCheckBox();
            this.m_node_tree_view_text_box_ = new Aga.Controls.Tree.NodeControls.NodeTextBox();
            this.m_menu_strip_.SuspendLayout();
            this.m_postprocess_group_box_.SuspendLayout();
            this.m_node_tree_menu_strip_.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_menu_strip_
            // 
            this.m_menu_strip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.m_file_tool_strip_menu_item_});
            this.m_menu_strip_.Location = new System.Drawing.Point(0, 0);
            this.m_menu_strip_.Name = "m_menu_strip_";
            this.m_menu_strip_.Size = new System.Drawing.Size(784, 24);
            this.m_menu_strip_.TabIndex = 0;
            this.m_menu_strip_.Text = "MenuStrip";
            // 
            // m_file_tool_strip_menu_item_
            // 
            this.m_file_tool_strip_menu_item_.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.m_open_mesh_tool_strip_menu_item_,
            this.m_export_mesh_tool_strip_menu_item_,
            this.m_tool_strip_menu_item_separator_,
            this.m_exit_tool_strip_menu_item_});
            this.m_file_tool_strip_menu_item_.Name = "m_file_tool_strip_menu_item_";
            this.m_file_tool_strip_menu_item_.Size = new System.Drawing.Size(37, 20);
            this.m_file_tool_strip_menu_item_.Text = "&File";
            // 
            // m_open_mesh_tool_strip_menu_item_
            // 
            this.m_open_mesh_tool_strip_menu_item_.Name = "m_open_mesh_tool_strip_menu_item_";
            this.m_open_mesh_tool_strip_menu_item_.Size = new System.Drawing.Size(139, 22);
            this.m_open_mesh_tool_strip_menu_item_.Text = "&Open Mesh";
            this.m_open_mesh_tool_strip_menu_item_.Click += new System.EventHandler(this.m_open_mesh_tool_strip_menu_item__Click);
            // 
            // m_export_mesh_tool_strip_menu_item_
            // 
            this.m_export_mesh_tool_strip_menu_item_.Name = "m_export_mesh_tool_strip_menu_item_";
            this.m_export_mesh_tool_strip_menu_item_.Size = new System.Drawing.Size(139, 22);
            this.m_export_mesh_tool_strip_menu_item_.Text = "&Export Mesh";
            this.m_export_mesh_tool_strip_menu_item_.Click += new System.EventHandler(this.m_export_mesh_tool_strip_menu_item__Click);
            // 
            // m_tool_strip_menu_item_separator_
            // 
            this.m_tool_strip_menu_item_separator_.Name = "m_tool_strip_menu_item_separator_";
            this.m_tool_strip_menu_item_separator_.Size = new System.Drawing.Size(136, 6);
            // 
            // m_exit_tool_strip_menu_item_
            // 
            this.m_exit_tool_strip_menu_item_.Name = "m_exit_tool_strip_menu_item_";
            this.m_exit_tool_strip_menu_item_.Size = new System.Drawing.Size(139, 22);
            this.m_exit_tool_strip_menu_item_.Text = "&Exit";
            this.m_exit_tool_strip_menu_item_.Click += new System.EventHandler(this.m_exit_tool_strip_menu_item__Click);
            // 
            // m_open_mesh_dialog_
            // 
            this.m_open_mesh_dialog_.Filter = "All files|*.*";
            this.m_open_mesh_dialog_.Title = "Choose a mesh to open";
            // 
            // m_postprocess_group_box_
            // 
            this.m_postprocess_group_box_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.m_postprocess_group_box_.Controls.Add(this.m_postprocess_checked_list_box_);
            this.m_postprocess_group_box_.Controls.Add(this.m_reload_button_);
            this.m_postprocess_group_box_.Location = new System.Drawing.Point(12, 27);
            this.m_postprocess_group_box_.Name = "m_postprocess_group_box_";
            this.m_postprocess_group_box_.Size = new System.Drawing.Size(190, 523);
            this.m_postprocess_group_box_.TabIndex = 2;
            this.m_postprocess_group_box_.TabStop = false;
            this.m_postprocess_group_box_.Text = "Post-processing";
            // 
            // m_postprocess_checked_list_box_
            // 
            this.m_postprocess_checked_list_box_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.m_postprocess_checked_list_box_.FormattingEnabled = true;
            this.m_postprocess_checked_list_box_.Location = new System.Drawing.Point(6, 19);
            this.m_postprocess_checked_list_box_.Name = "m_postprocess_checked_list_box_";
            this.m_postprocess_checked_list_box_.Size = new System.Drawing.Size(178, 469);
            this.m_postprocess_checked_list_box_.TabIndex = 1;
            // 
            // m_reload_button_
            // 
            this.m_reload_button_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.m_reload_button_.Enabled = false;
            this.m_reload_button_.Location = new System.Drawing.Point(6, 494);
            this.m_reload_button_.Name = "m_reload_button_";
            this.m_reload_button_.Size = new System.Drawing.Size(75, 23);
            this.m_reload_button_.TabIndex = 0;
            this.m_reload_button_.Text = "Reload";
            this.m_reload_button_.UseVisualStyleBackColor = true;
            this.m_reload_button_.Click += new System.EventHandler(this.m_reload_button__Click);
            // 
            // m_log_text_box_
            // 
            this.m_log_text_box_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_log_text_box_.Location = new System.Drawing.Point(208, 390);
            this.m_log_text_box_.Name = "m_log_text_box_";
            this.m_log_text_box_.Size = new System.Drawing.Size(564, 160);
            this.m_log_text_box_.TabIndex = 3;
            this.m_log_text_box_.Text = "";
            // 
            // m_node_tree_menu_strip_
            // 
            this.m_node_tree_menu_strip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.m_select_all_tool_strip_menu_item_,
            this.m_deselect_all_tool_strip_menu_item_,
            this.m_node_tree_tool_strip_menu_item_separator_,
            this.m_expand_all_tool_strip_menu_item_,
            this.m_collapse_all_tool_strip_menu_item_});
            this.m_node_tree_menu_strip_.Name = "m_node_tree_menu_strip_";
            this.m_node_tree_menu_strip_.Size = new System.Drawing.Size(153, 120);
            // 
            // m_select_all_tool_strip_menu_item_
            // 
            this.m_select_all_tool_strip_menu_item_.Name = "m_select_all_tool_strip_menu_item_";
            this.m_select_all_tool_strip_menu_item_.Size = new System.Drawing.Size(152, 22);
            this.m_select_all_tool_strip_menu_item_.Text = "Select &All";
            this.m_select_all_tool_strip_menu_item_.Click += new System.EventHandler(this.m_select_all_tool_strip_menu_item__Click);
            // 
            // m_deselect_all_tool_strip_menu_item_
            // 
            this.m_deselect_all_tool_strip_menu_item_.Name = "m_deselect_all_tool_strip_menu_item_";
            this.m_deselect_all_tool_strip_menu_item_.Size = new System.Drawing.Size(152, 22);
            this.m_deselect_all_tool_strip_menu_item_.Text = "Deselect All";
            this.m_deselect_all_tool_strip_menu_item_.Click += new System.EventHandler(this.m_deselect_all_tool_strip_menu_item__Click);
            // 
            // m_node_tree_tool_strip_menu_item_separator_
            // 
            this.m_node_tree_tool_strip_menu_item_separator_.Name = "m_node_tree_tool_strip_menu_item_separator_";
            this.m_node_tree_tool_strip_menu_item_separator_.Size = new System.Drawing.Size(149, 6);
            // 
            // m_expand_all_tool_strip_menu_item_
            // 
            this.m_expand_all_tool_strip_menu_item_.Name = "m_expand_all_tool_strip_menu_item_";
            this.m_expand_all_tool_strip_menu_item_.Size = new System.Drawing.Size(152, 22);
            this.m_expand_all_tool_strip_menu_item_.Text = "Expand All";
            this.m_expand_all_tool_strip_menu_item_.Click += new System.EventHandler(this.m_expand_all_tool_strip_menu_item__Click);
            // 
            // m_collapse_all_tool_strip_menu_item_
            // 
            this.m_collapse_all_tool_strip_menu_item_.Name = "m_collapse_all_tool_strip_menu_item_";
            this.m_collapse_all_tool_strip_menu_item_.Size = new System.Drawing.Size(152, 22);
            this.m_collapse_all_tool_strip_menu_item_.Text = "CollapseAll";
            this.m_collapse_all_tool_strip_menu_item_.Click += new System.EventHandler(this.m_collapse_all_tool_strip_menu_item__Click);
            // 
            // m_export_mesh_dialog_
            // 
            this.m_export_mesh_dialog_.DefaultExt = "tem";
            this.m_export_mesh_dialog_.Filter = "Text ELG Mesh|*.tem|All files|*.*";
            this.m_export_mesh_dialog_.Title = "Choose a file name for exported mesh";
            // 
            // m_node_tree_view_
            // 
            this.m_node_tree_view_.BackColor = System.Drawing.SystemColors.Window;
            this.m_node_tree_view_.ContextMenuStrip = this.m_node_tree_menu_strip_;
            this.m_node_tree_view_.DefaultToolTipProvider = null;
            this.m_node_tree_view_.DragDropMarkColor = System.Drawing.Color.Black;
            this.m_node_tree_view_.LineColor = System.Drawing.SystemColors.ControlDark;
            this.m_node_tree_view_.Location = new System.Drawing.Point(208, 27);
            this.m_node_tree_view_.Model = null;
            this.m_node_tree_view_.Name = "m_node_tree_view_";
            this.m_node_tree_view_.NodeControls.Add(this.m_node_tree_view_check_box_);
            this.m_node_tree_view_.NodeControls.Add(this.m_node_tree_view_text_box_);
            this.m_node_tree_view_.SelectedNode = null;
            this.m_node_tree_view_.Size = new System.Drawing.Size(564, 357);
            this.m_node_tree_view_.TabIndex = 5;
            this.m_node_tree_view_.Text = "Nodes tree view";
            this.m_node_tree_view_.NodeMouseDoubleClick += new System.EventHandler<Aga.Controls.Tree.TreeNodeAdvMouseEventArgs>(this.m_node_tree_view__NodeMouseDoubleClick);
            // 
            // m_node_tree_view_check_box_
            // 
            this.m_node_tree_view_check_box_.DataPropertyName = "IsSelected";
            this.m_node_tree_view_check_box_.EditEnabled = true;
            this.m_node_tree_view_check_box_.LeftMargin = 0;
            this.m_node_tree_view_check_box_.ParentColumn = null;
            // 
            // m_node_tree_view_text_box_
            // 
            this.m_node_tree_view_text_box_.DataPropertyName = "Label";
            this.m_node_tree_view_text_box_.IncrementalSearchEnabled = true;
            this.m_node_tree_view_text_box_.LeftMargin = 3;
            this.m_node_tree_view_text_box_.ParentColumn = null;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 562);
            this.Controls.Add(this.m_node_tree_view_);
            this.Controls.Add(this.m_log_text_box_);
            this.Controls.Add(this.m_postprocess_group_box_);
            this.Controls.Add(this.m_menu_strip_);
            this.MainMenuStrip = this.m_menu_strip_;
            this.Name = "MainForm";
            this.Text = "MeshConverter";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.m_menu_strip_.ResumeLayout(false);
            this.m_menu_strip_.PerformLayout();
            this.m_postprocess_group_box_.ResumeLayout(false);
            this.m_node_tree_menu_strip_.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip m_menu_strip_;
        private System.Windows.Forms.ToolStripMenuItem m_file_tool_strip_menu_item_;
        private System.Windows.Forms.ToolStripMenuItem m_open_mesh_tool_strip_menu_item_;
        private System.Windows.Forms.ToolStripSeparator m_tool_strip_menu_item_separator_;
        private System.Windows.Forms.ToolStripMenuItem m_exit_tool_strip_menu_item_;
        private System.Windows.Forms.OpenFileDialog m_open_mesh_dialog_;
        private System.Windows.Forms.GroupBox m_postprocess_group_box_;
        private System.Windows.Forms.Button m_reload_button_;
        private System.Windows.Forms.CheckedListBox m_postprocess_checked_list_box_;
        private System.Windows.Forms.RichTextBox m_log_text_box_;
        private System.Windows.Forms.ToolStripMenuItem m_export_mesh_tool_strip_menu_item_;
        private System.Windows.Forms.SaveFileDialog m_export_mesh_dialog_;
        private System.Windows.Forms.ContextMenuStrip m_node_tree_menu_strip_;
        private System.Windows.Forms.ToolStripMenuItem m_select_all_tool_strip_menu_item_;
        private System.Windows.Forms.ToolStripMenuItem m_deselect_all_tool_strip_menu_item_;
        private Aga.Controls.Tree.TreeViewAdv m_node_tree_view_;
        private Aga.Controls.Tree.NodeControls.NodeCheckBox m_node_tree_view_check_box_;
        private Aga.Controls.Tree.NodeControls.NodeTextBox m_node_tree_view_text_box_;
        private System.Windows.Forms.ToolStripSeparator m_node_tree_tool_strip_menu_item_separator_;
        private System.Windows.Forms.ToolStripMenuItem m_expand_all_tool_strip_menu_item_;
        private System.Windows.Forms.ToolStripMenuItem m_collapse_all_tool_strip_menu_item_;
    }
}

