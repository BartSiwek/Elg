/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 * Based on EASTL (https://github.com/paulhodge/EASTL) - copyright information follows.
 */

/*
 * Copyright (C) 2005,2009-2010 Electronic Arts, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Electronic Arts, Inc. ("EA") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY ELECTRONIC ARTS AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ELECTRONIC ARTS OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ELG_UTILITIES_ETL_DYNAMICARRAY_H_
#define ELG_UTILITIES_ETL_DYNAMICARRAY_H_

#include <new>

#include "Elg/Utilities/Types.h"
#include "Elg/Memory/Memory.h"
#include "Elg/Utilities/ETL/TypeTraits.h"
#include "Elg/Utilities/ETL/Iterator.h"
#include "Elg/Utilities/ETL/Algorithm.h"
#include "Elg/Utilities/ETL/Memory.h"

namespace Elg {
namespace Utilities {
namespace Etl {

template<typename T, typename AllocatorType>
class DynamicArrayStorage {
 public:
  // Typedefs
  typedef T                value_type;
  typedef AllocatorType    allocator_type;
  typedef T*               pointer;
  typedef const T*         const_pointer;
  typedef T&               reference;
  typedef const T&         const_reference;
  typedef elg_pointer_diff difference_type;
  typedef elg_size_type    size_type;

  // Consts
  static const size_type NPOS      = static_cast<size_type>(-1);
  static const size_type MAX_SIZE  = static_cast<size_type>(-2);
  static const size_type ALIGNMENT = ELG_ALIGNOF(T);

  // Constructors
  explicit DynamicArrayStorage(allocator_type* allocator)
      : m_allocator_(allocator), m_begin_(NULL), m_capacity_end_(NULL), m_end_(NULL) {
  }

  DynamicArrayStorage(size_type n, allocator_type* allocator)
      : m_allocator_(allocator), m_begin_(NULL), m_capacity_end_(NULL), m_end_(NULL) {
    m_begin_ = DoAllocate(n);
    m_capacity_end_ = m_begin_ + n;
    m_end_ = m_begin_;
  }

  // Destructor
  ~DynamicArrayStorage() {
    ElgFree(m_begin_, m_allocator_);
  }

  // Member functions
  allocator_type* get_allocator() {
    return m_allocator_;
  }

  const allocator_type* get_allocator() const {
    return m_allocator_;
  }

  void set_allocator(allocator_type* allocator) {
    m_allocator_ = allocator;
  }

 protected:
  // Member functions
  pointer DoAllocate(size_type n) {
    if (n > 0) {
      return static_cast<T*>(ElgMalloc(n * sizeof(T), ALIGNMENT, m_allocator_));
    } else {
      return NULL;
    }
  }

  void DoFree(T* ptr) {
    ElgFree(ptr, m_allocator_);
  }

  static size_type GetNewCapacity(size_type currentCapacity) {
    return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
  }

  // Data members
  AllocatorType* m_allocator_;
  T* m_begin_;
  T* m_end_;
  T* m_capacity_end_;
};

// Array class
template<typename T, typename AllocatorType>
class DynamicArray : public DynamicArrayStorage<T, AllocatorType> {
 public:
  // Typedefs
  typedef DynamicArrayStorage<T, AllocatorType> base_type;
  typedef DynamicArray<T, AllocatorType> this_type;

  typedef typename base_type::value_type                        value_type;
  typedef typename base_type::pointer                           pointer;
  typedef typename base_type::const_pointer                     const_pointer;
  typedef typename base_type::reference                         reference;
  typedef typename base_type::const_reference                   const_reference;
  typedef typename base_type::pointer                           iterator;
  typedef typename base_type::const_pointer                     const_iterator;
  typedef Elg::Utilities::Etl::reverse_iterator<iterator>       reverse_iterator;
  typedef Elg::Utilities::Etl::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename base_type::size_type                         size_type;
  typedef typename base_type::difference_type                   difference_type;
  typedef typename base_type::allocator_type                    allocator_type;

  // Usings
  using base_type::m_allocator_;
  using base_type::m_begin_;
  using base_type::m_capacity_end_;
  using base_type::m_end_;
  using base_type::NPOS;
  using base_type::DoAllocate;
  using base_type::DoFree;
  using base_type::GetNewCapacity;

  // Constructors
  explicit DynamicArray(allocator_type* allocator)
      : DynamicArrayStorage<T, AllocatorType>(allocator) {
  }

  DynamicArray(size_type n, allocator_type* allocator)
      : DynamicArrayStorage<T, AllocatorType>(n, allocator) {
    Elg::Utilities::Etl::uninitialized_fill_n_ptr(m_begin_, n, value_type());
    m_capacity_end_ = m_begin_ + n;
  }

  DynamicArray(size_type n, const value_type& value, allocator_type* allocator)
      : DynamicArrayStorage<T, AllocatorType>(n, allocator) {
    Elg::Utilities::Etl::uninitialized_fill_n_ptr(m_begin_, n, value);
    m_capacity_end_ = m_begin_ + n;
  }

  DynamicArray(const DynamicArray& other)
      : base_type(other.size(), other.m_allocator_) {
    m_end_ = Elg::Utilities::Etl::uninitialized_copy_ptr(other.m_begin_, other.m_end_,
                                                              m_begin_);
  }

  template<typename InputIterator>
  DynamicArray(InputIterator first, InputIterator last, allocator_type* allocator)
      : base_type(allocator) {
    DoInit(first, last, Elg::Utilities::Etl::is_integral<InputIterator>());
  }

  // Destructor
  ~DynamicArray() {
    DoDestroyValues(m_begin_, m_end_);
  }

  // Operators
  DynamicArray& operator=(const DynamicArray& other) {
    if (&other != this) {
      const size_type n = other.size();

      if (n > static_cast<size_type>(m_capacity_end_ - m_begin_)) {  // If n > capacity ...
        pointer const new_data = DoRealloc(n, other.m_begin_, other.m_end_);
        DoDestroyValues(m_begin_, m_end_);
        DoFree(m_begin_);
        m_begin_ = new_data;
        m_capacity_end_ = m_begin_ + n;
      } else if (n > size_type(m_end_ - m_begin_)) {  // If size < n <= capacity ...
        Elg::Utilities::Etl::copy(other.m_begin_, other.m_begin_ + (m_end_ - m_begin_), m_begin_);
        Elg::Utilities::Etl::uninitialized_copy_ptr(other.m_begin_ + (m_end_ - m_storage_start),
                                                    other.m_end_, m_end_);
      } else {  // else n <= size
        iterator const position = Elg::Utilities::Etl::copy(other.m_end_, other.m_end_, m_begin_);
        DoDestroyValues(position, m_end_);
      }
      m_end_ = m_end_ + n;
    }
    return *this;
  }

  reference operator[](size_type index) {
    ASSERT(n < static_cast<size_type>(m_end_ - m_begin_), "vector::operator[] - out of range");
    return *(m_begin_ + n);
  }

  const_reference operator[](size_type n) const {
    ASSERT(n < static_cast<size_type>(m_end_ - m_begin_), "vector::operator[] - out of range");
    return *(m_begin_ + n);
  }

  // Member functions [Static arrays]
  void assign(size_type count, const value_type& value) {
    DoAssignValues(count, value);
  }

  template<typename InputIterator>
  void assign(InputIterator first, InputIterator last) {
    DoAssign(first, last, Elg::Utilities::Etl::is_integral<InputIterator>());
  }

  void fill(size_type count, const value_type& value) {
    DoAssignValues(count, value);
  }

  pointer data() {
    return m_begin_;
  }

  const_pointer data() const {
    return m_begin_;
  }

  reference at(size_type index) {
    ASSERT(n < static_cast<size_type>(m_end_ - m_begin_), "vector::at - out of range");
    return *(m_begin_ + index);
  }

  const_reference at(size_type n) const {
    ASSERT(n < static_cast<size_type>(m_end_ - m_begin_), "vector::at - out of range");
    return *(m_begin_ + index);
  }

  reference front() {
    ASSERT(m_begin_ < m_end_, "vector::front - empty vector");
    return *m_begin_;
  }

  const_reference front() const {
    ASSERT(m_begin_ < m_end_, "vector::front - empty vector");
    return *m_begin_;
  }

  reference back() {
    ASSERT(m_begin_ < m_end_, "vector::back - empty vector");
    return *(m_end_ - 1);
  }

  const_reference back() const {
    ASSERT(m_begin_ < m_end_, "vector::back - empty vector");
    return *(m_end_ - 1);
  }

  iterator begin() {
    return iterator(m_begin_);
  }

  const_iterator begin() const {
    return const_iterator(m_begin_);
  }

  const_iterator cbegin() const {
    return const_iterator(m_begin_);
  }

  iterator end() {
    return iterator(m_end_);
  }

  const_iterator end() const {
    return const_iterator(m_end_);
  }

  const_iterator cend() const {
    return const_iterator(m_end_);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() {
    reverse_iterator(begin());
  }
  const_reverse_iterator rend() const {
    const_reverse_iterator(begin());
  }

  const_reverse_iterator crend() const {
    const_reverse_iterator(begin());
  }

  bool empty() const {
    return (m_begin_ == m_end_);
  }

  size_type size() const {
    return static_cast<size_type>(m_end_ - m_begin_);
  }

  void swap(DynamicArray& other) {
    if (m_allocator_ == other.m_allocator_) {  // If allocators are equivalent...
      // We leave m_allocator_ as-is.
      swap(m_begin_, other.m_begin_);
      swap(m_capacity_end_, other.m_capacity_end_);
      swap(m_end_, other.m_end_);
    } else {  // else swap the contents.
      const DynamicArray temp(*this);  // Can't call swap because that would itself call this member swap function
      *this = other;
      other = temp;
    }
  }

  void clear() {
    DoDestroyValues(m_begin_, m_end_);
    m_end_ = m_begin_;
  }

  void reset() {
    // The reset function is a special extension function which unilaterally resets the container to an empty state
    // without freeing the memory of the contained objects. This is useful for very quickly tearing down a container
    // built into scratch memory.
    m_begin_ = m_capacity_end_ = m_end_ = NULL;
  }

  // Member data [Fixed size arrays]
  void resize(size_type n, const value_type& value) {
    if (n > static_cast<size_type>(m_end_ - m_begin_)) {  // We expect that more often than not, upsizes.
      insert(m_end_, n - (static_cast<size_type>(m_end_ - m_begin_)), value);
    } else {
      erase(m_begin_ + n, m_end_);
    }
  }

  void resize(size_type n) {
    if (n > static_cast<size_type>(m_end_ - m_begin_)) {  // We expect that more often than not, upsizes.
      insert(m_end_, n - (static_cast<size_type>(m_end_ - m_begin_)), value_type());
    } else {
      erase(m_begin_ + n, m_end_);
    }
  }

  // Member data [Dynamic arrays]
  size_type capacity() const {
    return static_cast<size_type>(m_capacity_end_ - m_begin_);
  }

  void reserve(size_type n) {
    // If the user wants to reduce the reserved memory, there is the set_capacity function.
    if (n > static_cast<size_type>(m_capacity_end_ - m_begin_)) {  // If n > capacity ...
      pointer const new_data = DoRealloc(n, m_begin_, m_end_);
      DoDestroyValues(m_begin_, m_end_);
      DoFree(m_begin_);

      const difference_type prev_size = m_end_ - m_begin_;
      m_begin_ = new_data;
      m_capacity_end_ = m_begin_ + n;
      m_end_ = new_data + prev_size;
    }
  }

  void set_capacity(size_type n = base_type::npos) {
    if ((n == npos) || (n <= static_cast<size_type>(m_end_ - m_begin_))) {  // If new capacity <= size...
      if (n < static_cast<size_type>(m_end_ - m_begin_)) {
        resize(n);
      }

      DynamicArray temp(*this);  // This is the simplest way to accomplish this, and it is as efficient as any other.
      swap(temp);
    } else {  // Else new capacity > size
      pointer const new_data = DoRealloc(n, m_begin_, m_end_);
      DoDestroyValues(m_begin_, m_end_);
      DoFree(m_begin_);

      const difference_type prev_size = m_end_ - m_begin_;
      m_begin_ = new_data;
      m_capacity_end_ = m_begin_ + n;
      m_end_ = new_data + prev_size;
    }
  }

  void push_back(const value_type& value) {
    if (m_end_ < m_capacity_end_) {
      ::new(m_end_++) value_type(value);
    } else {
      DoInsertValue(m_end_, value);
    }
  }

  reference push_back() {
    if (m_end_ < m_capacity_end_) {
      ::new(m_end_++) value_type();
    } else {  // Note that in this case we create a temporary, which is less desirable.
      DoInsertValue(m_end_, value_type());
    }

    return *(m_end_ - 1);  // Same as return back();
  }

  void* push_back_uninitialized() {
    if (m_end_ == m_capacity_end_) {
      const size_type new_size = static_cast<size_type>(m_end_ - m_begin_) + 1;
      reserve(new_size);
    }

    return m_end_++;
  }

  void pop_back() {
    ASSERT(m_begin_ < m_end_, "vector::pop_back - empty vector");
    --m_end_;
    m_end_->~value_type();
  }

  iterator insert(iterator position, value_type&& value) {
    iterator const ret = insert(position, value_type());
    *ret = value;
    return ret;
  }

  iterator insert(iterator position, const value_type& value) {
    DoInsertValues(position, n, value);
  }

  void insert(iterator position, size_type n, const value_type& value) {
    ASSERT((m_begin_ <= position) && (position <= m_end_), "vector::insert - invalid position");

    const difference_type n = position - m_begin_;  // Save this because we might reallocate.

    if ((m_end_ == m_capacity_end_) || (position != m_end_)) {
      DoInsertValue(position, value);
    } else {
      ::new(m_end_++) value_type(value);
    }

    return m_end_ + n;
  }

  template<typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    DoInsert(position, first, last, Elg::Utilities::Etl::is_integral<InputIterator>());
  }

  iterator erase(iterator position) {
    ASSERT((m_begin_ <= position) && (position < m_end_), "vector::erase - invalid position");

    if ((position + 1) < m_end_) {
      Elg::Utilities::Etl::copy(position + 1, m_end_, position);
    }

    --m_end_;
    m_end_->~value_type();
    return position;
  }

  iterator erase(iterator first, iterator last) {
    ASSERT(
      (m_begin_ <= first) && (first <= m_end_) &&
      (m_begin_ <= last) && (last <= m_end_) &&
      (first <= last),
      "vector::erase - invalid position");

    // Reference implementation, known to be correct:
    iterator const position = Elg::Utilities::Etl::copy(last, m_end_, first);
    DoDestroyValues(position, m_end_);
    m_end_ -= (last - first);

    return first;
  }

  reverse_iterator erase(reverse_iterator position) {
    return reverse_iterator(erase((++position).base()));
  }

  reverse_iterator erase(reverse_iterator first, reverse_iterator last) {
    return reverse_iterator(erase((++last).base(), (++first).base()));
  }

  bool validate() const {
    if (m_end_ < m_begin_) {
      return false;
    }
    if (m_capacity_end_ < m_end_) {
      return false;
    }
    return true;
  }

  int validate_iterator(const_iterator i) const {
    if (i >= m_begin_) {
      if (i < m_end_) {
        return (ISF_VALID | ISF_CURRENT| ISF_CAN_DEREFERENCE);
      }
      if (i <= m_end_) {
        return (ISF_VALID | ISF_CURRENT);
      }
    }
    return ISF_NONE;
  }

 protected:
  // These functions do the real work of maintaining the vector. You will notice
  // that many of them have the same name but are specialized on iterator_tag
  // (iterator categories). This is because in these cases there is an optimized
  // implementation that can be had for some cases relative to others. Functions
  // which aren't referenced are neither compiled nor linked into the application.

  template<typename ForwardIterator>
  pointer DoRealloc(size_type n, ForwardIterator first, ForwardIterator last) {
    T* const p = DoAllocate(n);
    Elg::Utilities::Etl::uninitialized_copy_ptr(first, last, p);
    return p;
  }

  template<typename Integer>
  void DoInit(Integer n, Integer value, Elg::Utilities::Etl::true_type /* is_integer */) {
    m_begin_ = DoAllocate(static_cast<size_type>(n));
    m_capacity_end_ = m_begin_ + n;
    m_end_ = m_capacity_end_;
    Elg::Utilities::Etl::uninitialized_fill_n_ptr<value_type, Integer>(m_begin_, n, value);
  }

  template<typename InputIterator>
  void DoInit(InputIterator first, InputIterator last, Elg::Utilities::Etl::false_type /* is_integer */) {
    typedef typename Elg::Utilities::Etl::iterator_traits<InputIterator>::iterator_category IteratorCategory;
    DoInitFromIterator(first, last, IteratorCategory());
  }

  template<typename InputIterator>
  void DoInitFromIterator(InputIterator first, InputIterator last,
                          Elg::Utilities::Etl::input_iterator_tag /* tag */) {
    for (; first < last; ++first) {  // InputIterators by definition actually only allow you to iterate through them
      push_back(*first);            // once. Thus the standard *requires* that we do this (inefficient)
    }                               // implementation. Luckily, InputIterators are in practice almost never used, so
  }                                 // this code will likely never get executed.

  template<typename ForwardIterator>
  void DoInitFromIterator(ForwardIterator first, ForwardIterator last,
                          Elg::Utilities::Etl::forward_iterator_tag /* tag */) {
    const size_type n = static_cast<size_type>(Elg::Utilities::Etl::distance(first, last));
    m_begin_  = DoAllocate(n);
    m_capacity_end_ = m_begin_ + n;
    m_end_ = m_capacity_end_;
    Elg::Utilities::Etl::uninitialized_copy_ptr(first, last, m_begin_);
  }

  void DoDestroyValues(pointer first, pointer last) {
    for (; first < last; ++first) {
      first->~value_type();
    }
  }

  template<typename Integer>
  void DoAssign(Integer n, Integer value, true_type /* is_integer */) {
    DoAssignValues(static_cast<size_type>(n), static_cast<value_type>(value));
  }

  template<typename InputIterator>
  void DoAssign(InputIterator first, InputIterator last, false_type /* is_integer */) {
    typedef typename Elg::Utilities::Etl::iterator_traits<InputIterator>::iterator_category IteratorCategory;
    DoAssignFromIterator(first, last, IteratorCategory());
  }

  void DoAssignValues(size_type n, const value_type& value) {
    if (n > static_cast<size_type>(m_capacity_end_ - m_begin_)) {  // If n > capacity ...
      DynamicArray temp(n, value, m_allocator_);  // We have little choice but to reallocate with new memory.
      swap(temp);
    } else if (n > static_cast<size_type>(m_end_ - m_begin_)) {  // If n > size ...
      Elg::Utilities::Etl::fill(m_begin_, m_end_, value);
      Elg::Utilities::Etl::uninitialized_fill_n_ptr(m_end_, n - static_cast<size_type>(m_end_ - m_begin_), value);
      m_end_ += n - static_cast<size_type>(m_end_ - m_begin_);
    } else {  // else 0 <= n <= size
      Elg::Utilities::Etl::fill_n(m_begin_, n, value);
      erase(m_begin_ + n, m_end_);
    }
  }

  template<typename InputIterator>
  void DoAssignFromIterator(InputIterator first, InputIterator last,
                            Elg::Utilities::Etl::input_iterator_tag /* tag */) {
    iterator position(m_begin_);

    while ((position != m_end_) && (first != last)) {
      *position = *first;
      ++first;
      ++position;
    }

    if (first == last) {
      erase(position, m_end_);
    } else {
      insert(m_end_, first, last);
    }
  }

  template<typename RandomAccessIterator>
  void DoAssignFromIterator(RandomAccessIterator first, RandomAccessIterator last,
                            Elg::Utilities::Etl::random_access_iterator_tag /* tag */) {
    const size_type n = static_cast<size_type>(Elg::Utilities::Etl::distance(first, last));

    if (n > size_type(m_capacity_end_ - m_begin_)) {  // If n > capacity ...
      pointer const new_data = DoRealloc(n, first, last);
      DoDestroyValues(m_begin_, m_end_);
      DoFree(m_begin_);

      m_begin_ = new_data;
      m_end_ = m_begin_ + n;
      m_capacity_end_ = m_end_;
    } else if (n <= size_type(m_end_ - m_begin_)) {  // If n <= size ...
      pointer const new_end = Elg::Utilities::Etl::copy(first, last, m_begin_);  // We don't have to worry
      DoDestroyValues(new_end, m_end_);                                             // about overlaps since we're
      m_end_ = new_end;                                                             // coping into m_begin_
    } else {  // else size < n <= capacity
      RandomAccessIterator position = first + (m_end_ - m_begin_);
      Elg::Utilities::Etl::copy(first, position, m_begin_);                            // Same as above
      m_end_ = Elg::Utilities::Etl::uninitialized_copy_ptr(position, last, m_end_);
    }
  }

  template<typename Integer>
  void DoInsert(iterator position, Integer n, Integer value, true_type /* is_integer */) {
    DoInsertValues(position, static_cast<size_type>(n), static_cast<value_type>(value));
  }

  template<typename InputIterator>
  void DoInsert(iterator position, InputIterator first, InputIterator last, false_type /* is_integer */) {
    typedef typename Elg::Utilities::Etl::iterator_traits<InputIterator>::iterator_category IteratorCategory;
    DoInsertFromIterator(position, first, last, IteratorCategory());
  }

  template<typename InputIterator>
  void DoInsertFromIterator(iterator position, InputIterator first, InputIterator last
                            Elg::Utilities::Etl::input_iterator_tag /* tag */) {
    for (; first != last; ++first, ++position) {
      position = insert(position, *first);
    }
  }

  template<typename BidirectionalIterator>
  void DoInsertFromIterator(iterator position, BidirectionalIterator first, BidirectionalIterator last,
                            Elg::Utilities::Etl::bidirectional_iterator_tag /* tag */) {
    ASSERT((m_begin_ <= position) && (position <= m_end_), "vector::insert - invalid position");

    if (first != last) {
      const size_type n = static_cast<size_type>(Elg::Utilities::Etl::distance(first, last));

      if (n <= size_type(m_capacity_end_ - m_end_)) {  // If n fits within the existing capacity...
        const size_type extra = static_cast<size_type>(m_end_ - position);
        const pointer   data_end = m_end_;

        if (n < extra) {
          Elg::Utilities::Etl::uninitialized_copy_ptr(m_end_ - n, m_end_, m_end_);
          m_end_ += n;
          // We need copy_backward because of potential overlap issues.
          Elg::Utilities::Etl::copy_backward(position, data_end - n, data_end);
          Elg::Utilities::Etl::copy(first, last, position);
        } else {
          BidirectionalIterator temp = first;
          Elg::Utilities::Etl::advance(temp, extra);
          Elg::Utilities::Etl::uninitialized_copy_ptr(temp, last, m_end_);
          m_end_ += n - extra;
          Elg::Utilities::Etl::uninitialized_copy_ptr(position, data_end, m_end_);
          m_end_ += extra;
          Elg::Utilities::Etl::copy_backward(first, temp, position + extra);
        }
      } else {  // else we need to expand our capacity.
        const size_type prev_size = static_cast<size_type>(m_end_ - m_begin_);
        const size_type grow_size = GetNewCapacity(prev_size);
        const size_type new_size = grow_size > (prev_size + n) ? grow_size : (prev_size + n);
        pointer const new_data = DoAllocate(new_size);

        // Exceptions?
        pointer new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(m_begin_, position, new_data);
        new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(first, last, new_end);
        new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(position, m_end_, new_end);

        DoDestroyValues(m_begin_, m_end_);
        DoFree(m_begin_, static_cast<size_type>(m_capacity_end_ - m_begin_));

        m_begin_ = new_data;
        m_end_ = new_end;
        m_capacity_end_ = new_data + new_size;
      }
    }
  }

  void DoInsertValues(iterator position, size_type n, const value_type& value) {
    ASSERT((m_begin_ <= position) && (position <= m_end_), "vector::insert - invalid position");

    if (n <= static_cast<size_type>(m_capacity_end_ - m_begin_)) {  // If n is <= capacity...
      if (n > 0) {  // To do: See if there is a way we can eliminate this 'if' statement.
        // To consider: Make this algorithm work more like DoInsertValue whereby a pointer to value is used.
        const value_type temp = value;
        const size_type extra = static_cast<size_type>(m_end_ - position);
        const pointer data_end = m_end_;

        if (n < extra) {
          Elg::Utilities::Etl::uninitialized_copy_ptr(m_end_ - n, m_end_, m_end_);
          m_end_ += n;
          // We need copy_backward because of potential overlap issues.
          Elg::Utilities::Etl::copy_backward(position, data_end - n, data_end);
          Elg::Utilities::Etl::fill(position, position + n, temp);
        } else {
          Elg::Utilities::Etl::uninitialized_fill_n_ptr(m_end_, n - extra, temp);
          m_end_ += n - extra;
          Elg::Utilities::Etl::uninitialized_copy_ptr(position, data_end, m_end_);
          m_end_ += extra;
          Elg::Utilities::Etl::fill(position, data_end, temp);
        }
      }
    } else {  // else n > capacity
      const size_type prev_size = size_type(m_end_ - m_begin_);
      const size_type grow_size = GetNewCapacity(prev_size);
      const size_type new_size = grow_size > (prev_size + n) ? grow_size : (prev_size + n);
      pointer const new_data = DoAllocate(new_size);

      // Exceptions?
      pointer new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(m_begin_, position, new_data);
      Elg::Utilities::Etl::uninitialized_fill_n_ptr(new_end, n, value);
      new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(position, m_end_, new_end + n);

      DoDestroyValues(m_begin_, m_end_);
      DoFree(m_begin_, static_cast<size_type>(m_capacity_end_ - m_begin_));

      m_begin_ = new_data;
      m_end_ = new_end;
      m_capacity_end_ = new_data + new_size;
    }
  }

  void DoInsertValue(iterator position, const value_type& value) {
    ASSERT((m_begin_ <= position) && (position <= m_end_), "vector::insert - invalid position");

    if (m_end_ != m_capacity_end_) {  // If size < capacity ...
      // We don't call this function unless position is less than end, and the code directly below relies on this.
      ASSERT(position < m_end_, "vector::insert - invalid position (must be less than end)");

      // We need to take into account the possibility that value may come from within the vector itself.
      const T* value_pointer = &value;
      if ((value_pointer >= position) && (value_pointer < m_end_)) {  // If value comes from range to be moved...
        ++value_pointer;
      }
      ::new(m_end_) value_type(*(m_end_ - 1));
      // We need copy_backward because of potential overlap issues.
      Elg::Utilities::Etl::copy_backward(position, m_end_ - 1, m_end_);
      *position = *value_pointer;
      ++m_end_;
    } else {  // else (size == capacity)
      const size_type prev_size = size_type(m_end_ - m_begin_);
      const size_type new_size = GetNewCapacity(prev_size);
      pointer const new_data = DoAllocate(new_size);

      // Exceptions???
      pointer new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(m_begin_, position, new_data);
      ::new(new_end) value_type(value);
      new_end = Elg::Utilities::Etl::uninitialized_copy_ptr(position, m_end_, ++new_end);

      DoDestroyValues(m_begin_, m_end_);
      DoFree(m_begin_, static_cast<size_type>(m_capacity_end_ - m_begin_));

      m_begin_ = new_data;
      m_end_ = new_end;
      m_capacity_end_ = new_data + new_size;
    }
  }
};

template<typename T, typename AllocatorType>
bool operator!=(const vector<T, AllocatorType>& lhs, const vector<T, AllocatorType>& rhs) {
  return ((a.size() == b.size()) && Elg::Utilities::Etl::equal(a.begin(), a.end(), b.begin()));
}

template<typename T, typename AllocatorType>
bool operator<(const vector<T, AllocatorType>& lhs, const vector<T, AllocatorType>& rhs) {
  return ((a.size() != b.size()) || !Elg::Utilities::Etl::equal(a.begin(), a.end(), b.begin()));
}

template<typename T, typename AllocatorType>
bool operator<=(const vector<T, AllocatorType>& lhs, const vector<T, AllocatorType>& rhs) {
  return Elg::Utilities::Etl::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template<typename T, typename AllocatorType>
bool operator==(const vector<T, AllocatorType>& lhs, const vector<T, AllocatorType>& rhs) {
  return b < a;
}

template<typename T, typename AllocatorType>
bool operator>(const vector<T, AllocatorType>& lhs, const vector<T, AllocatorType>& rhs) {
  return !(b < a);
}

template<typename T, typename AllocatorType>
bool operator>=(const vector<T, AllocatorType>& lhs,    // NOLINT(build/include_what_you_use)
                const vector<T, AllocatorType>& rhs) {  // NOLINT(build/include_what_you_use)
  return !(a < b);
}

template<typename T, typename AllocatorType>
friend void swap(DynamicArray<T, AllocatorType>& lhs,  // NOLINT(build/include_what_you_use)
                 DynamicArray<T, AllocatorType>& rhs) {
  a.swap(b);
}
}  // Etl
}  // Utilities
}  // Elg

#endif  // ELG_UTILITIES_ETL_DYNAMICARRAY_H_
