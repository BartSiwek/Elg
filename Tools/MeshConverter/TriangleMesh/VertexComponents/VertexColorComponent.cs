using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.TriangleMesh.VertexComponents
{
    public class VertexColorComponent : IVertexComponent
    {
        public VertexColorComponent()
        {
            m_data_[0] = 0.0f;
            m_data_[1] = 0.0f;
            m_data_[2] = 0.0f;
            m_data_[3] = 0.0f;
        }

        public VertexColorComponent(float r, float g, float b, float a)
        {
            m_data_[0] = r;
            m_data_[1] = g;
            m_data_[2] = b;
            m_data_[3] = a;
        }

        public VertexColorComponent(float[] color_values)
        {
            Debug.Assert(color_values.Length == 4, "Length of color values must be 4");

            m_data_ = color_values;
        }

        public float[] Value
        {
            get
            {
                return m_data_;
            }
            set
            {
                Debug.Assert(value.Length == 4, "Length of value must be 4");
                m_data_ = value;
            }
        }

        public void Export(IMeshExporter exporter, LayoutEntry entry)
        {
            exporter.ExportVertexComponent(m_data_, entry);
        }

        private float[] m_data_ = new float[4];
    }
}
