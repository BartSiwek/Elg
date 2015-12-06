using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MeshConverter.TriangleMesh.TriangleLayout
{
    public class TriangleIndexFormatFactory
    {
        public static TriangleIndexFormat[] GetPossibleFormats()
        {
            return new TriangleIndexFormat[] {
                TriangleIndexFormat.R32_UINT,
                TriangleIndexFormat.R16_UINT,
            };
        }
    }
}
