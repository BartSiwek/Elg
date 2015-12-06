using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace MeshConverter.TriangleMesh.VertexLayout
{
    public class LayoutEntry
    {
        public LayoutEntry(SubMesh parent, string semantic_name, int semantic_index, LayoutEntryFormat default_layout, 
                           LayoutEntryFormat[] possible_layouts)
        {
            IsSelected = true;
            Parent = parent;
            SemanticName = semantic_name;
            SemanticIndex = semantic_index;
            DefaultFormat = default_layout;
            PossibleFormats = possible_layouts;
            m_layout_ = default_layout;
        }

        public bool IsSelected
        {
            get;
            set;
        }

        public string Label
        {
            get
            {
                string index_string = (SemanticIndex >= 0 ? SemanticIndex.ToString() : "");
                return String.Format("{0}{1} ({2})", SemanticName, index_string, Format);
            }
        }

        public SubMesh Parent
        {
            get;
            private set;
        }

        public string SemanticName
        {
            get;
            set;
        }

        public int SemanticIndex
        {
            get;
            set;
        }

        public LayoutEntryFormat Format
        {
            get
            {
                return m_layout_;
            }
            set
            {
                if(Array.IndexOf<LayoutEntryFormat>(PossibleFormats, value) == -1)
                {
                    throw new ArgumentException("Invalid format", "value");
                }
                m_layout_ = value;
            }
        }

        public LayoutEntryFormat DefaultFormat
        {
            get;
            private set;
        }

        public LayoutEntryFormat[] PossibleFormats
        {
            get;
            private set;
        }

        public int FormatSizeInBytes
        {
            get
            {
                switch (Format)
                {
                    case LayoutEntryFormat.R32G32B32A32_FLOAT:  // 16 bytes == 128 bits
                    case LayoutEntryFormat.R32G32B32A32_UINT:
                    case LayoutEntryFormat.R32G32B32A32_SINT:
                        return 16;
                    case LayoutEntryFormat.R32G32B32_FLOAT:  // 12 bytes == 96 bits
                    case LayoutEntryFormat.R32G32B32_UINT:
                    case LayoutEntryFormat.R32G32B32_SINT:
                        return 12;
                    case LayoutEntryFormat.R16G16B16A16_FLOAT:  // 8 bytes == 64 bits
                    case LayoutEntryFormat.R16G16B16A16_UNORM:
                    case LayoutEntryFormat.R16G16B16A16_UINT:
                    case LayoutEntryFormat.R16G16B16A16_SNORM:
                    case LayoutEntryFormat.R16G16B16A16_SINT:
                    case LayoutEntryFormat.R32G32_FLOAT:
                    case LayoutEntryFormat.R32G32_UINT:
                    case LayoutEntryFormat.R32G32_SINT:
                        return 8;
                    case LayoutEntryFormat.R10G10B10A2_UNORM:  // 4 bytes == 32 bits
                    case LayoutEntryFormat.R10G10B10A2_UINT:
                    case LayoutEntryFormat.R11G11B10_FLOAT:
                    case LayoutEntryFormat.R8G8B8A8_UNORM:
                    case LayoutEntryFormat.R8G8B8A8_UINT:
                    case LayoutEntryFormat.R8G8B8A8_SNORM:
                    case LayoutEntryFormat.R8G8B8A8_SINT:
                    case LayoutEntryFormat.B8G8R8A8_UNORM:
                    case LayoutEntryFormat.B8G8R8X8_UNORM:
                    case LayoutEntryFormat.R16G16_FLOAT:
                    case LayoutEntryFormat.R16G16_UNORM:
                    case LayoutEntryFormat.R16G16_UINT:
                    case LayoutEntryFormat.R16G16_SNORM:
                    case LayoutEntryFormat.R16G16_SINT:
                    case LayoutEntryFormat.R32_FLOAT:
                    case LayoutEntryFormat.R32_UINT:
                    case LayoutEntryFormat.R32_SINT:
                        return 4;
                    case LayoutEntryFormat.R8G8_UNORM:  // 2 bytes == 16 bits
                    case LayoutEntryFormat.R8G8_UINT:
                    case LayoutEntryFormat.R8G8_SNORM:
                    case LayoutEntryFormat.R8G8_SINT:
                    case LayoutEntryFormat.R16_FLOAT:
                    case LayoutEntryFormat.R16_UNORM:
                    case LayoutEntryFormat.R16_UINT:
                    case LayoutEntryFormat.R16_SNORM:
                    case LayoutEntryFormat.R16_SINT:
                    case LayoutEntryFormat.B5G6R5_UNORM:
                    case LayoutEntryFormat.B5G5R5A1_UNORM:
                    case LayoutEntryFormat.B4G4R4A4_UNORM:
                        return 2;
                    case LayoutEntryFormat.R8_UNORM:  // 1 byte == 8 bits
                    case LayoutEntryFormat.R8_UINT:
                    case LayoutEntryFormat.R8_SNORM:
                    case LayoutEntryFormat.R8_SINT:
                        return 1;
                    default:
                        throw new InvalidOperationException("Unknown layout entry format format");
                }
            }
        }

        private LayoutEntryFormat m_layout_;
    }
}
