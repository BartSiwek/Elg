/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 * Based on EASTL (https://github.com/paulhodge/EASTL) - copyright information follows.
 */

#ifndef ELG_TESTS_UTILITIES_ETL_TESTITERATOR_H_
#define ELG_TESTS_UTILITIES_ETL_TESTITERATOR_H_

#include "Elg/Utilities/ETL/Iterator.h"

template<typename IteratorCategoryType>
struct TestIterator : public Elg::Utilities::Etl::iterator<IteratorCategoryType, elg_int32, elg_pointer_diff,
  elg_int32*, elg_int32&> {
    TestIterator() : m_pointer_(NULL) {
    }

    explicit TestIterator(elg_int32* i) : m_pointer_(i) {
    }

    elg_int32* base() const {
      return m_pointer_;
    }

    elg_int32& operator*() const {
      return *m_pointer_;
    }

    elg_int32* operator->() const {
      return m_pointer_;
    }

    TestIterator& operator++() {
      ++m_pointer_;
      return *this;
    }

    TestIterator operator++(int /* postfix */) {
      TestIterator prev(*this);
      ++m_pointer_;
      return prev;
    }

    TestIterator& operator--() {
      --m_pointer_;
      return *this;
    }

    TestIterator operator--(int /* postfix */) {
      TestIterator prev(*this);
      --m_pointer_;
      return prev;
    }

    TestIterator operator+(difference_type n) const {
      return TestIterator(m_pointer_ + n);
    }

    TestIterator& operator+=(difference_type n) {
      m_pointer_ += n;
      return *this;
    }

    TestIterator operator-(difference_type n) const {
      return TestIterator(m_pointer_ - n);
    }

    TestIterator& operator-=(difference_type n) {
      m_pointer_ -= n;
      return *this;
    }

    elg_int32& operator[](difference_type n) const {
      return m_pointer_[n];
    }

 private:
  elg_int32* m_pointer_;
};

template<typename IC>
inline bool operator==(const TestIterator<IC>& lhs, const TestIterator<IC>& rhs) {
  return lhs.base() == rhs.base();
}

template<typename IC>
inline bool operator!=(const TestIterator<IC>& lhs, const TestIterator<IC>& rhs) {
  return lhs.base() != rhs.base();
}

template<typename IC>
inline bool operator<(const TestIterator<IC>& lhs, const TestIterator<IC>& rhs) {
  return lhs.base() < rhs.base();
}

template<typename IC>
inline bool operator>(const TestIterator<IC>& lhs, const TestIterator<IC>& rhs) {
  return lhs.base() > rhs.base();
}

template<typename IC>
inline bool operator<=(const TestIterator<IC>& lhs, const TestIterator<IC>& rhs) {
  return lhs.base() <= rhs.base();
}

template<typename IC>
inline bool operator>=(const TestIterator<IC>& lhs, const TestIterator<IC>& rhs) {
  return lhs.base() >= rhs.base();
}

template<typename IC>
inline typename TestIterator<IC>::difference_type operator-(const TestIterator<IC>& lhs,
                                                            const TestIterator<IC>& rhs) {
  return lhs.base() - rhs.base();
}

template<typename IC>
inline TestIterator<IC> operator+(typename TestIterator<IC>::difference_type n, const TestIterator<IC>& x) {
  return TestIterator<Iterator, IC>(x.base() + n);
}

typedef TestIterator<Elg::Utilities::Etl::random_access_iterator_tag> TestRandomIterator;
typedef TestIterator<Elg::Utilities::Etl::bidirectional_iterator_tag> TestBidirectionalIterator;
typedef TestIterator<Elg::Utilities::Etl::forward_iterator_tag> TestForwardIterator;
typedef TestIterator<Elg::Utilities::Etl::input_iterator_tag> TestInputIterator;

#endif  // ELG_TESTS_UTILITIES_ETL_TESTITERATOR_H_
