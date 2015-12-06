/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_MACROS_H_
#define ELG_UTILITIES_MACROS_H_

// Force inline macro
#if (__GNUC__ && __cplusplus)
#define ELG_FORCEINLINE __attribute__((always_inline))
#elif(_MSC_VER >= 1400)
#define ELG_FORCEINLINE __forceinline
#else
#error "Cannot define FORCEINLINE macro"
#endif

// Simple function name macro
#if (__GNUC__ && __cplusplus)
#define ELG_FUNC __FUNC__
#elif(_MSC_VER >= 1400)
#define ELG_FUNC __FUNCTION__
#else
#error "Cannot define FUNCNAME macro"
#endif

// Function name macro
#if (__GNUC__ && __cplusplus)
#define ELG_PRETTY_FUNC __PRETTY_FUNCTION__
#elif(_MSC_VER >= 1400)
#define ELG_PRETTY_FUNC __FUNCSIG__
#else
#error "Cannot define FUNCNAME macro"
#endif

// Debug breakpoint macro
#if (_MSC_VER >= 1310)
#pragma warning(push)
#pragma warning(disable : 6540)
#include <intrin.h>
#include <windows.h>
#pragma warning(pop)
#include <cstdlib>
#define ELG_DEBUGBREAK (IsDebuggerPresent() ? __debugbreak() : std::abort() )
#else
#define ELG_DEBUGBREAK abort()
#endif

// Thread local storage macro
#if (__GNUC__ && __cplusplus)
#define ELG_THREAD_LOCAL __thread
#elif(_MSC_VER >= 1310)
#define ELG_THREAD_LOCAL __declspec(thread)
#else
#error "Cannot define THREAD_LOCAL macro"
#endif

// Static code analysis assumptions
#if (_MSC_VER >= 1600)
#define ELG_STATIC_ANALYSIS_ASSUME(condition) __analysis_assume(!!(condition))
#else
#define ELG_STATIC_ANALYSIS_ASSUME(condition)
#endif

// Memory alignment
#if (_MSC_VER >= 1310)
#define ELG_ALIGNOF(TYPE) __alignof(TYPE)
#else
#error "Cannot define ALIGNOF macro"
#endif

// Offset of a member in structure
#if (_MSC_VER >= 1310)
#include <cstddef>
#define ELG_OFFSETOF(MEMBER, TYPE) offsetof(MEMBER, TYPE)
#else
#error "Cannot define ALIGNOF macro"
#endif

#endif  // ELG_UTILITIES_MACROS_H_
