  /*
   * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
   */

////////////////////////////////////////////////////////////////////////////////////////////////////
// This is suppose to be like std::vector but with fixed size and better allocator model- finsih it someday
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
#ifndef ELG_UTILITIES_ETL_FIXEDSIZEARRAY_H_
#define ELG_UTILITIES_ETL_FIXEDSIZEARRAY_H_

#include<iterator>

#include "Elg/Utilities/Types.h"
#include "Elg/Memory/Memory.h"
#include "Elg/Utilities/Containers/ArrayIterator.h"

namespace Elg {
namespace Utilities {
namespace Containers {

// Array class
template<typename T, typename AllocatorType>
class Array {
  public:
  // Typedefs
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef ArrayIterator<pointer, Array> iterator;
  typedef ArrayIterator<const_pointer, Array> const_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef size_type size_type;
  typedef elg_pointer_diff difference_type;
  typedef AllocatorType allocator_type;

  // Constructors
  Array(size_type n, allocator_type* allocator)
      : m_allocator_(allocator), m_start_(NULL), m_end_(NULL) {
    // Allocate
    m_start_ = ElgNewArray(T, n, m_allocator_);
    m_end_ = m_start_ + n;

    // Assert we got memory
    ASSERT(m_start_ != NULL, "Memory allocation of FixedSizeArray failed");
    
    // Set the default value
    for(size_type index = 0; index < n; ++index) {
      m_start_[index] = T();
    }
  }
  
  Array(size_type n, const value_type& value, allocator_type* allocator)
      : m_allocator_(allocator), m_start_(NULL), m_end_(NULL) {
    // Allocate
    m_start_ = ElgNewArray(T, n, m_allocator_);
    m_end_ = m_start_ + n;

    // Assert we got memory
    ASSERT(m_start_ != NULL, "Memory allocation of FixedSizeArray failed");

    // Set the provided value
    for(size_type index = 0; index < n; ++index) {
      m_start_[index] = value;
    }
  }

  template<typename InputIterator>
  Array(InputIterator first, InputIterator last, allocator_type* allocator)
      : m_allocator_(allocator), m_start_(NULL), m_end_(NULL) {
    // Allocate
    size_type n = std::distance(first, last);
    m_start_ = ElgNewArray(T, n, m_allocator_);
    m_end_ = m_start_ + n;

    // Assert we got memory
    ASSERT(m_start_ != NULL, "Memory allocation of FixedSizeArray failed");

    // Set the provided value
    for(size_type index = 0; index < n; ++index) {
      m_start_[index] = *(first++);
    }
  }

  Array(const Array& other)
      : m_start_(NULL), m_end_(NULL), m_allocator_(other.m_allocator_) {
    // Allocate
    size_type n = other.m_end_ - other.m_start_;
    m_start_ = ElgNewArray(T, n, m_allocator_);
    m_end_ = m_start_ + n;

    // Assert we got memory
    ASSERT(m_start_ != NULL, "Memory allocation of FixedSizeArray failed");

    // Copy the array
    for(size_type index = 0; index < n; ++index) {
      m_start_[index] = other.m_start_[index];
    }
  }

  // Destructor
  ~Array() {
    ElgDeleteArray(m_start_, m_allocator_);
  }

  // Operators [no initializer list assignment]
  Array& operator=(const Array& other) {
    // TODO: Avoid self assign

    // 1. Delete previous state
    ElgArrayDelete(m_start_, m_allocator_);

    // 2. Set the new state
    size_type n = other.m_end_ - other.m_start_;
    m_allocator_ = other.m_allocator_;
    m_start_ = ElgNewArray(T, n, m_allocator_);
    m_end_ = m_start_ + n;

    // 3. Assert we got memory
    ASSERT(m_pointer_ != NULL, "Memory allocation of FixedSizeArray failed");

    // 4. Copy the data
    for(size_type index = 0; index < n; ++index) {
      m_pointer_[index] = other.m_pointer_[index];
    }

    // 5. Return
    return *this;
  }

  reference operator[](size_type index) {
    return (m_pointer_ + index);
  }

  const_reference operator[](size_type index) const {
    return (m_pointer_ + index);
  }

// Member functions [Static arrays]
void assign(size_type count, const value_type& value) {
  if(count > capacity()) {
    // In ths case we need to reserve a new memory chunk
    ElgDeleteArray(m_storage_start_, m_allocator_);

    m_storage_start_ = ElgNewArray(T, count, m_allocator_);
    m_storage_end_ = m_storage_start_ + count;
    m_end_ = m_storage_start_;

    while(m_end_ != m_storage_end_) {
      *m_end_ = value;
      ++m_end_;
    } else if(count > size()) {
      m_end_ = m_storage_start_;
      while(count > 0) {
        --count;
      }
    }
  }
}

template<class InputIterator> void assign(InputIterator first, InputIterator last);

void fill(size_type count, const value_type& value);

T* data();
const T* data() const;

reference at(size_type index);
const_reference at(size_type index) const;

reference front();
const_reference front() const;

reference back();
const_reference back() const;
  
const_iterator begin() const;
iterator begin();

const_iterator cbegin() const;

iterator end();
const_iterator end() const;

const_iterator cend() const;

reverse_iterator rbegin();
const_reverse_iterator rbegin() const;

const_reverse_iterator crbegin() const;

const_reverse_iterator rend() const;
reverse_iterator rend();

const_reverse_iterator crend() const;

bool empty() const;

size_type size() const;

void swap(DynamicArray& other);

void clear();

// Member data [Fixed size arrys]
AllocatorType get_allocator() const;

void resize(size_type new_size);
void resize(size_type new_size, T value);  

private:
  allocator_type* m_allocator_;
  T* m_start_;
  T* m_end_;
};

// ------------------------------------------

template<typename T, typename AllocatorType>
inline bool operator==(const Array<T, AllocatorType>& lhs, const Array<T, AllocatorType>& rhs);

template<typename T, typename AllocatorType>
inline bool operator<(const Array<T, AllocatorType>& lhs, const Array<T, AllocatorType>& rhs);

template<typename T, typename AllocatorType>
inline bool operator!=(const Array<T, AllocatorType>& lhs, const Array<T, AllocatorType>& rhs);

template<typename T, typename AllocatorType>
inline bool operator>(const Array<T, AllocatorType>& lhs, const Array<T, AllocatorType>& rhs);

template<typename T, typename AllocatorType>
inline bool operator<=(const Array<T, AllocatorType>& lhs, const Array<T, AllocatorType>& rhs);

template<typename T, typename AllocatorType>
inline bool operator>=(const Array<T, AllocatorType>& lhs, const Array<T, AllocatorType>& rhs);

template<typename T, typename AllocatorType>
inline void swap(Array<T, AllocatorType>& lhs, Array<T, AllocatorType>& rhs);

}  // Containers
}  // Utilities
}  // Elg

#endif  // ELG_UTILITIES_ETL_FIXEDSIZEARRAY_H_
*/
