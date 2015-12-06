using System;
using System.Collections.Generic;
using System.Text;
using MeshConverter.TriangleMesh.VertexComponents;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.VertexLayout;
using System.Diagnostics;

namespace MeshConverter.TriangleMesh
{
    public class Vertex
    {
        public Vertex(float x, float y, float z)
        {
            m_components_ = new List<IVertexComponent>();
            PositionComponent position = new PositionComponent(x, y, z);
            AddVertexComponent(position);
        }

        public IVertexComponent GetVertexComponent(int index)
        {
            return m_components_[index];
        }

        public void AddVertexComponent(IVertexComponent component)
        {
            m_components_.Add(component);
        }

        public void Export(IMeshExporter exporter, List<LayoutEntry> entries)
        {
            Debug.Assert(m_components_.Count == entries.Count);

            exporter.BeginVertexExport();

            for(int component_index = 0; component_index < m_components_.Count; ++component_index)
            {
                if (entries[component_index].IsSelected)
                {
                    m_components_[component_index].Export(exporter, entries[component_index]);
                }
            }

            exporter.EndVertexExport();
        }

        private List<IVertexComponent> m_components_;
    }
}
