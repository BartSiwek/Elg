using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using MeshConverter.TriangleMesh.VertexLayout;
using MeshConverter.Exporters;

namespace MeshConverter.TriangleMesh.VertexComponents
{
    public class NormalComponent : IVertexComponent
    {
        public NormalComponent()
        {
            m_data_[0] = 0.0f;
            m_data_[1] = 0.0f;
            m_data_[2] = 0.0f;
        }

        public NormalComponent(float x, float y, float z)
        {
            m_data_[0] = x;
            m_data_[1] = y;
            m_data_[2] = z;
        }

        public NormalComponent(float[] coords)
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
