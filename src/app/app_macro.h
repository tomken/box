
#ifndef __APP_MACRO_H__
#define __APP_MACRO_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#ifndef _STR
#define _STR(m_x) #m_x
#define _MKSTR(m_x) _STR(m_x)
#endif

#ifndef _ALWAYS_INLINE_
#if defined(__GNUC__)
#define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define _ALWAYS_INLINE_ __forceinline
#else
#define _ALWAYS_INLINE_ inline
#endif
#endif

#ifndef _FORCE_INLINE_
#ifdef DISABLE_FORCED_INLINE
#define _FORCE_INLINE_ inline
#else
#define _FORCE_INLINE_ _ALWAYS_INLINE_
#endif
#endif

#if defined(__GNUC__)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x) x
#define unlikely(x) x
#endif

#endif // __APP_MACRO_H__
