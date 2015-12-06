using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using Aga.Controls.Tree;
using MeshConverter.TriangleMesh;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.UI
{
    class NodeTreeModel : ITreeModel
    {
        public NodeTreeModel()
        {
        }

        public Mesh CurrentMesh
        {
            get
            {
                return m_mesh_;
            }
            set
            {
                m_mesh_ = value;
                NotifyStructureChanged(TreePath.Empty);
            }
        }   

        public IEnumerable GetChildren(TreePath tree_path)
        {
            if (m_mesh_ != null)
            {
                if (tree_path.IsEmpty())
                {
                    return m_mesh_.SubMeshes;
                }
                else
                {
                    SubMesh submesh_item = tree_path.LastNode as SubMesh;
                    if (submesh_item != null)
                    {
                        return submesh_item.Entries;
                    }
                    else
                    {
                        return null;
                    }
                }
            }
            else
            {
                return null;
            }
        }

        public bool IsLeaf(TreePath tree_path)
        {
            if (tree_path.LastNode is LayoutEntry)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void SetCheck(bool is_checked)
        {
            foreach (SubMesh submesh in m_mesh_.SubMeshes)
            {
                submesh.IsSelected = is_checked;

                foreach (LayoutEntry entry in submesh.Entries)
                {
                    entry.IsSelected = is_checked;
                }
            }
        }

        public void UpdateChecks(TreePath tree_path)
        {
            if (tree_path.LastNode is SubMesh)
            {
                SubMesh submesh = tree_path.LastNode as SubMesh;
                foreach (LayoutEntry entry in submesh.Entries)
                {
                    entry.IsSelected = submesh.IsSelected;
                }
            }
            else if (tree_path.LastNode is LayoutEntry)
            {
                LayoutEntry entry = tree_path.LastNode as LayoutEntry;
                if (entry.IsSelected)
                {
                    // We checked a node - make usre parent is checked as well
                    entry.Parent.IsSelected = true;
                }
                else
                {
                    // We unchecked a node - check if all are uncheked and adjust parent
                    bool all_unchecked = true;
                    foreach (LayoutEntry parent_entry in entry.Parent.Entries)
                    {
                        if (parent_entry.IsSelected)
                        {
                            all_unchecked = false;
                            break;
                        }
                    }

                    if (all_unchecked)
                    {
                        entry.Parent.IsSelected = false;
                    }
                }
            }
        }

        public event EventHandler<TreeModelEventArgs> NodesChanged;
        public event EventHandler<TreeModelEventArgs> NodesInserted;
        public event EventHandler<TreeModelEventArgs> NodesRemoved;
        public event EventHandler<TreePathEventArgs> StructureChanged;

        private void NotifyNodesChanged(TreePath parent, object[] children)
        {
            if (NodesChanged != null)
            {
                NodesChanged(this, new TreeModelEventArgs(parent, children));
            }
        }

        private void NotifyNodesInserted(TreePath parent, object[] children)
        {
            if (NodesInserted != null)
            {
                NodesInserted(this, new TreeModelEventArgs(parent, children));
            }
        }

        private void NotifyNodesRemoved(TreePath parent, object[] children)
        {
            if(NodesRemoved != null)
            {
                NodesInserted(this, new TreeModelEventArgs(parent, children));
            }
        }

        private void NotifyStructureChanged()
        {
            if (StructureChanged != null)
            {
                StructureChanged(this, new TreePathEventArgs());
            }
        }

        private void NotifyStructureChanged(TreePath path)
        {
            if (StructureChanged != null)
            {
                StructureChanged(this, new TreePathEventArgs(path));
            }
        }

        private Mesh m_mesh_;
    }
}
