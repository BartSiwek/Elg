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

#ifndef ELG_UTILITIES_ETL_ITERATOR_H_
#define ELG_UTILITIES_ETL_ITERATOR_H_

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"

namespace Elg {
namespace Utilities {
namespace Etl {

// iterator_status_flag
//   Defines the validity status of an iterator. This is primarily used for iterator validation in debug builds.
//   These are implemented as OR-able flags (as opposed to mutually exclusive values) in order to deal with
//   the nature of iterator status. In particular, an iterator may be valid but not dereferencable, as in the case
//   with an iterator to container end(). An iterator may be valid but also dereferencable, as in the case with an
//   iterator to container begin().
//
enum iterator_status_flag {
  ISF_NONE            = 0x00,  // This is called none and not called invalid because it is not strictly the opposite
                                // of invalid.
  ISF_VALID           = 0x01,  // The iterator is valid, which means it is in the range of [begin, end].
  ISF_CURRENT         = 0x02,  // The iterator is valid and points to the same element it did when created. For
                                // example, if an iterator points to vector::begin() but an element is inserted at
                                // the front, the iterator is valid but not current. Modification of elements in
                                // place do not make iterators non-current.
  ISF_CAN_DEREFERENCE = 0x04   // The iterator is dereferencable, which means it is in the range of [begin, end).
                                // It may or may not be current.
};

// The following declarations are taken directly from the C++ standard document.
//   input_iterator_tag, etc.
//   iterator
//   iterator_traits
//   reverse_iterator

// Iterator categories
//   Every iterator is defined as belonging to one of the iterator categories that we define here. These categories
//   come directly from the C++ standard.
struct input_iterator_tag {
};

struct output_iterator_tag {
};

struct forward_iterator_tag : public input_iterator_tag {
};

struct bidirectional_iterator_tag : public forward_iterator_tag {
};

struct random_access_iterator_tag : public bidirectional_iterator_tag {
};

struct contiguous_iterator_tag : public random_access_iterator_tag {  // Extension to the C++ standard.
};                                                                    // Contiguous ranges are more than random
                                                                      // access, they are physically contiguous.

// iterator
template<typename Category, typename T, typename Distance = elg_pointer_diff, typename Pointer = T*,
         typename Reference = T&>
struct iterator {
  typedef Category  iterator_category;
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
};

// iterator_traits
template<typename Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
};

template<typename T>
struct iterator_traits<T*> {
  typedef Elg::Utilities::Etl::random_access_iterator_tag iterator_category;
  typedef T                                               value_type;
  typedef elg_pointer_diff                                difference_type;
  typedef T*                                              pointer;
  typedef T&                                              reference;
};

template<typename T>
struct iterator_traits<const T*> {
  typedef Elg::Utilities::Etl::random_access_iterator_tag iterator_category;
  typedef T                                               value_type;
  typedef elg_pointer_diff                                difference_type;
  typedef const T*                                        pointer;
  typedef const T&                                        reference;
};

// reverse_iterator
//   From the C++ standard:
//     Bidirectional and random access iterators have corresponding reverse iterator adaptors that iterate through
//     the data structure in the opposite direction. They have the same signatures as the corresponding iterators.
//     The fundamental relation between a reverse iterator and its corresponding iterator i is established by the
//     identity: &*(reverse_iterator(i)) == &*(i - 1).
//     This mapping is dictated by the fact that while there is always a pointer past the end of an array, there
//     might not be a valid pointer before the beginning of an array.
//
template<typename Iterator>
class reverse_iterator : public iterator<typename Elg::Utilities::Etl::iterator_traits<Iterator>::iterator_category,
                                         typename Elg::Utilities::Etl::iterator_traits<Iterator>::value_type,
                                         typename Elg::Utilities::Etl::iterator_traits<Iterator>::difference_type,
                                         typename Elg::Utilities::Etl::iterator_traits<Iterator>::pointer,
                                         typename Elg::Utilities::Etl::iterator_traits<Iterator>::reference> {
 public:
  typedef Iterator                                                                 iterator_type;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::pointer         pointer;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::reference       reference;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::difference_type difference_type;

  reverse_iterator()     // It's important that we construct mIterator, because if Iterator is a pointer, there's a
      : m_iterator_() {  // difference between doing it and not.
  }

  explicit reverse_iterator(iterator_type i)
      : m_iterator_(i) {
  }

  reverse_iterator(const reverse_iterator& ri)
      : m_iterator_(ri.m_iterator_) {
  }

  template<typename U>
  reverse_iterator(const reverse_iterator<U>& ri)  // NOLINT(runtime/explicit)
      : m_iterator_(ri.base()) {
  }

  // This operator= isn't in the standard, but the the C++  library working group has tentatively approved it, as it
  // allows const and non-const reverse_iterators to interoperate.
  template<typename U>
  reverse_iterator<Iterator>& operator=(const reverse_iterator<U>& ri) {
    m_iterator_ = ri.base();
    return *this;
  }

  iterator_type base() const {
    return m_iterator_;
  }

  reference operator*() const {
    iterator_type i(m_iterator_);
    return *--i;
  }

  pointer operator->() const {
    return &(operator*());
  }

  reverse_iterator& operator++() {
    --m_iterator_;
    return *this;
  }

  reverse_iterator operator++(int /* postfix */) {
    reverse_iterator ri(*this);
    --m_iterator_;
    return ri;
  }

  reverse_iterator& operator--() {
    ++m_iterator_;
    return *this;
  }

  reverse_iterator operator--(int /* postfix */) {
    reverse_iterator ri(*this);
    ++m_iterator_;
    return ri;
  }

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(m_iterator_ - n);
  }

  reverse_iterator& operator+=(difference_type n) {
    m_iterator_ -= n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(m_iterator_ + n);
  }

  reverse_iterator& operator-=(difference_type n) {
    m_iterator_ += n;
    return *this;
  }

  reference operator[](difference_type n) const {
    return m_iterator_[-n - 1];
  }

 protected:
  Iterator m_iterator_;
};

// The C++ library working group has tentatively approved the usage of two template parameters (Iterator1 and
// Iterator2) in order to allow reverse_iterators and const_reverse iterators to be comparable. This is a similar
// issue to the C++ defect report #179 regarding comparison of container iterators and const_iterators.
template<typename IteratorLhs, typename IteratorRhs>
inline bool operator==(const reverse_iterator<IteratorLhs>& lhs, const reverse_iterator<IteratorRhs>& rhs) {
  return lhs.base() == rhs.base();
}

template<typename IteratorLhs, typename IteratorRhs>
inline bool operator<(const reverse_iterator<IteratorLhs>& lhs, const reverse_iterator<IteratorRhs>& rhs) {
  return lhs.base() > rhs.base();
}

template<typename IteratorLhs, typename IteratorRhs>
inline bool operator!=(const reverse_iterator<IteratorLhs>& lhs, const reverse_iterator<IteratorRhs>& rhs) {
  return lhs.base() != rhs.base();
}

template<typename IteratorLhs, typename IteratorRhs>
inline bool operator>(const reverse_iterator<IteratorLhs>& lhs, const reverse_iterator<IteratorRhs>& rhs) {
  return lhs.base() < rhs.base();
}

template<typename IteratorLhs, typename IteratorRhs>
inline bool operator<=(const reverse_iterator<IteratorLhs>& lhs, const reverse_iterator<IteratorRhs>& rhs) {
  return lhs.base() >= rhs.base();
}

template<typename IteratorLhs, typename IteratorRhs>
inline bool operator>=(const reverse_iterator<IteratorLhs>& lhs, const reverse_iterator<IteratorRhs>& rhs) {
  return lhs.base() <= rhs.base();
}

template<typename IteratorLhs, typename IteratorRhs>
inline typename reverse_iterator<IteratorLhs>::difference_type operator-(const reverse_iterator<IteratorLhs>& lhs,
                                                                          const reverse_iterator<IteratorRhs>& rhs) {
  return rhs.base() - lhs.base();
}

template<typename Iterator>
inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                            const reverse_iterator<Iterator>& i) {
  return reverse_iterator<Iterator>(i.base() - n);
}

// back_insert_iterator
//   A back_insert_iterator is simply a class that acts like an iterator but when you assign a value to it, it calls
//   push_back on the container with the value.
template<typename Container>
class back_insert_iterator : public iterator<Elg::Utilities::Etl::output_iterator_tag, void, void, void, void> {
  public:
  typedef Container                           container_type;
  typedef typename Container::const_reference const_reference;

  explicit back_insert_iterator(Container& x)  // NOLINT(runtime/references)
      : m_container_(x) {
  }

  back_insert_iterator& operator=(const_reference value) {
    m_container_.push_back(value);
    return *this;
  }

  back_insert_iterator& operator*() {
    return *this;
  }

  back_insert_iterator& operator++() {
    return *this;  // This is by design.
  }

  back_insert_iterator operator++(int /* postfix */) {
    return *this;  // This is by design.
  }

 protected:
  Container& m_container_;

  // Disallow copy and assign (prevent warning C4512)
  back_insert_iterator(const back_insert_iterator& other);
  back_insert_iterator& operator=(const back_insert_iterator& other);
};

// back_inserter
//   Creates an instance of a back_insert_iterator.
template<typename Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {  // NOLINT(runtime/references)
  return back_insert_iterator<Container>(x);
}

// front_insert_iterator
//   A front_insert_iterator is simply a class that acts like an iterator but when you assign a value to it, it calls
//   push_front on the container with the value.
template<typename Container>
class front_insert_iterator : public iterator<Elg::Utilities::Etl::output_iterator_tag, void, void, void, void> {
  public:
  typedef Container                           container_type;
  typedef typename Container::const_reference const_reference;

  explicit front_insert_iterator(Container& x)  // NOLINT(runtime/references)
      : m_container_(x) {
  }

  front_insert_iterator& operator=(const_reference value) {
    m_container_.push_front(value);
    return *this;
  }

  front_insert_iterator& operator*() {
    return *this;
  }

  front_insert_iterator& operator++() {
    return *this;  // This is by design.
  }

  front_insert_iterator operator++(int /* postfix */) {
    return *this;  // This is by design.
  }

 protected:
  Container& m_container_;

  // Disallow copy and assign (prevent warning C4512)
  front_insert_iterator(const front_insert_iterator& other);
  front_insert_iterator& operator=(const front_insert_iterator& other);
};

// front_inserter
//   Creates an instance of a front_insert_iterator.
template<typename Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {  // NOLINT(runtime/references)
  return front_insert_iterator<Container>(x);
}

// insert_iterator
//   An insert_iterator is like an iterator except that when you assign a value to it, the insert_iterator inserts
//   the value into the container and increments the iterator.
//
//    insert_iterator is an iterator adaptor that functions as an OutputIterator: assignment through an
//    insert_iterator inserts an object into a container. Specifically, if ii is an insert_iterator, then ii keeps
//    track of a container c and an insertion point p; the expression *ii = x performs the insertion c.insert(p, x).
//
//    If you assign through an insert_iterator several times, then you will be inserting several elements into the
//    underlying container. In the case of a sequence, they will appear at a particular location in the underlying
//    sequence, in the order in which they were inserted: one of the arguments to insert_iterator's constructor is an
//    iterator p, and the new range will be inserted immediately before p.
template<typename Container>
class insert_iterator : public iterator<Elg::Utilities::Etl::output_iterator_tag, void, void, void, void> {
 public:
  typedef Container                           container_type;
  typedef typename Container::iterator        iterator_type;
  typedef typename Container::const_reference const_reference;

  insert_iterator(Container& x, iterator_type it)  // NOLINT(runtime/references)
      : m_container_(x), m_it_(it) {
  }

  // This assignment operator is defined more to stop compiler warnings (e.g. VC++ C4512) than to be useful. However,
  // it allows insert_iterator to be assigned to another insert iterator provided that they point to the same
  // container. Copy constructor complements it.
  insert_iterator(const insert_iterator& other)
    : m_container_(other.m_container_), m_it_(other.m_it_) {
  }

  insert_iterator& operator=(const insert_iterator& other) {
    ASSERT(&m_container_ == &other.m_container_, "The insert iterator container must be the same as the assigned one");
    m_it_ = other.m_it_;
    return *this;
  }

  insert_iterator& operator=(const_reference value) {
    m_it_ = m_container_.insert(m_it_, value);
    ++m_it_;
    return *this;
  }

  insert_iterator& operator*() {
    return *this;
  }

  insert_iterator& operator++() {
    return *this;  // This is by design.
  }

  insert_iterator& operator++(int /* postfix */) {
    return *this;  // This is by design.
  }

 protected:
  Container&     m_container_;
  iterator_type  m_it_;
};

// inserter
//   Creates an instance of an insert_iterator.
template<typename Container, typename Iterator>
inline Elg::Utilities::Etl::insert_iterator<Container> inserter(Container& x,  // NOLINT(runtime/references)
                                                                Iterator i) {
  typedef typename Container::iterator iterator;
  return Elg::Utilities::Etl::insert_iterator<Container>(x, iterator(i));
}

// distance
//   Implements the distance() function. There are two versions, one for random access iterators (e.g. with vector)
//   and one for regular input iterators (e.g. with list). The former is more efficient.
template<typename InputIterator>
inline typename Elg::Utilities::Etl::iterator_traits<InputIterator>::difference_type distance_impl(
    InputIterator first,
    InputIterator last,
    Elg::Utilities::Etl::input_iterator_tag /* tag */) {
  typename Elg::Utilities::Etl::iterator_traits<InputIterator>::difference_type n = 0;

  while (first != last) {
    ++first;
    ++n;
  }
  return n;
}

template<typename RandomAccessIterator>
inline typename Elg::Utilities::Etl::iterator_traits<RandomAccessIterator>::difference_type distance_impl(
    RandomAccessIterator first,
    RandomAccessIterator last,
    Elg::Utilities::Etl::random_access_iterator_tag /* tag */) {
  return last - first;
}

template<typename InputIterator>
inline typename Elg::Utilities::Etl::iterator_traits<InputIterator>::difference_type distance(InputIterator first,
                                                                                              InputIterator last) {
  typedef typename Elg::Utilities::Etl::iterator_traits<InputIterator>::iterator_category IC;
  return Elg::Utilities::Etl::distance_impl(first, last, IC());
}

// advance
//   Implements the advance() function. There are three versions, one for random access iterators (e.g. with vector),
//   one for bidirectional iterators (list) and one for regular input iterators (e.g. with slist).
template<typename InputIterator, typename Distance>
inline void advance_impl(InputIterator& i, Distance n,  // NOLINT(runtime/references)
                         Elg::Utilities::Etl::input_iterator_tag /* it_tag */) {
  while (n--) {
    ++i;
  }
}

template<typename BidirectionalIterator, typename Distance>
inline void advance_impl(BidirectionalIterator& i, Distance n,  // NOLINT(runtime/references)
                         Elg::Utilities::Etl::bidirectional_iterator_tag /* it_tag */) {
  if (n > 0) {
    while (n--) {
      ++i;
    }
  } else {
    while (n++) {
      --i;
    }
  }
}

template<typename RandomAccessIterator, typename Distance>
inline void advance_impl(RandomAccessIterator& i, Distance n,  // NOLINT(runtime/references)
                         Elg::Utilities::Etl::random_access_iterator_tag /* it_tag */) {
  i += n;
}

template<typename InputIterator, typename Distance>
inline void advance(InputIterator& i, Distance n) {  // NOLINT(runtime/references)
  typedef typename Elg::Utilities::Etl::iterator_traits<InputIterator>::iterator_category IC;
  Elg::Utilities::Etl::advance_impl(i, n, IC());
}

}  // namespace Etl
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_ETL_ITERATOR_H_
