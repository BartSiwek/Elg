﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MeshConverter.TriangleMesh.VertexLayout
{
    public enum LayoutEntryFormat
    {
        R32G32B32A32_FLOAT,
        R32G32B32A32_UINT,
        R32G32B32A32_SINT,

        R32G32B32_FLOAT,
        R32G32B32_UINT,
        R32G32B32_SINT,

        R16G16B16A16_FLOAT,
        R16G16B16A16_UNORM,
        R16G16B16A16_UINT,
        R16G16B16A16_SNORM,
        R16G16B16A16_SINT,

        R32G32_FLOAT,
        R32G32_UINT,
        R32G32_SINT,

        R10G10B10A2_UNORM,
        R10G10B10A2_UINT,

        R11G11B10_FLOAT,

        R8G8B8A8_UNORM,
        R8G8B8A8_UINT,
        R8G8B8A8_SNORM,
        R8G8B8A8_SINT,
        B8G8R8A8_UNORM,
        B8G8R8X8_UNORM,

        R16G16_FLOAT,
        R16G16_UNORM,
        R16G16_UINT,
        R16G16_SNORM,
        R16G16_SINT,

        R32_FLOAT,
        R32_UINT,
        R32_SINT,

        R8G8_UNORM,
        R8G8_UINT,
        R8G8_SNORM,
        R8G8_SINT,

        R16_FLOAT,
        R16_UNORM,
        R16_UINT,
        R16_SNORM,
        R16_SINT,

        R8_UNORM,
        R8_UINT,
        R8_SNORM,
        R8_SINT,

        B5G6R5_UNORM,
        B5G5R5A1_UNORM,
        B4G4R4A4_UNORM,
    }
}