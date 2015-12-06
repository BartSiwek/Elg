/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */


////////////////////////////////////////////////////////////////////////////////////////////////////
// This is suppose to be like compile time array - finsih it someday
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
#ifndef ELG_UTILITIES_ETL_STATICARRAY_H_
#define ELG_UTILITIES_ETL_STATICARRAY_H_

#include<iterator>

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Containers/ArrayIterator.h"

namespace Elg {
namespace Utilities {
namespace Containers {

template<class T, elg_size_type N>
class StaticArray {
 public:
  // Typedefs
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef ArrayIterator<pointer, StaticArray> iterator;
  typedef ArrayIterator<const_pointer, StaticArray> const_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef elg_size_type size_type;
  typedef elg_pointer_diff difference_type;

  // Constructor
  StaticArray() {
    for(size_type index = 0; index < N; ++index) {
      new(m_array_ + index) T();
    }
  }

  StaticArray(const value_type& value) {
    for(size_type index = 0; index < N; ++index) {
      new(m_array_ + index) T(value);
    }
  }

  StaticArray(const StaticArray& other) {
    for(size_type index = 0; index < N; ++index) {
      new(m_array_ + index) T(other.m_array_[index]);
    }
  }

  // Destructor
  ~StaticArray() {
  }

  // Operators
  StaticArray& operator=(const StaticArray& other) {
    for(size_type index = 0; index < N; ++index) {
      new(m_array_ + index) T(other.m_array_[index]);
    }
  }

  reference operator[](size_type index) {
    return m_array_[index];
  }

  const_reference operator[](size_type index) const {
    return m_array_[index];
  }
 
  // Member functions
  void assign(const value_type& value) {
    for(size_type index = 0; index < N; ++index) {
      new(m_array_ + index) T(value);
    }
  }

  void fill(const value_type& value) {
    assign(value);
  }

  pointer data() {
    return m_array_;
  }

  const_pointer data() const {
    return m_array_;
  }

  reference at(size_type index) {
    return m_array_[index];
  }
      
  const_reference at(size_type index) const {
    return m_array_[index];
  }

  reference front() {
    return m_array_[0];
  }

  const_reference front() const {
    return m_array_[0];
  }

  reference back() {
    return m_array_[N-1];
  }
      
  const_reference back() const {
    return m_array_[N-1];
  }

  iterator begin() {
    return iterator(m_array_);
  }

  const_iterator begin() const {
    return const_iterator(m_array_);
  }

  const_iterator cbegin() const {
    return const_iterator(m_array_);
  }

  iterator end() {
    return iterator(m_array_ + N);
  }
      
  const_iterator end() const {
    return const_iterator(m_array_ + N);
  }

  const_iterator cend() const {
    return const_iterator(m_array_ + N);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(cend());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  const_reverse_iterator crend() const {
    return const_reverse_iterator(cbegin());
  }

  bool empty() const {
    return (N == 0);
  }

  size_type size() const {
    return N;
  }

  void swap(StaticArray& other) {
    for(size_type index = 0; index < N; ++index) {
      swap(m_array_[index], other.m_array_[index]);
    }
  }

  void clear() {
    for(size_type index = 0; index < N; ++index) {
      new(m_array_ + index) T();
    }
  }

 private:
  T m_array_[N];
};

// Binary operators
template<typename T, elg_size_type N>
inline bool operator==(const StaticArray<T, N>& lhs, const StaticArray<T, N>& rhs) {
  for(StaticArray<T, N>::size_type index = 0; index < N; ++index) {
    if(lhs[index] != rhs[index]) {
      return false;
    }
  }
  return true;
}

template<typename T, elg_size_type N>
inline bool operator<(const StaticArray<T, N>& lhs, const StaticArray<T, N>& rhs) {
  for(StaticArray<T, N>::size_type index = 0; index < N; ++index) {
    if(lhs[index] >= rhs[index]) {
      return false;
    }
  }
  return true;
}

template<typename T, elg_size_type N>
inline bool operator!=(const StaticArray<T, N>& lhs, const StaticArray<T, N>& rhs) {
  return !(lhs == rhs);
}

template<typename T, elg_size_type N>
inline bool operator>(const StaticArray<T, N>& lhs, const StaticArray<T, N>& rhs) {
  return (rhs < lhs);
}

template<typename T, elg_size_type N>
inline bool operator<=(const StaticArray<T, N>& lhs, const StaticArray<T, N>& rhs) {
  returh !(rhs < lhs);
}

template<typename T, elg_size_type N>
inline bool operator>=(const StaticArray<T, N>& lhs, const StaticArray<T, N>& rhs) {
  return !(lhs < rhs)
}

// Utility functions
template<elg_size_type Index, typename T, elg_size_type N>
T& get(StaticArray<T, N>& a) {
  return a[Index];
}

template<elg_size_type Index, class T, elg_size_type N>
const T& get(const StaticArray<T, N>& a) {
  return a[Index];
}

template<typename T, elg_size_type N>
inline void swap(StaticArray<T, N>& x, StaticArray<T, N>& y) {
  x.swap(y);
}

}  // Containers
}  // Utilities
}  // Elg

#endif  // ELG_UTILITIES_ETL_STATICARRAY_H_
*/
