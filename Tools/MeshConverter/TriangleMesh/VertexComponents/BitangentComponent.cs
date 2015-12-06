using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.TriangleMesh.VertexComponents
{
    public class BitangentComponent : IVertexComponent
    {
        public BitangentComponent()
        {
            m_data_[0] = 0.0f;
            m_data_[1] = 0.0f;
            m_data_[2] = 0.0f;
        }

        public BitangentComponent(float x, float y, float z)
        {
            m_data_[0] = x;
            m_data_[1] = y;
            m_data_[2] = z;
        }

        public BitangentComponent(float[] coords)
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
