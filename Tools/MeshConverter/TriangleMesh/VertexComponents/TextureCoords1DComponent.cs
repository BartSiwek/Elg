using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.TriangleMesh.VertexComponents
{
    public class TextureCoords1DComponent : IVertexComponent
    {
        public TextureCoords1DComponent()
        {
            m_data_[0] = 0.0f;
        }

        public TextureCoords1DComponent(float u)
        {
            m_data_[0] = u;
        }

        public TextureCoords1DComponent(float[] coords)
        {
            Debug.Assert(coords.Length == 1, "Length of coords must be 1");

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
                Debug.Assert(value.Length == 1, "Length of value must be 1");
                m_data_ = value;
            }
        }

        public void Export(IMeshExporter exporter, LayoutEntry entry)
        {
            exporter.ExportVertexComponent(m_data_, entry);
        }

        private float[] m_data_ = new float[1];
    }
}
