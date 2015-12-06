/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_MEMORY_MEMORY_H_
#define ELG_MEMORY_MEMORY_H_

#include <type_traits>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"

namespace Elg {
namespace Memory {

// Helper templates
template<typename T>
struct IsPod {
  static const bool value = std::is_pod<T>::value;
};

// Helper functions
template<typename AllocatorType>
inline void* Malloc(elg_size_type size, elg_size_type align, AllocatorType* allocator, const char* file,
                    elg_uint32 line) {
  // Just allocate the memory (out of memory NULL is handled okay)
  return allocator->Allocate(size, align, file, line);
}

template<typename AllocatorType>
inline void Free(void* ptr, AllocatorType* allocator, const char* file, elg_uint32 line) {
  // Act only on non-NULL pointers
  if (ptr != NULL) {
    // Free the memory
    allocator->Free(ptr, file, line);
  }
}

template<typename T, typename AllocatorType>
inline void* ElgNewHelper(AllocatorType* allocator, const char* file, int line) {
  // Don't call the constructor - just allocate the memory and return it to placement new
  return allocator->Allocate(sizeof(T), ELG_ALIGNOF(T), file, line);
}

template<typename T, typename AllocatorType>
inline void ElgDeleteHelper(T* ptr, AllocatorType* allocator, const char* file, int line) {
  // Act only on non-NULL pointers
  if (ptr != NULL) {
    // Call the destructor (compiler will ommit this for POD types)
    ptr->~T();

    // Free the memory
    allocator->Free(ptr, file, line);
  }
}

template<typename T, typename AllocatorType>
inline typename std::enable_if<IsPod<T>::value, T*>::type ElgNewArrayHelper(elg_size_type count,
                                                                            AllocatorType* allocator,
                                                                            const char* file, int line) {
  // Just allocate the memory (out of memory NULL is handled okay)
  return static_cast<T*>(allocator->Allocate(count*sizeof(T), ELG_ALIGNOF(T), file, line));
}

template<typename T, typename AllocatorType>
inline typename std::enable_if<!IsPod<T>::value, T*>::type ElgNewArrayHelper(elg_size_type count,
                                                                             AllocatorType* allocator,
                                                                             const char* file, int line) {
  // Helper struct
  struct AllocationHelper {
    elg_size_type Size;
    T Array[1];
  };

  // Compute the allocation size
  const elg_size_type allocation_size = sizeof(AllocationHelper) + (count-1)*sizeof(T);
  const elg_size_type allocation_align = ELG_ALIGNOF(AllocationHelper);

  // Allocate the memory
  void* ptr = allocator->Allocate(allocation_size, allocation_align, file, line);

  // Act only if we got the memory (NULL means we ran out)
  if (ptr != NULL) {
    AllocationHelper* h = static_cast<AllocationHelper*>(ptr);

    // Store number of elements
    h->Size = count;

    // Call placement new
    for (elg_size_type index = 0; index < count;++index) {
      new(h->Array + index) T;
    }

    // Hand user the pointer to the first element
    return &h->Array[0];
  } else {
    return NULL;
  }
}

template<typename T, typename AllocatorType>
inline typename std::enable_if<IsPod<T>::value, void>::type ElgDeleteArrayHelper(T* ptr, AllocatorType* allocator,
                                                                                 const char* file, int line) {
  // Act only on non-NULL pointers
  if (ptr != NULL) {
    allocator->Free(ptr, file, line);
  }
}

template<typename T, typename AllocatorType>
inline typename std::enable_if<!IsPod<T>::value, void>::type ElgDeleteArrayHelper(T* ptr, AllocatorType* allocator,
                                                                                  const char* file, int line) {
  // The helper struct
  struct Helper {
    elg_size_type Count;
    T Array[1];
  };

  // Act only on non-NULL pointers
  if (ptr != NULL) {
    // Convert the input pointer to the pointer to the struct
    Helper *h = reinterpret_cast<Helper*>(reinterpret_cast<elg_uint_pointer>(ptr) - ELG_OFFSETOF(Helper, Array[0]));

    // Get the count
    elg_size_type count = h->Count;

    // Call destructors in reverse order (C++ standard)
    for (elg_size_type i = count; i > 0; --i) {
      h->Array[i-1].~T();
    }

    // Free the actual memory
    allocator->Free(h, file, line);
  }
}

}  // namespace Memory
}  // namespace Elg

// Macros
#define ElgMalloc(SIZE, ALIGN, ALLOCATOR_PTR)                                                                         \
  Elg::Memory::Malloc((SIZE), (ALIGN), (ALLOCATOR_PTR), __FILE__, __LINE__)
#define ElgFree(PTR, ALLOCATOR_PTR)                                                                                   \
  Elg::Memory::Free(PTR, (ALLOCATOR_PTR), __FILE__, __LINE__)
#define ElgNew(TYPE, ALLOCATOR_PTR)                                                                                   \
  new(Elg::Memory::ElgNewHelper<TYPE>((ALLOCATOR_PTR), __FILE__, __LINE__)) TYPE
#define ElgDelete(PTR, ALLOCATOR_PTR)                                                                                 \
  Elg::Memory::ElgDeleteHelper((PTR), (ALLOCATOR_PTR), __FILE__, __LINE__)
#define ElgNewArray(TYPE, COUNT, ALLOCATOR_PTR)                                                                       \
  Elg::Memory::ElgNewArrayHelper<TYPE>((COUNT), (ALLOCATOR_PTR), __FILE__, __LINE__)
#define ElgDeleteArray(ARRAY_PTR, ALLOCATOR_PTR)                                                                      \
  Elg::Memory::ElgDeleteArrayHelper((ARRAY_PTR), (ALLOCATOR_PTR), __FILE__, __LINE__)

#endif  // ELG_MEMORY_MEMORY_H_
