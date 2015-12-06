using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.Diagnostics;
using Aga.Controls.Tree;
using MeshConverter.TriangleMesh;
using MeshConverter.TriangleMesh.VertexLayout;
using MeshConverter.Exporters;

namespace MeshConverter.UI
{
    public partial class MainForm : Form
    {
        // Constructor
        public MainForm()
        {
            // Call the designer part
            InitializeComponent();

            // Create tree model
            m_node_tree_model_ = new NodeTreeModel();
            m_node_tree_view_.Model = m_node_tree_model_;

            // Add some handlers
            m_node_tree_view_check_box_.CheckStateChanged += 
                new EventHandler<TreePathEventArgs>(m_node_tree_view_check_box__CheckStateChanged);

            // Create a selection dialogs for later
            m_vertex_format_dialog_ = new VertexFormatDialog();
            m_triangle_format_dialog_ = new TriangleFormatDialog();

            // Fill the postprocessing checkbox list
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.CalculateTangentSpace, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.JoinIdenticalVertices, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.MakeLeftHanded, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.Triangulate, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.RemoveComponent, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.GenerateNormals, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.GenerateSmoothNormals, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.SplitLargeMeshes, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.PreTransformVertices, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.LimitBoneWeights, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.ValidateDataStructure, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.ImproveCacheLocality, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.RemoveRedundantMaterials, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.FixInFacingNormals, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.SortByPrimitiveType, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.FindDegenerates, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.FindInvalidData, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.GenerateUVCoords, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.TransformUVCoords, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.FindInstances, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.OptimizeMeshes, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.OptimizeGraph, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.FlipUVs, false);
            m_postprocess_checked_list_box_.Items.Add(Assimp.PostProcessSteps.FlipWindingOrder, false);
        }

        // Methods
        private Assimp.PostProcessSteps GetPosprocessingSteps()
        {
            Assimp.PostProcessSteps steps = Assimp.PostProcessSteps.None;
            foreach (Assimp.PostProcessSteps current_step in m_postprocess_checked_list_box_.CheckedItems)
            {
                steps |= current_step;
            }
            return steps;
        }

        private void BuildModelTreeView()
        {
            NodeTreeModel model = m_node_tree_view_.Model as NodeTreeModel;
            if (model != null)
            {
                model.CurrentMesh = Mesh.Instance;
            }
        }

        private void LoadMesh()
        {
            MeshImporter.Instance.OpenMesh(m_last_filename_, GetPosprocessingSteps(), LogCallback);
        }

        private void ExportMesh(string export_filename)
        {
            JsonExporter exporter = new JsonExporter(export_filename, LogCallback);
            Mesh.Instance.Export(exporter);
        }

        private void UpdateCheckOfParentNodes(TreeNode node)
        {
            TreeNode parent = node.Parent;
            while (parent != null)
            {
                if (node.Checked)
                {
                    parent.Checked = true;
                }
                node = parent;
                parent = node.Parent;
            }
        }

        private void UpdateCheckOfAllChildNodes(TreeNode node)
        {
            Queue<TreeNode> q = new Queue<TreeNode>();

            foreach (TreeNode child_node in node.Nodes)
            {
                q.Enqueue(child_node);
            }

            while (q.Count > 0)
            {
                TreeNode current_node = q.Dequeue();
                current_node.Checked = node.Checked;
                foreach (TreeNode child_node in current_node.Nodes)
                {
                    q.Enqueue(child_node);
                }
            }
        }

        private string GetLastDirectory()
        {
            if (m_last_filename_ != null)
            {
                return Path.GetDirectoryName(m_last_filename_);
            }
            else
            {
                return Environment.CurrentDirectory;
            }
        }

        private bool IsMeshOpen()
        {
            return (m_last_filename_ != null);
        }

        // Callbacks
        private void LogCallback(string msg)
        {
            m_log_text_box_.AppendText(String.Format("{0}, {1}", DateTime.Now.ToLongTimeString(), msg));
            m_log_text_box_.SelectionStart = m_log_text_box_.Text.Length - 1;
            m_log_text_box_.ScrollToCaret(); 
        }

        // Handlers
        private void m_open_mesh_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            m_open_mesh_dialog_.InitialDirectory = GetLastDirectory();
            if (m_open_mesh_dialog_.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {   
                m_last_filename_ = m_open_mesh_dialog_.FileName;
                LoadMesh();
                BuildModelTreeView();
                m_reload_button_.Enabled = true;
            }
        }

        private void m_export_mesh_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            if (IsMeshOpen())
            {
                m_export_mesh_dialog_.InitialDirectory = GetLastDirectory();
                if (m_export_mesh_dialog_.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    string export_filename = m_export_mesh_dialog_.FileName;
                    ExportMesh(export_filename);
                }
            }
        }

        private void m_reload_button__Click(object sender, EventArgs e)
        {
            if (m_last_filename_ != null)
            {
                LoadMesh();
                BuildModelTreeView();
            }
        }

        void m_node_tree_view_check_box__CheckStateChanged(object sender, TreePathEventArgs e)
        {
            NodeTreeModel model = m_node_tree_view_.Model as NodeTreeModel;
            if (model != null)
            {
                model.UpdateChecks(e.Path);
                m_node_tree_view_.Refresh();
            }
        }

        private void m_node_tree_view__NodeMouseDoubleClick(object sender, TreeNodeAdvMouseEventArgs e)
        {
            SubMesh submesh = e.Node.Tag as SubMesh;
            if (submesh != null)
            {
                bool expanded = e.Node.IsExpanded;

                m_triangle_format_dialog_.Formats = submesh.PossibleFormats;
                m_triangle_format_dialog_.DefaultFormat = submesh.DefaultFormat;
                m_triangle_format_dialog_.SelectedFormat = submesh.Format;

                if (m_triangle_format_dialog_.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    submesh.Format = m_triangle_format_dialog_.SelectedFormat;
                }

                m_node_tree_view_.Refresh();

                e.Handled = true;
            }

            LayoutEntry entry = e.Node.Tag as LayoutEntry;
            if (entry != null)
            {
                m_vertex_format_dialog_.SemanticName = entry.SemanticName;
                m_vertex_format_dialog_.SemanticIndex = entry.SemanticIndex;
                m_vertex_format_dialog_.Formats = entry.PossibleFormats;
                m_vertex_format_dialog_.DefaultFormat = entry.DefaultFormat;
                m_vertex_format_dialog_.SelectedFormat = entry.Format;

                if (m_vertex_format_dialog_.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    entry.SemanticName = m_vertex_format_dialog_.SemanticName;
                    entry.SemanticIndex = m_vertex_format_dialog_.SemanticIndex;
                    entry.Format = m_vertex_format_dialog_.SelectedFormat;
                }

                m_node_tree_view_.Refresh();

                e.Handled = true;
            }
        }

        private void m_select_all_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            NodeTreeModel model = m_node_tree_view_.Model as NodeTreeModel;
            if (model != null)
            {
                model.SetCheck(true);
                m_node_tree_view_.Refresh();
            }
        }

        private void m_deselect_all_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            NodeTreeModel model = m_node_tree_view_.Model as NodeTreeModel;
            if (model != null)
            {
                model.SetCheck(false);
                m_node_tree_view_.Refresh();
            }
        }

        private void m_expand_all_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            m_node_tree_view_.ExpandAll();
        }

        private void m_collapse_all_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            m_node_tree_view_.CollapseAll();
        }

        private void m_exit_tool_strip_menu_item__Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        // Member Data
        private NodeTreeModel m_node_tree_model_;
        private string m_last_filename_ = null;
        private VertexFormatDialog m_vertex_format_dialog_;
        private TriangleFormatDialog m_triangle_format_dialog_;
    }
}
