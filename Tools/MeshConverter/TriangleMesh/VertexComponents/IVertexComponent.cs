using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MeshConverter.Exporters;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.TriangleMesh.VertexComponents
{
    public interface IVertexComponent
    {
        void Export(IMeshExporter exporter, LayoutEntry entry);
    }
}
