using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MeshConverter.TriangleMesh;
using MeshConverter.TriangleMesh.VertexLayout;
using MeshConverter.TriangleMesh.TriangleLayout;

namespace MeshConverter.Exporters
{
    public interface IMeshExporter
    {
        void BeginMeshExport();

        void BeginSubMeshExport();

        void ExportLayout(List<LayoutEntry> entries);
        void ExportTriangleFormat(TriangleIndexFormat format, TriangleIndexFormat default_format);

        void BeginVerticesExport();
        void BeginVertexExport();
        void ExportVertexComponent(float[] values, LayoutEntry entry);
        void EndVertexExport();
        void EndVerticesExport();

        void BeginTrianglesExport();
        void ExportTriangle(uint[] indices);
        void EndTrianglesExport();

        void EndSubMeshExport();

        void EndMeshExport();
    }
}
