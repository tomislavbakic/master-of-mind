/*  mem.h

    Memory manipulation functions

*/

/*
 *      C/C++ Run Time Library - Version 10.0
 *
 *      Copyright (c) 1987, 2000 by Inprise Corporation
 *      All Rights Reserved.
 *
 */

/ $Revision:   9.4.1.0  $ /

#if !defined(__MEM_H)
#define __MEM_H

#ifndef ___STDDEF_H
#include <_stddef.h>
#endif

#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  / !RC_INVOKED /


#ifdef __cplusplus
extern "C" {
#endif

    / Intrinsic functions, defined outside of the namespace /

        void FAR * RTLENTRY  EXPFUNC16 _memchr__(const void FAR * _s, int _c, SIZE_T __n);
    int         RTLENTRY  EXPFUNC16 _memcmp__(const void FAR  _s1, const void FAR  _s2, SIZE_T __n);
    void FAR* RTLENTRY  EXPFUNC16 _memcpy__(void FAR* _dest, const void FAR* _src, SIZE_T _n);
    void FAR* RTLENTRYF EXPFUNC16 _memset__(void FAR* _s, int _c, SIZE_T __n);

#ifdef __cplusplus
    namespace std {
#endif

        void FAR* RTLENTRY  EXPFUNC memccpy(void FAR _dest, const void FAR __src,
            int _c, SIZE_T __n);
        int         RTLENTRY  EXPFUNC memcmp(const void FAR* __s1, const void FAR* __s2,
            SIZE_T _n);
        void FAR* RTLENTRY  EXPFUNC memcpy(void FAR _dest, const void FAR __src,
            SIZE_T _n);
        int         RTLENTRY  EXPFUNC memicmp(const void FAR* __s1, const void FAR* __s2,
            SIZE_T _n);
        void FAR* RTLENTRYF EXPFUNC memmove(void FAR _dest, const void FAR __src,
            SIZE_T _n);
        void FAR* RTLENTRYF EXPFUNC memset(void FAR* __s, int _c, SIZE_T __n);

        void           RTLENTRY  EXPFUNC _wmemset(void __s, int _c, SIZE_T __n);
        void           RTLENTRY  EXPFUNC _wmemcpy(void __dest, const void* __src, SIZE_T _n);

#if defined(__cplusplus)
        extern "C++"
        {
            void FAR* RTLENTRY EXPFUNC32 memchr(void FAR* __s, int _c, SIZE_T __n);
            const void FAR* RTLENTRY EXPFUNC32 memchr(const void FAR* __s, int _c, SIZE_T __n);
            void       RTLENTRY EXPFUNC32 _wmemchr(void __s, int _c, SIZE_T __n);
            const void       RTLENTRY EXPFUNC32 _wmemchr(const void __s, int _c, SIZE_T __n);
        }
#else
        void FAR* RTLENTRY EXPFUNC32 memchr(const void FAR* __s, int _c, SIZE_T __n);
        void       RTLENTRY EXPFUNC32 _wmemchr(const void __s, int _c, SIZE_T __n);
#endif



#define movmem(src,dest,length) (void)memmove(dest,src,length)
#define setmem(dest,length,value) (void)memset(dest,value,length)

#if !defined(__STDC__) / NON_ANSI  /
#define _fmemccpy memccpy
#define _fmemchr  memchr
#define _fmemcmp  memcmp
#define _fmemcpy  memcpy
#define _fmemicmp memicmp
#define _fmemmove memmove
#define _fmemset  memset
#define _fmovmem  movmem
#define _fsetmem  setmem
#endif / _STDC_  /

#ifdef __cplusplus
    } // std
} // extern "C"
#endif

#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  / !RC_INVOKED /


#endif  / __MEM_H /

#if defined(__cplusplus) && !defined(__USING_CNAME__) && !defined(__MEM_H_USING_LIST)
#define __MEM_H_USING_LIST
using std::_wmemchr;
using std::_wmemcpy;
using std::_wmemset;
using std::memccpy;
using std::memicmp;
using std::memmove;

/*
   Handle intrinsics specially.  If intrinsics are on, the compiler creates
   a macro of the normal function mapping to the __ intrinsic version, ie:
     #define strcpy _strcpy_
   Thus, we can test the normal name as a macro to see if it's defined, and
   only preform a using statement if it's not an intrinsic
*/

#  ifndef memchr
using std::memchr;
#  endif // ifndef memchr
#  ifndef memcmp
using std::memcmp;
#  endif // ifndef memcmp
#  ifndef memcpy
using std::memcpy;
#  endif // ifndef memcpy
#  ifndef memset
using std::memset;
#  endif // ifndef memset

#endif / _USING_CNAME_ /