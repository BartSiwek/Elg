using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MeshConverter.Exporters;

namespace MeshConverter.TriangleMesh
{
    public class Triangle
    {
        public Triangle(uint[] indices)
        {
            Indices = new uint[3];

            Indices[0] = indices[0];
            Indices[1] = indices[1];
            Indices[2] = indices[2];
        }

        public uint[] Indices
        {
            get;
            set;
        }

        public void Export(IMeshExporter exporter)
        {
            exporter.ExportTriangle(Indices);
        }
    }
}
