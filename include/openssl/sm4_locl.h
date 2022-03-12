/* crypto/sm4/sm4_locl.h
 *
 */

#ifndef HEADER_SM4_LOCL_H
#define HEADER_SM4_LOCL_H

#include <openssl/e_os2.h>

#ifdef OPENSSL_NO_SM4
#error SM4 is disabled.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64))
# define SWAP(x) (_lrotl(x, 8) & 0x00ff00ff | _lrotr(x, 8) & 0xff00ff00)
# define GETU32(p) SWAP(*((u32 *)(p)))
# define PUTU32(ct, st) { *((u32 *)(ct)) = SWAP((st)); }
#else
# define GETU32(pt) (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]))
# define PUTU32(ct, st) { (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }
#endif

#if !defined(PEDANTIC) && !defined(OPENSSL_NO_ASM) && !defined(OPENSSL_NO_INLINE_ASM)
# if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64))
#  define CROR(x, s) _lrotr(x, s)
#  define CROL(x, s)  _lrotl(x, s)
# elif defined(__GNUC__) && __GNUC__>=2
#  if defined(__i386) || defined(__x86_64)
#  define CROL(a,n) ({ register unsigned int ret;   \
                    asm ("roll %%cl,%0" \
                        : "=r"(ret) \
                        : "c"(n),"0"((unsigned int)(a)) \
                        : "cc");    \
                    ret;            \
                })
#  define CROR(a,n) ({ register unsigned int ret;   \
                    asm ("rorl %%cl,%0" \
                        : "=r"(ret) \
                        : "c"(n),"0"((unsigned int)(a)) \
                        : "cc");    \
                    ret;            \
                })
#  elif defined(_ARCH_PPC) || defined(_ARCH_PPC64) || \
        defined(__powerpc) || defined(__ppc__) || defined(__powerpc64__)
#   define CROL(x,s)  ({u32 ret; asm ("rlwinm %0,%1,%2,0,31":"=r"(ret):"r"(x),"I"(s)); ret; })
#   define CROR(x,s) CROL(x,(32-s))
#  elif defined(__s390x__)
#   define CROL(x,s)  ({u32 ret; asm ("rll %0,%1,%2":"=r"(ret):"r"(x),"I"(s)); ret; })
#   define CROR(x,s) CROL(x,(32-s))
#  endif
# endif
#endif

#if !defined(CROR) && !defined(CROL)
# define CROR(x, s) ( ((x) >> (s)) | ((x) << (32 - (s))) )
# define CROL(x, s) ( ((x) << (s)) | ((x) >> (32 - (s))) )
#endif

#define SWAP32(l) (((l) >> 24) | \
    (((l) & 0x00ff0000) >> 8)  | \
    (((l) & 0x0000ff00) << 8)  | \
    ((l) << 24))

#ifdef SM4_LONG
typedef unsigned long u32;
#else
typedef unsigned int u32;
#endif
typedef unsigned short u16;
typedef unsigned char u8;

#define MAXKC   (256/32)
#define MAXKB   (256/8)
#define MAXNR   14

/* This controls loop-unrolling in sm4_core.c */
#undef FULL_UNROLL

#endif /* !HEADER_SM4_LOCL_H */
