/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ASSETMANAGER_LOADERS_TEXTMESHLOADER_H_
#define ELG_ASSETMANAGER_LOADERS_TEXTMESHLOADER_H_

#include <string>

#include "Elg/Utilities/Types.h"
#include "Elg/Memory/Memory.h"
#include "Elg/Utilities/Filesystem/File.h"
#include "Elg/External/jansson/jansson.h"

// Forward declarations
namespace Elg { namespace AssetManager { namespace Assets { class Mesh; } } }

// Class declaration
namespace Elg {
namespace AssetManager {
namespace Loaders {

class TextMesgLoader {
 public:
  // Constants and enums
  static const elg_uint32 ASSET_TYPE_ID_HASH;

  // Typedefs
  typedef Elg::AssetManager::Assets::Mesh loaded_type;

  // Constructors
  TextMesgLoader() {
  }

  // Destructors
  ~TextMesgLoader() {
  }

  // Methods, including static methods
  template<typename AllocatorType>
  Elg::AssetManager::Assets::Mesh Load(std::string filename, AllocatorType* allocator) {
    // Open file
    Elg::Utilities::Filesystem::File mesh_file(filename, Elg::Utilities::Filesystem::FILE_ACCESS_MODE_READ);

    // Allocate memory for file contents
    elg_uint32 mesh_file_size = mesh_file.Size();
    char* file_contents = ElgNewArray(char, mesh_file_size + 1, allocator);
    file_contents[0] = 0;

    // Read the contents
    elg_uint32 bytes_read = mesh_file.Read(file_contents, mesh_file_size);
    file_data[bytes_read] = '\0';

    // Parse the JSON
    json_error_t error;
    json_t* root = json_loads(file_data, 0, &error);

    // Free the memory
    free(file_data);

    ASSERT(root, "Cannot parse JSON in mesh file");
    ASSERT(json_is_array(root), "JSON root of a mesh file is not an array");

    // Get the submesh count
    elg_uint32 submesh_count = json_array_size(root);

    for (unsigned int i = 0; i < submesh_count; i++) {
      json_t* submesh;
      json_t* vertex_format_array;

      submesh = json_array_get(root, i);
      ASSERT(json_is_object(submesh), "JSON submesh %d is not an object", i + 1);

      vertex_format_array = json_object_get(submesh, "VertexFormat");
      ASSERT(json_is_array(vertex_format_array), "JSON VertexFormat in submesh %d is not an array", i + 1);

      for (unsigned int j = 0; j < json_array_size(vertex_format_array); j++) {
        // Get the format
        json_t* format_entry = json_array_get(vertex_format_array, j);
        ASSERT(json_is_object(format_entry), "JSON Entry %d in VertexFormat in submesh %d is not an object\n",
               j + 1, i + 1);

        // Get the format components
        json_t* semantic_name = json_object_get(format_entry, "SemanticName");
        json_t* semantic_index = json_object_get(format_entry, "SemanticIndex");
        json_t* format = json_object_get(format_entry, "Format");
        json_t* input_slot = json_object_get(format_entry, "InputSlot");
        json_t* aligned_by_offset = json_object_get(format_entry, "AlignedByOffset");
        json_t* input_slot_class = json_object_get(format_entry, "InputSlotClass");
        json_t* instance_data_step_rate = json_object_get(format_entry, "InstanceDataStepRate");

        // Assert they are okay
        ASSERT(json_is_string(semantic_name),
               "JSON SemanticName of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
        ASSERT(json_is_integer(semantic_name),
               "JSON SemanticIndex of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
        ASSERT(json_is_string(semantic_name),
               "JSON Format of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
        ASSERT(json_is_integer(semantic_name),
               "JSON InputSlot of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
        ASSERT(json_is_integer(semantic_name),
               "JSON AlignedByOffset of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
        ASSERT(json_is_string(semantic_name),
               "JSON InputSlotClass of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
        ASSERT(json_is_integer(semantic_name),
               "JSON InstanceDataStepRate of entry %d in VertexFormat in submesh %d is not a string\n", j + 1, i + 1);
      }
    }

    json_decref(root);
  }

  template<typename AllocatorType>
  void Unload(Elg::AssetManager::Assets::Image* image, AllocatorType* allocator) {
  }

 private:
  // Disallow copy and assign
  TextMesgLoader(const TextMesgLoader& orig);
  void operator=(const TextMesgLoader&);
};

}  // namespace Loaders
}  // namespace AssetManager
}  // namespace Elg


/*
#include "Elg/AssetManager/Loaders/ImageLoader-inl.h"
*/

#endif  // ELG_ASSETMANAGER_LOADERS_TEXTMESHLOADER_H_
