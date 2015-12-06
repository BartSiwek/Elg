using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Newtonsoft.Json;

/*
namespace MeshConverter
{
    public class MeshExporter
    {
        MeshExporter()
        {
        }

        public void ExportMeshes(string filename, Json.SubMeshExportDescription[] export_descriptions, LogCallback callback)
        {
            // Prapare meshes
            Json.JsonExportedSubMesh[] exported_submeshes = new Json.JsonExportedSubMesh[export_descriptions.Length];
            for (int export_desc_index = 0; export_desc_index < export_descriptions.Length; ++export_desc_index)
            {
                Json.SubMeshExportDescription desc = export_descriptions[export_desc_index];
                SubMesh submesh = Mesh.Instance.SubMeshes[desc.SubMeshIndex];
                exported_submeshes[export_desc_index] = new Json.JsonExportedSubMesh(submesh, desc);
            }

            // Prepare exported mesh
            Json.JsonExportedMesh exported_mesh = new Json.JsonExportedMesh(exported_submeshes);

            // Export
            TextWriter output = null;
            try
            {
                output = new StreamWriter(filename, false, Encoding.ASCII);
                output.WriteLine(JsonConvert.SerializeObject(exported_mesh, Formatting.Indented));
                LogSuccessMessage(callback);
            }
            catch (Exception e)
            {
                LogErrorMessage(e, callback);
            }
            finally
            {
                if (output != null)
                {
                    output.Close();
                }
            }
        }

        private void LogErrorMessage(Exception e, LogCallback callback)
        {
            callback(String.Format("Error exporting [{0}]{1}",
                                   e.Message,
                                   Environment.NewLine
                                  )
                    );
        }

        private void LogSuccessMessage(LogCallback callback)
        {
            callback(String.Format("Exported meshes successfully...{0}",
                                   Environment.NewLine
                                  )
                    );
        }

        //Implementation of Singleton pattern
        public static MeshExporter Instance
        {
            get
            {
                if (s_mesh_exporter_ == null)
                {
                    s_mesh_exporter_ = new MeshExporter();
                }

                return s_mesh_exporter_;
            }
        }

        private static MeshExporter s_mesh_exporter_ = null;
    }
}
*/
