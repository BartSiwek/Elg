using System;
using System.Collections.Generic;
using System.Text;
using MeshConverter.TriangleMesh.VertexLayout;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.TriangleLayout;

namespace MeshConverter.TriangleMesh
{
    public class SubMesh
    {
        public SubMesh(int vetex_count, int triangle_count, int submesh_index,
                       TriangleIndexFormat default_format, TriangleIndexFormat[] possible_formats)
        {
            IsSelected = true;
            DefaultFormat = default_format;
            PossibleFormats = possible_formats;

            m_vertex_layout_entries_ = new List<LayoutEntry>();
            m_vertices_ = new Vertex[vetex_count];
            m_triangles_ = new Triangle[triangle_count];
            m_format_ = default_format;
            m_submesh_index_ = submesh_index;

            AddLayoutEntry(VertexComponentType.POSITION_COMPONENT, -1);
        }

        public bool IsSelected
        {
            get;
            set;
        }

        public string Label
        {
            get
            {
                return String.Format("Mesh #{0} (Vertices: {1} Faces: {2} Format: {3})", 
                                         m_submesh_index_, 
                                         m_vertices_.Length,
                                         m_triangles_.Length,
                                         m_format_);
            }
        }

        public LayoutEntry[] Entries
        {
            get
            {
                return m_vertex_layout_entries_.ToArray();
            }
        }

        public int EntryCount
        {
            get
            {
                return m_vertex_layout_entries_.Count;
            }
        }

        public TriangleIndexFormat Format
        {
            get
            {
                return m_format_;
            }
            set
            {
                if (Array.IndexOf<TriangleIndexFormat>(PossibleFormats, value) == -1)
                {
                    throw new ArgumentException("Invalid triangle index format", "value");
                }
                m_format_ = value;
            }
        }

        public TriangleIndexFormat DefaultFormat
        {
            get;
            private set;
        }

        public TriangleIndexFormat[] PossibleFormats
        {
            get;
            private set;
        }

        public Vertex[] Vertices
        {
            get
            {
                return m_vertices_;
            }
        }

        public Triangle[] Triangles
        {
            get
            {
                return m_triangles_;
            }
        }

        public void AddLayoutEntry(VertexComponentType type, int index)
        {
            m_vertex_layout_entries_.Add(LayoutEntryFactory.CreateLayoutEntry(this, type, index));
        }

        public void Export(IMeshExporter exporter)
        {
            exporter.BeginSubMeshExport();
            exporter.ExportLayout(m_vertex_layout_entries_);
            exporter.ExportTriangleFormat(m_format_, DefaultFormat);
            exporter.BeginVerticesExport();

            foreach (Vertex vertex in m_vertices_)
            {
                vertex.Export(exporter, m_vertex_layout_entries_);
            }

            exporter.EndVerticesExport();
            exporter.BeginTrianglesExport();

            foreach (Triangle triangle in m_triangles_)
            {
                triangle.Export(exporter);
            }

            exporter.EndTrianglesExport();
            exporter.EndSubMeshExport();
        }

        private List<LayoutEntry> m_vertex_layout_entries_;
        private Vertex[] m_vertices_;
        private Triangle[] m_triangles_;
        private TriangleIndexFormat m_format_;
        private int m_submesh_index_;
    }
}
