using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MeshConverter.TriangleMesh.VertexLayout
{
    public class LayoutEntryFactory
    {
        public static LayoutEntry CreateLayoutEntry(SubMesh parent, VertexComponentType type, int index)
        {
            switch (type)
            {
                case VertexComponentType.POSITION_COMPONENT:
                    return new LayoutEntry(parent,
                                           "POSITION",
                                           index,
                                           LayoutEntryFormat.R32G32B32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 4 Components
                                               LayoutEntryFormat.R32G32B32A32_FLOAT,
                                               LayoutEntryFormat.R32G32B32A32_UINT,
                                               LayoutEntryFormat.R32G32B32A32_SINT,

                                               LayoutEntryFormat.R16G16B16A16_FLOAT,
                                               LayoutEntryFormat.R16G16B16A16_UNORM,
                                               LayoutEntryFormat.R16G16B16A16_UINT,
                                               LayoutEntryFormat.R16G16B16A16_SNORM,
                                               LayoutEntryFormat.R16G16B16A16_SINT,

                                               LayoutEntryFormat.R10G10B10A2_UNORM,
                                               LayoutEntryFormat.R10G10B10A2_UINT,

                                               LayoutEntryFormat.R8G8B8A8_UNORM,
                                               LayoutEntryFormat.R8G8B8A8_UINT,
                                               LayoutEntryFormat.R8G8B8A8_SNORM,
                                               LayoutEntryFormat.R8G8B8A8_SINT,
                                               LayoutEntryFormat.B8G8R8A8_UNORM,

                                               LayoutEntryFormat.B4G4R4A4_UNORM,

                                               LayoutEntryFormat.B5G5R5A1_UNORM,
                                                   
                                               // 3 components
                                               LayoutEntryFormat.R32G32B32_FLOAT,
                                               LayoutEntryFormat.R32G32B32_UINT,
                                               LayoutEntryFormat.R32G32B32_SINT,

                                               LayoutEntryFormat.R11G11B10_FLOAT,

                                               LayoutEntryFormat.B8G8R8X8_UNORM,

                                               LayoutEntryFormat.B5G6R5_UNORM,
                                           });
                case VertexComponentType.NORMAL_COMPONENT:
                    return new LayoutEntry(parent,
                                           "NORMAL",
                                           index,
                                           LayoutEntryFormat.R32G32B32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 4 Components
                                               LayoutEntryFormat.R32G32B32A32_FLOAT,
                                               LayoutEntryFormat.R32G32B32A32_UINT,
                                               LayoutEntryFormat.R32G32B32A32_SINT,

                                               LayoutEntryFormat.R16G16B16A16_FLOAT,
                                               LayoutEntryFormat.R16G16B16A16_UNORM,
                                               LayoutEntryFormat.R16G16B16A16_UINT,
                                               LayoutEntryFormat.R16G16B16A16_SNORM,
                                               LayoutEntryFormat.R16G16B16A16_SINT,

                                               LayoutEntryFormat.R10G10B10A2_UNORM,
                                               LayoutEntryFormat.R10G10B10A2_UINT,

                                               LayoutEntryFormat.R8G8B8A8_UNORM,
                                               LayoutEntryFormat.R8G8B8A8_UINT,
                                               LayoutEntryFormat.R8G8B8A8_SNORM,
                                               LayoutEntryFormat.R8G8B8A8_SINT,
                                               LayoutEntryFormat.B8G8R8A8_UNORM,

                                               LayoutEntryFormat.B4G4R4A4_UNORM,

                                               LayoutEntryFormat.B5G5R5A1_UNORM,

                                               // 3 components
                                               LayoutEntryFormat.R32G32B32_FLOAT,
                                               LayoutEntryFormat.R32G32B32_UINT,
                                               LayoutEntryFormat.R32G32B32_SINT,

                                               LayoutEntryFormat.R11G11B10_FLOAT,

                                               LayoutEntryFormat.B8G8R8X8_UNORM,

                                               LayoutEntryFormat.B5G6R5_UNORM,

                                               // 2 components
                                               LayoutEntryFormat.R32G32_FLOAT,
                                               LayoutEntryFormat.R32G32_UINT,
                                               LayoutEntryFormat.R32G32_SINT,

                                               LayoutEntryFormat.R16G16_FLOAT,
                                               LayoutEntryFormat.R16G16_UNORM,
                                               LayoutEntryFormat.R16G16_UINT,
                                               LayoutEntryFormat.R16G16_SNORM,
                                               LayoutEntryFormat.R16G16_SINT,

                                               LayoutEntryFormat.R8G8_UNORM,
                                               LayoutEntryFormat.R8G8_UINT,
                                               LayoutEntryFormat.R8G8_SNORM,
                                               LayoutEntryFormat.R8G8_SINT,
                                           });
                case VertexComponentType.TANGENT_COMPONENT:
                    return new LayoutEntry(parent,
                                           "TANGENT",
                                           index,
                                           LayoutEntryFormat.R32G32B32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 4 Components
                                               LayoutEntryFormat.R32G32B32A32_FLOAT,
                                               LayoutEntryFormat.R32G32B32A32_UINT,
                                               LayoutEntryFormat.R32G32B32A32_SINT,

                                               LayoutEntryFormat.R16G16B16A16_FLOAT,
                                               LayoutEntryFormat.R16G16B16A16_UNORM,
                                               LayoutEntryFormat.R16G16B16A16_UINT,
                                               LayoutEntryFormat.R16G16B16A16_SNORM,
                                               LayoutEntryFormat.R16G16B16A16_SINT,

                                               LayoutEntryFormat.R10G10B10A2_UNORM,
                                               LayoutEntryFormat.R10G10B10A2_UINT,

                                               LayoutEntryFormat.R8G8B8A8_UNORM,
                                               LayoutEntryFormat.R8G8B8A8_UINT,
                                               LayoutEntryFormat.R8G8B8A8_SNORM,
                                               LayoutEntryFormat.R8G8B8A8_SINT,
                                               LayoutEntryFormat.B8G8R8A8_UNORM,

                                               LayoutEntryFormat.B4G4R4A4_UNORM,

                                               LayoutEntryFormat.B5G5R5A1_UNORM,

                                               // 3 components
                                               LayoutEntryFormat.R32G32B32_FLOAT,
                                               LayoutEntryFormat.R32G32B32_UINT,
                                               LayoutEntryFormat.R32G32B32_SINT,

                                               LayoutEntryFormat.R11G11B10_FLOAT,

                                               LayoutEntryFormat.B8G8R8X8_UNORM,

                                               LayoutEntryFormat.B5G6R5_UNORM,

                                               // 2 components
                                               LayoutEntryFormat.R32G32_FLOAT,
                                               LayoutEntryFormat.R32G32_UINT,
                                               LayoutEntryFormat.R32G32_SINT,

                                               LayoutEntryFormat.R16G16_FLOAT,
                                               LayoutEntryFormat.R16G16_UNORM,
                                               LayoutEntryFormat.R16G16_UINT,
                                               LayoutEntryFormat.R16G16_SNORM,
                                               LayoutEntryFormat.R16G16_SINT,

                                               LayoutEntryFormat.R8G8_UNORM,
                                               LayoutEntryFormat.R8G8_UINT,
                                               LayoutEntryFormat.R8G8_SNORM,
                                               LayoutEntryFormat.R8G8_SINT,
                                           });
                case VertexComponentType.BITANGENT_COMPONENT:
                    return new LayoutEntry(parent,
                                           "BITANGENT",
                                           index,
                                           LayoutEntryFormat.R32G32B32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 4 Components
                                               LayoutEntryFormat.R32G32B32A32_FLOAT,
                                               LayoutEntryFormat.R32G32B32A32_UINT,
                                               LayoutEntryFormat.R32G32B32A32_SINT,

                                               LayoutEntryFormat.R16G16B16A16_FLOAT,
                                               LayoutEntryFormat.R16G16B16A16_UNORM,
                                               LayoutEntryFormat.R16G16B16A16_UINT,
                                               LayoutEntryFormat.R16G16B16A16_SNORM,
                                               LayoutEntryFormat.R16G16B16A16_SINT,

                                               LayoutEntryFormat.R10G10B10A2_UNORM,
                                               LayoutEntryFormat.R10G10B10A2_UINT,

                                               LayoutEntryFormat.R8G8B8A8_UNORM,
                                               LayoutEntryFormat.R8G8B8A8_UINT,
                                               LayoutEntryFormat.R8G8B8A8_SNORM,
                                               LayoutEntryFormat.R8G8B8A8_SINT,
                                               LayoutEntryFormat.B8G8R8A8_UNORM,

                                               LayoutEntryFormat.B4G4R4A4_UNORM,

                                               LayoutEntryFormat.B5G5R5A1_UNORM,

                                               // 3 components
                                               LayoutEntryFormat.R32G32B32_FLOAT,
                                               LayoutEntryFormat.R32G32B32_UINT,
                                               LayoutEntryFormat.R32G32B32_SINT,

                                               LayoutEntryFormat.R11G11B10_FLOAT,

                                               LayoutEntryFormat.B8G8R8X8_UNORM,

                                               LayoutEntryFormat.B5G6R5_UNORM,

                                               // 2 components
                                               LayoutEntryFormat.R32G32_FLOAT,
                                               LayoutEntryFormat.R32G32_UINT,
                                               LayoutEntryFormat.R32G32_SINT,

                                               LayoutEntryFormat.R16G16_FLOAT,
                                               LayoutEntryFormat.R16G16_UNORM,
                                               LayoutEntryFormat.R16G16_UINT,
                                               LayoutEntryFormat.R16G16_SNORM,
                                               LayoutEntryFormat.R16G16_SINT,

                                               LayoutEntryFormat.R8G8_UNORM,
                                               LayoutEntryFormat.R8G8_UINT,
                                               LayoutEntryFormat.R8G8_SNORM,
                                               LayoutEntryFormat.R8G8_SINT,
                                           });
                case VertexComponentType.VERTEX_COLOR_COMPONENT:
                    return new LayoutEntry(parent,
                                           "COLOR",
                                           index,
                                           LayoutEntryFormat.R32G32B32A32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 4 Components
                                               LayoutEntryFormat.R32G32B32A32_FLOAT,
                                               LayoutEntryFormat.R32G32B32A32_UINT,
                                               LayoutEntryFormat.R32G32B32A32_SINT,

                                               LayoutEntryFormat.R16G16B16A16_FLOAT,
                                               LayoutEntryFormat.R16G16B16A16_UNORM,
                                               LayoutEntryFormat.R16G16B16A16_UINT,
                                               LayoutEntryFormat.R16G16B16A16_SNORM,
                                               LayoutEntryFormat.R16G16B16A16_SINT,

                                               LayoutEntryFormat.R10G10B10A2_UNORM,
                                               LayoutEntryFormat.R10G10B10A2_UINT,

                                               LayoutEntryFormat.R8G8B8A8_UNORM,
                                               LayoutEntryFormat.R8G8B8A8_UINT,
                                               LayoutEntryFormat.R8G8B8A8_SNORM,
                                               LayoutEntryFormat.R8G8B8A8_SINT,
                                               LayoutEntryFormat.B8G8R8A8_UNORM,

                                               LayoutEntryFormat.B4G4R4A4_UNORM,

                                               LayoutEntryFormat.B5G5R5A1_UNORM,

                                               // 3 components
                                               LayoutEntryFormat.R32G32B32_FLOAT,
                                               LayoutEntryFormat.R32G32B32_UINT,
                                               LayoutEntryFormat.R32G32B32_SINT,

                                               LayoutEntryFormat.R11G11B10_FLOAT,

                                               LayoutEntryFormat.B8G8R8X8_UNORM,

                                               LayoutEntryFormat.B5G6R5_UNORM,
                                           });
                case VertexComponentType.TEXTCOORDS_1D_COMPONENT:
                                        return new LayoutEntry(parent,
                                           "TEXCOORD",
                                           index,
                                           LayoutEntryFormat.R32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 1 component
                                               LayoutEntryFormat.R32_FLOAT,
                                               LayoutEntryFormat.R32_UINT,
                                               LayoutEntryFormat.R32_SINT,

                                               LayoutEntryFormat.R16_FLOAT,
                                               LayoutEntryFormat.R16_UNORM,
                                               LayoutEntryFormat.R16_UINT,
                                               LayoutEntryFormat.R16_SNORM,
                                               LayoutEntryFormat.R16_SINT,

                                               LayoutEntryFormat.R8_UNORM,
                                               LayoutEntryFormat.R8_UINT,
                                               LayoutEntryFormat.R8_SNORM,
                                               LayoutEntryFormat.R8_SINT,
                                           });
                case VertexComponentType.TEXTCOORDS_2D_COMPONENT:
                                        return new LayoutEntry(parent,
                                           "TEXCOORD",
                                           index,
                                           LayoutEntryFormat.R32G32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 2 components
                                               LayoutEntryFormat.R32G32_FLOAT,
                                               LayoutEntryFormat.R32G32_UINT,
                                               LayoutEntryFormat.R32G32_SINT,

                                               LayoutEntryFormat.R16G16_FLOAT,
                                               LayoutEntryFormat.R16G16_UNORM,
                                               LayoutEntryFormat.R16G16_UINT,
                                               LayoutEntryFormat.R16G16_SNORM,
                                               LayoutEntryFormat.R16G16_SINT,

                                               LayoutEntryFormat.R8G8_UNORM,
                                               LayoutEntryFormat.R8G8_UINT,
                                               LayoutEntryFormat.R8G8_SNORM,
                                               LayoutEntryFormat.R8G8_SINT,

                                               // 1 component
                                               LayoutEntryFormat.R32_FLOAT,
                                               LayoutEntryFormat.R32_UINT,
                                               LayoutEntryFormat.R32_SINT,

                                               LayoutEntryFormat.R16_FLOAT,
                                               LayoutEntryFormat.R16_UNORM,
                                               LayoutEntryFormat.R16_UINT,
                                               LayoutEntryFormat.R16_SNORM,
                                               LayoutEntryFormat.R16_SINT,

                                               LayoutEntryFormat.R8_UNORM,
                                               LayoutEntryFormat.R8_UINT,
                                               LayoutEntryFormat.R8_SNORM,
                                               LayoutEntryFormat.R8_SINT,
                                           });
                case VertexComponentType.TEXTCOORDS_3D_COMPONENT:
                                        return new LayoutEntry(parent,
                                           "TEXCOORD",
                                           index,
                                           LayoutEntryFormat.R32G32B32_FLOAT,
                                           new LayoutEntryFormat[]
                                           {
                                               // 3 components
                                               LayoutEntryFormat.R32G32B32_FLOAT,
                                               LayoutEntryFormat.R32G32B32_UINT,
                                               LayoutEntryFormat.R32G32B32_SINT,

                                               LayoutEntryFormat.R11G11B10_FLOAT,

                                               LayoutEntryFormat.B8G8R8X8_UNORM,

                                               LayoutEntryFormat.B5G6R5_UNORM,

                                               // 2 components
                                               LayoutEntryFormat.R32G32_FLOAT,
                                               LayoutEntryFormat.R32G32_UINT,
                                               LayoutEntryFormat.R32G32_SINT,

                                               LayoutEntryFormat.R16G16_FLOAT,
                                               LayoutEntryFormat.R16G16_UNORM,
                                               LayoutEntryFormat.R16G16_UINT,
                                               LayoutEntryFormat.R16G16_SNORM,
                                               LayoutEntryFormat.R16G16_SINT,

                                               LayoutEntryFormat.R8G8_UNORM,
                                               LayoutEntryFormat.R8G8_UINT,
                                               LayoutEntryFormat.R8G8_SNORM,
                                               LayoutEntryFormat.R8G8_SINT,

                                               // 1 component
                                               LayoutEntryFormat.R32_FLOAT,
                                               LayoutEntryFormat.R32_UINT,
                                               LayoutEntryFormat.R32_SINT,

                                               LayoutEntryFormat.R16_FLOAT,
                                               LayoutEntryFormat.R16_UNORM,
                                               LayoutEntryFormat.R16_UINT,
                                               LayoutEntryFormat.R16_SNORM,
                                               LayoutEntryFormat.R16_SINT,

                                               LayoutEntryFormat.R8_UNORM,
                                               LayoutEntryFormat.R8_UINT,
                                               LayoutEntryFormat.R8_SNORM,
                                               LayoutEntryFormat.R8_SINT,
                                           });
                default:
                    throw new ArgumentException("The component type provided is unsupported", "type");
            }
        }
    }
}
