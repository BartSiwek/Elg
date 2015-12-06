using System;
using System.Collections.Generic;
using System.Text;
using MeshConverter.Exporters;

namespace MeshConverter.TriangleMesh
{
    public class Mesh
    {
        public Mesh(SubMesh[] submeshes)
        {
            m_submeshes_ = submeshes;
        }

        public SubMesh[] SubMeshes
        {
            get
            {
                return m_submeshes_;
            }
        }

        public int SubMeshCount
        {
            get
            {
                return m_submeshes_.Length;
            }
        }

        public void Export(IMeshExporter exporter)
        {
            exporter.BeginMeshExport();

            foreach (SubMesh submesh in m_submeshes_)
            {
                if (submesh.IsSelected)
                {
                    submesh.Export(exporter);
                }
            }

            exporter.EndMeshExport();
        }

        //Implementation of Singleton pattern
        public static Mesh Instance
        {
            get
            {
                if (s_mesh_ == null)
                {
                    throw new InvalidOperationException("A mesh needs to be loaded before it is queried");
                }

                return s_mesh_;
            }
            set
            {
                s_mesh_ = value;
            }
        }

        // Data members [static]
        private static Mesh s_mesh_ = null;

        // Data members [instance]
        private SubMesh[] m_submeshes_;
    }
}
