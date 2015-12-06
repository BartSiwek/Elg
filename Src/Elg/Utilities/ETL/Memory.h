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

#ifndef ELG_UTILITIES_ETL_MEMORY_H_
#define ELG_UTILITIES_ETL_MEMORY_H_

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/ETL/TypeTraits.h"
#include "Elg/Utilities/ETL/Iterator.h"
#include "Elg/Utilities/ETL/Utility.h"
#include "Elg/Utilities/ETL/Algorithm.h"

namespace Elg {
namespace Utilities {
namespace Etl {

// get_temporary_buffer
//   From the C++ standard, section 20.4.3:
//     1 Effects: Obtains a pointer to storage sufficient to store up to n adjacent T objects.
//     2 Returns: A pair containing the buffer's address and capacity (in the units of sizeof(T)), or a pair of 0
//       values if no storage can be obtained.
//
//   Note: The return value is space to hold T elements, but no T elements are constructed.
//
//   Our implementation here differs slightly in that we have alignment and allocator arguments.
//
//   Example usage:
//     pair<int*, ptrdiff_t> pr = get_temporary_buffer<int>(100, 0, my_fav_allocator_ptr);
//     memset(pr.first, 0, 100 * sizeof(int));
//     return_temporary_buffer(pr.first, my_fav_allocator_ptr);
//
template<typename T, typename AllocatorType>
pair<T*, elg_pointer_diff> get_temporary_buffer(elg_pointer_diff n, elg_size_type alignment,
                                                AllocatorType* allocator) {
  void* ptr = ElgMalloc(n * sizeof(T), alignment, allocator);
  return pair<T*, elg_pointer_diff>(static_cast<T*>(ptr), n);  // NOLINT(build/include_what_you_use)
}

// return_temporary_buffer
//   From the C++ standard, section 20.4.3:
//     3 Effects:  Deallocates the buffer to which p points.
//     4 Requires: The buffer shall have been previously allocated by get_temporary_buffer.
//
//     Note: This function merely frees space and does not destruct any T elements.
//
//     Example usage:
//     pair<int*, ptrdiff_t> pr = get_temporary_buffer<int>(100, 0, my_fav_allocator_ptr);
//     memset(pr.first, 0, 100 * sizeof(int));
//     return_temporary_buffer(pr.first, my_fav_allocator_ptr);
//
template<typename T, typename AllocatorType>
void return_temporary_buffer(T* p, AllocatorType* allocator) {
  ElgFree(p, allocator)
}

// uninitialized_move
//   uninitialized_move takes a constructed sequence of objects and an uninitialized destination buffer. In the case of
//   any exception thrown while moving the objects, any newly constructed objects are guaranteed to be destructed and
//   the input left fully constructed.
//
//   In the case where you need to do multiple moves atomically, split the calls into
//   uninitialized_move_start/abort/commit.
//
//   uninitialized_move_start can possibly throw an exception. If it does, you don't need to do anything. However, if
//   it returns without throwing an exception you need to guarantee that either uninitialize_move_abort or
//   uninitialized_move_commit is called.
//
//   Both uninitialize_move_abort and uninitialize_move_commit are guaranteed to not throw C++ exceptions.
template<bool HasTrivialMove, typename IteratorTag>
struct uninitialized_move_impl {
  template<typename ForwardIterator, typename ForwardIteratorDest>
  static ForwardIteratorDest do_move_start(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;

    ForwardIteratorDest orig_dest(dest);
    try {
      for (; first != last; ++first, ++dest) {
        ::new(&*dest) value_type(*first);
      }
    } catch(...) {
      for (; orig_dest < dest; ++orig_dest) {
        orig_dest->~value_type();
      }
      throw;
    }

    return dest;
  }

  template<typename ForwardIterator, typename ForwardIteratorDest>
  static ForwardIteratorDest do_move_start_nothrow(ForwardIterator first, ForwardIterator last,
                                                   ForwardIteratorDest dest) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;

    for (; first != last; ++first, ++dest) {
      ::new(&*dest) value_type(*first);
    }

    return dest;
  }

  template<typename ForwardIterator, typename ForwardIteratorDest>
  static ForwardIteratorDest do_move_commit(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;

    for (; first != last; ++first, ++dest) {
      first->~value_type();
    }

    return dest;
  }

  template<typename ForwardIterator, typename ForwardIteratorDest>
  static ForwardIteratorDest do_move_abort(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;

    for (; first != last; ++first, ++dest) {
      dest->~value_type();
    }

    return dest;
  }
};

template<>
struct uninitialized_move_impl<true, Elg::Utilities::Etl::random_access_iterator_tag> {
  template<typename T>
  static T* do_move_start(T* first, T* last, T* dest) {
    void* ptr = std::memcpy(dest, first, (size_t)((elg_uint_pointer)last - (elg_uint_pointer)first));
    return reinterpret_cast<T*>(ptr) + (last - first);
  }

  template<typename T>
  static T* do_move_start_nothrow(T* first, T* last, T* dest) {
    void* ptr = std::memcpy(dest, first, (size_t)((elg_uint_pointer)last - (elg_uint_pointer)first));
    return reinterpret_cast<T*>(ptr) + (last - first);
  }

  template<typename T>
  static T* do_move_commit(T* first, T* last, T* dest) {
    return dest + (last - first);
  }

  template<typename T>
  static T* do_move_abort(T* first, T* last, T* dest) {
    return dest + (last - first);
  }
};


// uninitialized_move_start, uninitialized_move_commit, uninitialized_move_abort
//   After calling uninitialized_move_start, if it doesn't throw an exception, both the source and destination
//   iterators point to undefined data. If it does throw an exception, the destination remains uninitialized and the
//   source is as it was before.
//
//   In order to make the iterators valid again you need to call either uninitialized_move_abort or
//   uninitialized_move_commit. The abort call makes the original source iterator valid again, and commit makes the
//   destination valid. Both abort and commit are guaranteed to not throw C++ exceptions.
//
//   Example usage:
//     iterator dest2 = uninitialized_move_start(first, last, dest);
//     try {
//         // some code here that might throw an exception
//     }
//     catch(...)
//     {
//         uninitialized_move_abort(first, last, dest);
//         throw;
//     }
//     uninitialized_move_commit(first, last, dest);
template<typename ForwardIterator, typename ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_start(ForwardIterator first, ForwardIterator last,
                                                    ForwardIteratorDest dest) {
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::iterator_category IC;
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type_input;
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIteratorDest>::value_type value_type_output;

  const bool HasTrivialMove = type_and<
    has_trivial_relocate<value_type_input>::value,
    is_pointer<ForwardIterator>::value,
    is_pointer<ForwardIteratorDest>::value,
    is_same<value_type_input, value_type_output>::value
  >::value;

  return Elg::Utilities::Etl::uninitialized_move_impl<HasTrivialMove, IC>::do_move_start(first, last, dest);
}

template<typename ForwardIterator, typename ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_start_nothrow(ForwardIterator first, ForwardIterator last,
                                                            ForwardIteratorDest dest) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::iterator_category IC;
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type_input;
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIteratorDest>::value_type value_type_output;

    const bool HasTrivialMove = type_and<
      has_trivial_relocate<value_type_input>::value,
      is_pointer<ForwardIterator>::value,
      is_pointer<ForwardIteratorDest>::value,
      is_same<value_type_input, value_type_output>::value
    >::value;

    return Elg::Utilities::Etl::uninitialized_move_impl<HasTrivialMove, IC>::do_move_start_nothrow(first, last, dest);
}

template<typename ForwardIterator, typename ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_commit(ForwardIterator first, ForwardIterator last,
                                                     ForwardIteratorDest dest) {
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::iterator_category IC;
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type_input;
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIteratorDest>::value_type value_type_output;

  const bool HasTrivialMove = type_and<
    has_trivial_relocate<value_type_input>::value,
    is_pointer<ForwardIterator>::value,
    is_pointer<ForwardIteratorDest>::value,
    is_same<value_type_input, value_type_output>::value
  >::value;

  return Elg::Utilities::Etl::uninitialized_move_impl<HasTrivialMove, IC>::do_move_commit(first, last, dest);
}

template<typename ForwardIterator, typename ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_abort(ForwardIterator first, ForwardIterator last,
                                                    ForwardIteratorDest dest) {
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::iterator_category IC;
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type_input;
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIteratorDest>::value_type value_type_output;

  const bool HasTrivialMove = type_and<
    has_trivial_relocate<value_type_input>::value,
    is_pointer<ForwardIterator>::value,
    is_pointer<ForwardIteratorDest>::value,
    is_same<value_type_input, value_type_output>::value
  >::value;

  return Elg::Utilities::Etl::uninitialized_move_impl<HasTrivialMove, IC>::do_move_abort(first, last, dest);
}

// uninitialized_move
//   uninitialized_move takes a constructed sequence of objects and an uninitialized destination buffer. In the case of
//   any exception thrown while moving the objects, any newly constructed objects are guaranteed to be destructed and
//   the input left as it was before.
template<typename ForwardIterator, typename ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest) {
  ForwardIteratorDest result = uninitialized_move_start(first, last, dest);
  uninitialized_move_commit(first, last, dest);

  return result;
}

template<typename ForwardIterator, typename ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_nothrow(ForwardIterator first, ForwardIterator last,
                                                      ForwardIteratorDest dest) {
  ForwardIteratorDest result = uninitialized_move_start_nothrow(first, last, dest);
  uninitialized_move_commit(first, last, dest);

  return result;
}


// uninitialized_copy
template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIterator dest,
                                               Elg::Utilities::Etl::true_type /* has_trivial_copy */) {
  /* The copy() in turn will use memcpy for POD types */
  return Elg::Utilities::Etl::copy(first, last, dest);  // NOLINT(build/include_what_you_use)
}

template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIterator dest,
                                               Elg::Utilities::Etl::false_type /* has_trivial_copy */) {
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
  ForwardIterator currentDest(dest);

  for (; first != last; ++first, ++currentDest) {
    ::new(&*currentDest) value_type(*first);
  }

  return currentDest;
}

// uninitialized_copy
//   Copies a source range to a destination, copy-constructing the destination with the source values (and not
//   *assigning* the destination with the source values). Returns the end of the destination range
//   (i.e. dest + (last - first)).
//
//   Declaration:
//     template<typename InputIterator, typename ForwardIterator>
//     ForwardIterator uninitialized_copy(InputIterator sourceFirst, InputIterator sourceLast,
//     ForwardIterator destination);
//
//   Example usage:
//     SomeClass* pArray = malloc(10 * sizeof(SomeClass));
//     uninitialized_copy(pSourceDataBegin, pSourceDataBegin + 10, pArray);
template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
  typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
  return uninitialized_copy_impl(first, last, result, Elg::Utilities::Etl::has_trivial_copy<value_type>());
}

// uninitialized_copy_ptr
//   This is a specialization of uninitialized_copy for iterators that are pointers. It exists so that we can declare
//   a value_type for the iterator, which you can't do with a pointer by itself.
template<typename First, typename Last, typename Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result) {
  typedef typename Elg::Utilities::Etl::iterator_traits< generic_iterator<Result, void> >::value_type value_type;

  const generic_iterator<Result, void> i(uninitialized_copy_impl(generic_iterator<First, void>(first),
                                                                 generic_iterator<Last, void>(last),
                                                                 generic_iterator<Result, void>(result),
                                                                 has_trivial_assign<value_type>()));
  return i.base();
}

// uninitialized_fill
template<typename ForwardIterator, typename T>
inline void uninitialized_fill_impl(ForwardIterator first, ForwardIterator last, const T& value,
                                    Elg::Utilities::Etl::true_type /* has_trivial_assign */) {
    Elg::Utilities::Etl::fill(first, last, value);
}

template<typename ForwardIterator, typename T>
void uninitialized_fill_impl(ForwardIterator first, ForwardIterator last, const T& value,
                              Elg::Utilities::Etl::false_type /* has_trivial_assign */) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
    ForwardIterator currentDest(first);

    for (; currentDest != last; ++currentDest) {
      ::new(&*currentDest) value_type(value);
    }
}

// uninitialized_fill
//   Copy-constructs the elements in the destination range with the given input value. Returns void. It wouldn't be
//   useful to return the end of the destination range, as that is the same as the 'last' input parameter.
//
//   Declaration:
//     template<typename ForwardIterator, typename T>
//     void uninitialized_fill(ForwardIterator destinationFirst, ForwardIterator destinationLast, const T& value);
template<typename ForwardIterator, typename T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
    uninitialized_fill_impl(first, last, value, Elg::Utilities::Etl::has_trivial_assign<value_type>());
}

// uninitialized_fill_ptr
//   This is a specialization of uninitialized_fill for iterators that are pointers. It exists so that we can declare a
//   value_type for the iterator, which you can't do with a pointer by itself.
template<typename T>
inline void uninitialized_fill_ptr(T* first, T* last, const T& value) {
  typedef typename Elg::Utilities::Etl::iterator_traits<generic_iterator<T*, void> >::value_type value_type;

  uninitialized_fill_impl(generic_iterator<T*, void>(first), generic_iterator<T*, void>(last), value,
    has_trivial_assign<value_type>());
}

// uninitialized_fill_n
//
template<typename ForwardIterator, typename Count, typename T>
inline void uninitialized_fill_n_impl(ForwardIterator first, Count n, const T& value,
                                      Elg::Utilities::Etl::true_type /* has_trivial_assign */) {
    Elg::Utilities::Etl::fill_n(first, n, value);
}

template<typename ForwardIterator, typename Count, typename T>
void uninitialized_fill_n_impl(ForwardIterator first, Count n, const T& value,
                               Elg::Utilities::Etl::false_type /* has_trivial_assign */) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
    ForwardIterator currentDest(first);

    for (; n > 0; --n, ++currentDest) {
      ::new(&*currentDest) value_type(value);
    }
}

// uninitialized_fill_n
//   Copy-constructs the range of [first, first + n) with the given input value. Returns void as per the C++
//   standard, though returning the end input iterator value may be of use.
//
//   Declaration:
//     template<typename ForwardIterator, typename Count, typename T>
//     void uninitialized_fill_n(ForwardIterator destination, Count n, const T& value);
template<typename ForwardIterator, typename Count, typename T>
inline void uninitialized_fill_n(ForwardIterator first, Count n, const T& value) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
    uninitialized_fill_n_impl(first, n, value, has_trivial_assign<value_type>());
}

// uninitialized_fill_n_ptr
//   This is a specialization of uninitialized_fill_n for iterators that are pointers. It exists so that we can
//    declare a value_type for the iterator, which you can't do with a pointer by itself.
template<typename T, typename Count>
inline void uninitialized_fill_n_ptr(T* first, Count n, const T& value) {
  typedef typename Elg::Utilities::Etl::iterator_traits<generic_iterator<T*, void> >::value_type value_type;
  uninitialized_fill_n_impl(generic_iterator<T*, void>(first), n, value, has_trivial_assign<value_type>());
}

// uninitialized_copy_fill
//   Copies [first1, last1) into [first2, first2 + (last1 - first1)) then fills [first2 + (last1 - first1), last2)
//   with value.
template<typename InputIterator, typename ForwardIterator, typename T>
inline void uninitialized_copy_fill(InputIterator first1, InputIterator last1, ForwardIterator first2,
  ForwardIterator last2, const T& value) {
    const ForwardIterator mid(Elg::Utilities::Etl::uninitialized_copy(first1, last1, first2));
    Elg::Utilities::Etl::uninitialized_fill(mid, last2, value);
}

// uninitialized_fill_copy
//   Fills [result, mid) with value then copies [first, last) into [mid, mid + (last - first)).
template<typename ForwardIterator, typename T, typename InputIterator>
inline ForwardIterator uninitialized_fill_copy(ForwardIterator result, ForwardIterator mid, const T& value,
  InputIterator first, InputIterator last) {
    Elg::Utilities::Etl::uninitialized_fill(result, mid, value);
    return Elg::Utilities::Etl::uninitialized_copy(first, last, mid);
}

// uninitialized_copy_copy
//   Copies [first1, last1) into [result, result + (last1 - first1)) then copies [first2, last2) into
//   [result, result + (last1 - first1) + (last2 - first2)).
template<typename InputIterator1, typename InputIterator2, typename ForwardIterator>
inline ForwardIterator uninitialized_copy_copy(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
  InputIterator2 last2, ForwardIterator result) {
    const ForwardIterator mid(Elg::Utilities::Etl::uninitialized_copy(first1, last1, result));
    return Elg::Utilities::Etl::uninitialized_copy(first2, last2, mid);
}

// destruct
//   Calls the destructor of a given object.
//
//   Note that we don't have a specialized version of this for objects with trivial destructors, such as integers.
//   This is because the compiler can already see in our version here that the destructor is a no-op.
template<typename T>
inline void destruct(T* p) {
    p->~T();
}

// destruct(first, last)
template<typename ForwardIterator>
inline void destruct_impl(ForwardIterator /* first */, ForwardIterator /* last */,
                          Elg::Utilities::Etl::true_type /* has_trivial_destructor */) {
}

template<typename ForwardIterator>
inline void destruct_impl(ForwardIterator first, ForwardIterator last,
                          Elg::Utilities::Etl::false_type /* has_trivial_destructor */) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;

    for (; first != last; ++first) {
        (*first).~value_type();
    }
}

// destruct
//   Calls the destructor on a range of objects.
//
//   We have a specialization for objects with trivial destructors, such as PODs. In this specialization the
//   destruction of the range is a no-op.
template<typename ForwardIterator>
inline void destruct(ForwardIterator first, ForwardIterator last) {
    typedef typename Elg::Utilities::Etl::iterator_traits<ForwardIterator>::value_type value_type;
    destruct_impl(first, last, Elg::Utilities::Etl::has_trivial_destructor<value_type>());
}

}  // namespace Elg
}  // namespace Utilities
}  // namespace Etl

#endif  // ELG_UTILITIES_ETL_MEMORY_H_
