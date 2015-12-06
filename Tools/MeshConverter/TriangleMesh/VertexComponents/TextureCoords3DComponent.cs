using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.TriangleMesh.VertexComponents
{
    public class TextureCoords3DComponent : IVertexComponent
    {
        public TextureCoords3DComponent()
        {
            m_data_[0] = 0.0f;
            m_data_[1] = 0.0f;
            m_data_[2] = 0.0f;
        }

        public TextureCoords3DComponent(float u, float v, float w)
        {
            m_data_[0] = u;
            m_data_[1] = v;
            m_data_[2] = w;
        }

        public TextureCoords3DComponent(float[] coords)
        {
            Debug.Assert(coords.Length == 3, "Length of coords must be 3");

            m_data_ = coords;
        }

        public float[] Value
        {
            get
            {
                return m_data_;
            }
            set
            {
                Debug.Assert(value.Length == 3, "Length of value must be 3");
                m_data_ = value;
            }
        }

        public void Export(IMeshExporter exporter, LayoutEntry entry)
        {
            exporter.ExportVertexComponent(m_data_, entry);
        }

        private float[] m_data_ = new float[3];
    }
}
