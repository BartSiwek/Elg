using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MeshConverter.TriangleMesh
{
    public enum VertexComponentType
    {
        POSITION_COMPONENT = 0,
        NORMAL_COMPONENT = 1,
        TANGENT_COMPONENT = 2,
        BITANGENT_COMPONENT = 3,
        VERTEX_COLOR_COMPONENT = 4,
        TEXTCOORDS_1D_COMPONENT = 5,
        TEXTCOORDS_2D_COMPONENT = 6,
        TEXTCOORDS_3D_COMPONENT = 7,
    }
}
