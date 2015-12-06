using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using MeshConverter.TriangleMesh;
using MeshConverter.TriangleMesh.VertexComponents;
using MeshConverter.TriangleMesh.TriangleLayout;

namespace MeshConverter
{
    public class MeshImporter
    {
        // Interface
        public void OpenMesh(string filename, Assimp.PostProcessSteps flags, LogCallback callback = null)
        {
            // Create the importer
            Assimp.AssimpImporter importer = new Assimp.AssimpImporter();

            // Add a logging callback 
            if (callback != null)
            {
                Assimp.LogStream logstream = new Assimp.LogStream(delegate(String msg, IntPtr userData) {
                    callback(msg);
                });
                importer.AttachLogStream(logstream);
            }

            // Set importer.SetConfig if needed

            // Add aditional options of needed
            Assimp.Scene scene = importer.ImportFile(filename, flags);

            // Set the current scene
            Mesh.Instance = CreateMesh(scene, callback);

            // Clean up
            importer.Dispose();
        }

        private Mesh CreateMesh(Assimp.Scene scene, LogCallback callback)
        {
            List<SubMesh> submeshes = new List<SubMesh>();
            for (int submesh_index = 0; submesh_index < scene.MeshCount; ++submesh_index)
            {
                if (scene.Meshes[submesh_index].PrimitiveType == Assimp.PrimitiveType.Triangle)
                {
                    submeshes.Add(CreateSubMesh(submesh_index, scene.Meshes[submesh_index]));
                }
                else
                {
                    callback(String.Format("Skipping a nontraingluar mesh with index {0}.{1}", 
                                           submesh_index,
                                           Environment.NewLine
                                          )
                            );
                }
            }
            return new Mesh(submeshes.ToArray());
        }

        private SubMesh CreateSubMesh(int submesh_index, Assimp.Mesh current_mesh)
        {
            // NOTE: The order we add layout entries and vertex components must be the same!!!

            // Create container
            SubMesh submesh = new SubMesh(current_mesh.VertexCount, current_mesh.FaceCount, submesh_index,
                                          TriangleIndexFormat.R32_UINT,
                                          TriangleIndexFormatFactory.GetPossibleFormats());

            // Setup layout
            if(current_mesh.HasNormals)
            {
                submesh.AddLayoutEntry(VertexComponentType.NORMAL_COMPONENT, -1);
            }

            if (current_mesh.HasTangentBasis)
            {
                submesh.AddLayoutEntry(VertexComponentType.TANGENT_COMPONENT, -1);
                submesh.AddLayoutEntry(VertexComponentType.BITANGENT_COMPONENT, -1);
            }

            for (int channel_index = 0; channel_index < current_mesh.VertexColorChannelCount; ++channel_index)
            {
                submesh.AddLayoutEntry(VertexComponentType.VERTEX_COLOR_COMPONENT, channel_index);
            }

            for (int channel_index = 0; channel_index < current_mesh.TextureCoordsChannelCount; ++channel_index)
            {
                int uv_component_count = current_mesh.GetUVComponentCount(channel_index);               
                switch(uv_component_count)
                {
                    case 1:
                        submesh.AddLayoutEntry(VertexComponentType.TEXTCOORDS_1D_COMPONENT, channel_index);
                        break;
                    case 2:
                        submesh.AddLayoutEntry(VertexComponentType.TEXTCOORDS_2D_COMPONENT, channel_index);
                        break;
                    case 3:
                        submesh.AddLayoutEntry(VertexComponentType.TEXTCOORDS_3D_COMPONENT, channel_index);
                        break;
                    default:
                        throw new InvalidOperationException("Unexpected number of texcoords");
                }
            }

            // Analyze each vertex
            for (int vertex_index = 0; vertex_index < current_mesh.VertexCount; ++vertex_index)
            {
                // Copy vertex positions
                submesh.Vertices[vertex_index] = new Vertex(current_mesh.Vertices[vertex_index].X, 
                                                            current_mesh.Vertices[vertex_index].Y,
                                                            current_mesh.Vertices[vertex_index].Z);

                // Additional vertex data
                if(current_mesh.HasNormals)
                {
                    NormalComponent normal = 
                        new NormalComponent(current_mesh.Normals[vertex_index].X,
                                            current_mesh.Normals[vertex_index].Y,
                                            current_mesh.Normals[vertex_index].Z);
                    submesh.Vertices[vertex_index].AddVertexComponent(normal);
                }

                if (current_mesh.HasTangentBasis)
                {
                    TangentComponent tangent =
                        new TangentComponent(current_mesh.Normals[vertex_index].X,
                                             current_mesh.Normals[vertex_index].Y,
                                             current_mesh.Normals[vertex_index].Z);
                    submesh.Vertices[vertex_index].AddVertexComponent(tangent);

                    BitangentComponent bitangent =
                        new BitangentComponent(current_mesh.Normals[vertex_index].X,
                                               current_mesh.Normals[vertex_index].Y,
                                               current_mesh.Normals[vertex_index].Z);
                    submesh.Vertices[vertex_index].AddVertexComponent(bitangent);
                }

                for (int channel_index = 0; channel_index < current_mesh.VertexColorChannelCount; ++channel_index)
                {
                    VertexColorComponent color =
                        new VertexColorComponent(current_mesh.GetVertexColors(channel_index)[vertex_index].R,
                                                 current_mesh.GetVertexColors(channel_index)[vertex_index].G,
                                                 current_mesh.GetVertexColors(channel_index)[vertex_index].B,
                                                 current_mesh.GetVertexColors(channel_index)[vertex_index].A);
                    submesh.Vertices[vertex_index].AddVertexComponent(color);
                }

                for (int channel_index = 0; channel_index < current_mesh.TextureCoordsChannelCount; ++channel_index)
                {
                    int uv_component_count = current_mesh.GetUVComponentCount(channel_index);
                    IVertexComponent texture_coords_component = null;
                    switch (uv_component_count)
                    {
                        case 1:
                            texture_coords_component =
                                new TextureCoords1DComponent(
                                    current_mesh.GetTextureCoords(channel_index)[vertex_index].X);
                            break;
                        case 2:
                            texture_coords_component =
                                new TextureCoords2DComponent(
                                    current_mesh.GetTextureCoords(channel_index)[vertex_index].X,
                                    current_mesh.GetTextureCoords(channel_index)[vertex_index].Y);
                            break;
                        case 3:
                            texture_coords_component =
                                new TextureCoords3DComponent(
                                    current_mesh.GetTextureCoords(channel_index)[vertex_index].X,
                                    current_mesh.GetTextureCoords(channel_index)[vertex_index].Y,
                                    current_mesh.GetTextureCoords(channel_index)[vertex_index].Z);
                            break;
                        default:
                            throw new InvalidOperationException("Unexpected number of texcoords");
                    }
                    submesh.Vertices[vertex_index].AddVertexComponent(texture_coords_component);
                }
            }

            
            // Copy triangle indices
            for (int face_index = 0; face_index < current_mesh.FaceCount; ++face_index)
            {
                submesh.Triangles[face_index] = new Triangle(current_mesh.Faces[face_index].Indices);
            }

            return submesh;
        }

        //Implementation of Singleton pattern
        public static MeshImporter Instance
        {
            get
            {
                if (s_mesh_ == null)
                {
                    s_mesh_ = new MeshImporter();
                }

                return s_mesh_;
            }
        }

        // Data memebers [static]
        private static MeshImporter s_mesh_ = null;
    }
}
