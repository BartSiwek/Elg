using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Newtonsoft.Json.Linq;
using System.Diagnostics;
using Newtonsoft.Json;
using MeshConverter.TriangleMesh.VertexLayout;
using MeshConverter.TriangleMesh.TriangleLayout;

namespace MeshConverter.Exporters
{
    class JsonExporter : IMeshExporter
    {
        public JsonExporter(string filename, LogCallback log_callback)
        {
            m_container_stack_ = new Stack<JContainer>();
            m_filename_ = filename;
            m_log_callback_ = log_callback;
        }

        public void BeginMeshExport()
        {
            JArray submesh_array = new JArray();
            m_container_stack_.Push(submesh_array);
        }

        public void BeginSubMeshExport()
        {
            JObject submesh_object = new JObject();
            m_container_stack_.Push(submesh_object);
        }

        public void ExportLayout(List<LayoutEntry> entries)
        {
            JArray entries_array = new JArray();

            int aligned_by_offset = 0;
            foreach(LayoutEntry entry in entries)
            {
                if (entry.IsSelected)
                {
                    JObject entry_object = new JObject();

                    entry_object.Add("SemanticName", entry.SemanticName);
                    entry_object.Add("SemanticIndex", (entry.SemanticIndex >= 0 ? entry.SemanticIndex.ToString() : "0"));
                    entry_object.Add("Format", entry.DefaultFormat.ToString());
                    entry_object.Add("InputSlot", "0");
                    entry_object.Add("AlignedByOffset", aligned_by_offset.ToString());
                    entry_object.Add("InputSlotClass", "INPUT_PER_VERTEX_DATA");
                    entry_object.Add("InstanceDataStepRate", "0");

                    entries_array.Add(entry_object);

                    aligned_by_offset += entry.FormatSizeInBytes;
                }
            }


            JContainer submesh_container = m_container_stack_.Peek();
            JProperty layout_property = new JProperty("VertexFormat", entries_array);
            submesh_container.Add(layout_property);
        }

        public void ExportTriangleFormat(TriangleIndexFormat format, TriangleIndexFormat default_format)
        {
            JContainer submesh_container = m_container_stack_.Peek();
            JProperty format_property = new JProperty("IndexFormat", default_format.ToString());
            submesh_container.Add(format_property);
        }

        public void BeginVerticesExport()
        {
            JArray vertices_array = new JArray();
            m_container_stack_.Push(vertices_array);
        }

        public void BeginVertexExport()
        {
            JObject vertex_object = new JObject();
            m_container_stack_.Push(vertex_object);
        }

        public void ExportVertexComponent(float[] values, TriangleMesh.VertexLayout.LayoutEntry entry)
        {
            string entry_name = entry.SemanticName + (entry.SemanticIndex >= 0 ? entry.SemanticIndex.ToString() : "");
            JArray values_array = new JArray(values);
            JProperty component_property = new JProperty(entry_name, values_array);

            JContainer vertex_container = m_container_stack_.Peek();
            vertex_container.Add(component_property);
        }

        public void EndVertexExport()
        {
            JContainer vertex_container = m_container_stack_.Pop();
            JContainer vertices_container = m_container_stack_.Peek();
            vertices_container.Add(vertex_container);
        }

        public void EndVerticesExport()
        {
            JContainer vertices_container = m_container_stack_.Pop();
            JContainer submesh_container = m_container_stack_.Peek();
            JProperty vertices_property = new JProperty("Vertices", vertices_container);
            submesh_container.Add(vertices_property);
        }

        public void BeginTrianglesExport()
        {
            JArray triangles_array = new JArray();
            m_container_stack_.Push(triangles_array);
        }

        public void ExportTriangle(uint[] indices)
        {
            JArray indeices_array = new JArray(indices);

            JContainer triangle_container = m_container_stack_.Peek();
            triangle_container.Add(indeices_array);
        }

        public void EndTrianglesExport()
        {
            JContainer triangles_container = m_container_stack_.Pop();
            JContainer submesh_container = m_container_stack_.Peek();
            JProperty triangles_property = new JProperty("Triangles", triangles_container);
            submesh_container.Add(triangles_property);
        }

        public void EndSubMeshExport()
        {
            JContainer submesh_container = m_container_stack_.Pop();
            m_container_stack_.Peek().Add(submesh_container);
        }

        public void EndMeshExport()
        {
            StreamWriter writer = null;
            try
            {
                JContainer submesh_container = m_container_stack_.Pop();  // Pop submesh array
                writer = new StreamWriter(m_filename_);
                writer.Write(submesh_container.ToString(Formatting.Indented));
            }
            catch (Exception e)
            {
                m_log_callback_(String.Format("Exception while exporting mesh [{0}]{1}",
                                                  e.Message, 
                                                  Environment.NewLine));
            }
            finally
            {
                if (writer != null)
                {
                    writer.Close();
                    writer = null;
                }
            }
        }

        private Stack<JContainer> m_container_stack_;
        private string m_filename_;
        private LogCallback m_log_callback_;
    }
}
