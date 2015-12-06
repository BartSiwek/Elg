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

#ifndef ELG_UTILITIES_ETL_GENERICITERATOR_H_
#define ELG_UTILITIES_ETL_GENERICITERATOR_H_

#include "Elg/Utilities/ETL/Iterator.h"
#include "Elg/Utilities/ETL/TypeTraits.h"

namespace Elg {
namespace Utilities {
namespace Etl {

// generic_iterator
//   Converts something which can be iterated into a formal iterator. While this class' primary purpose is to allow
//   the conversion of a pointer to an iterator, you can convert anything else to an iterator by defining an
//   iterator_traits<> specialization for that object type. See Iterator.h for this.
//
//   Example usage:
//      typedef generic_iterator<int*>       IntArrayIterator;
//      typedef generic_iterator<int*, char> IntArrayIteratorOther;
template<typename Iterator, typename Container = void>
class generic_iterator {
 public:
  // Typedefs
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::value_type        value_type;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::difference_type   difference_type;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::reference         reference;
  typedef typename Elg::Utilities::Etl::iterator_traits<Iterator>::pointer           pointer;
  typedef Iterator                                                                   iterator_type;
  typedef Container                                                                  container_type;

  typedef generic_iterator<Iterator, Container>                                      this_type;

  // Constructors
  generic_iterator() : m_iterator_(iterator_type()) {
  }

  explicit generic_iterator(const iterator_type& other)
      : m_iterator_(other) {
  }

  template<typename Iterator2>
  generic_iterator(const generic_iterator<Iterator2, Container>& other)
      : m_iterator_(other.base()) {
  }

  // Operators
  this_type& operator=(const iterator_type& other) {
    m_iterator_ = other;
    return *this;
  }

  reference operator*() const {
    return *m_iterator_;
  }

  pointer operator->() const {
    return m_iterator_;
  }

  this_type& operator++() {
    ++m_iterator_;
    return *this;
  }

  this_type operator++(int /* postfix */) {
    return this_type(m_iterator_++);
  }

  this_type& operator--() {
    --m_iterator_;
    return *this;
  }

  this_type operator--(int /* postfix */) {
    return this_type(m_iterator_--);
  }

  reference operator[](const difference_type& n) const {
    return m_iterator_[n];
  }

  this_type& operator+=(const difference_type& n) {
    m_iterator_ += n;
    return *this;
  }

  this_type operator+(const difference_type& n) const {
    return this_type(m_iterator_ + n);
  }

  this_type& operator-=(const difference_type& n) {
    m_iterator_ -= n;
    return *this;
  }

  this_type operator-(const difference_type& n) const {
    return this_type(m_iterator_ - n);
  }

  // Member functions
  const iterator_type& base() const {
    return m_iterator_;
  }

 protected:
  Iterator m_iterator_;
};

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator==(const generic_iterator<IteratorL, Container>& lhs,
                       const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() == rhs.base();
}

template<typename Iterator, typename Container>
inline bool operator==(const generic_iterator<Iterator, Container>& lhs,
                       const generic_iterator<Iterator, Container>& rhs) {
  return lhs.base() == rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator!=(const generic_iterator<IteratorL, Container>& lhs,
                       const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() != rhs.base();
}

template<typename Iterator, typename Container>
inline bool operator!=(const generic_iterator<Iterator, Container>& lhs,
                       const generic_iterator<Iterator, Container>& rhs) {
  return lhs.base() != rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator<(const generic_iterator<IteratorL, Container>& lhs,
                      const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() < rhs.base();
}

template<typename Iterator, typename Container>
inline bool operator<(const generic_iterator<Iterator, Container>& lhs,
                      const generic_iterator<Iterator, Container>& rhs) {
  return lhs.base() < rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator>(const generic_iterator<IteratorL, Container>& lhs,
                      const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() > rhs.base();
}

template<typename Iterator, typename Container>
inline bool operator>(const generic_iterator<Iterator, Container>& lhs,
                      const generic_iterator<Iterator, Container>& rhs) {
  return lhs.base() > rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator<=(const generic_iterator<IteratorL, Container>& lhs,
                       const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() <= rhs.base();
}

template<typename Iterator, typename Container>
inline bool operator<=(const generic_iterator<Iterator, Container>& lhs,
                       const generic_iterator<Iterator, Container>& rhs) {
  return lhs.base() <= rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline bool operator>=(const generic_iterator<IteratorL, Container>& lhs,
                       const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() >= rhs.base();
}

template<typename Iterator, typename Container>
inline bool operator>=(const generic_iterator<Iterator, Container>& lhs,
                       const generic_iterator<Iterator, Container>& rhs) {
  return lhs.base() >= rhs.base();
}

template<typename IteratorL, typename IteratorR, typename Container>
inline typename generic_iterator<IteratorL, Container>::difference_type operator-(
    const generic_iterator<IteratorL, Container>& lhs,
    const generic_iterator<IteratorR, Container>& rhs) {
  return lhs.base() - rhs.base();
}

template<typename Iterator, typename Container>
inline generic_iterator<Iterator, Container> operator+(
    typename generic_iterator<Iterator, Container>::difference_type n,
    const generic_iterator<Iterator, Container>& x) {
  return generic_iterator<Iterator, Container>(x.base() + n);
}

// is_generic_iterator
//   Tells if an iterator is one of these generic_iterators. This is useful if you want to write code that uses
//   miscellaneous iterators but wants to tell if they are generic_iterators. A primary reason to do so is that you
//   can get at the pointer within the generic_iterator.
template<typename Iterator>
struct is_generic_iterator : public false_type {
};

template<typename Iterator, typename Container>
struct is_generic_iterator<generic_iterator<Iterator, Container>> : public true_type {
};

}  // namespace Etl
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_ETL_GENERICITERATOR_H_
