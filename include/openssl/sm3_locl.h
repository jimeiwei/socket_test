/*
 * sm3_locl.h
 *
 *  Created on: 2012-10-17
 *      Author: zweib
 */

#ifndef SM3_LOCL_H_
#define SM3_LOCL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(PEDANTIC) && !defined(OPENSSL_NO_ASM) && !defined(OPENSSL_NO_INLINE_ASM)
# if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64))
#  define CROR(x, s) _lrotr(x, s)
#  define CROL(x, s)  _lrotl(x, s)
# elif defined(__GNUC__) && __GNUC__>=2
#  if defined(__i386) || defined(__x86_64)
#  define CROL(a,n)    ({ register unsigned int ret;    \
                    asm ("roll %%cl,%0"    \
                        : "=r"(ret)    \
                        : "c"(n),"0"((unsigned int)(a))    \
                        : "cc");    \
                    ret;            \
                })
#  define CROR(a,n)    ({ register unsigned int ret;    \
                    asm ("rorl %%cl,%0"    \
                        : "=r"(ret)    \
                        : "c"(n),"0"((unsigned int)(a))    \
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

#define IV0 0x7380166f
#define IV1 0x4914b2b9
#define IV2 0x172442d7
#define IV3 0xda8a0600
#define IV4 0xa96f30bc
#define IV5 0x163138aa
#define IV6 0xe38dee4d
#define IV7 0xb0fb0e4e

#define T(j) (j < 16 ? 0x79cc4519 : 0x7a879d8a)

#define FF(j, X, Y, Z) (j < 16 ? (X ^ Y ^ Z) : ((X & Y) | (X & Z) | (Y & Z)))
#define GG(j, X, Y, Z) (j < 16 ? (X ^ Y ^ Z) : ((X & Y) | (~X & Z)))

#define P0(X) (X ^ CROL(X, 9) ^ CROL(X, 17))
#define P1(X) (X ^ CROL(X, 15) ^ CROL(X, 23))

#define HOST_l2c(l,c)   (*((c)++)=(unsigned char)(((l)>>24)&0xff),  \
             *((c)++)=(unsigned char)(((l)>>16)&0xff),  \
             *((c)++)=(unsigned char)(((l)>> 8)&0xff),  \
             *((c)++)=(unsigned char)(((l)    )&0xff))

#define HOST_c2l(c,l)    (l =(((unsigned long)(*((c)++)))<<24),        \
             l|=(((unsigned long)(*((c)++)))<<16),        \
             l|=(((unsigned long)(*((c)++)))<< 8),        \
             l|=(((unsigned long)(*((c)++)))    ))

#ifdef __cplusplus
}
#endif

#endif /* SM3_LOCL_H_ */
