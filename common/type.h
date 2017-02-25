#pragma once

#ifndef __TYPE_H__
#define __TYPE_H__

#if defined(WIN64) || defined(_WIN64) || (__WORDSIZE == 64) || defined(x86_64) || defined(__x86_64) || defined(__x86_64__) || defined(amd64) || defined(__amd64) || defined(__amd64__)
#define __BUILD64__ 1
#endif

#if defined(WIN32) || defined(_WIN32) || (__WORDSIZE == 32) || defined(i386) || defined(__i386) || defined(__i386__) || defined(i486) || defined(__i486) || defined(__i486__) || defined(i586) || defined(__i586) || defined(__i586__) || defined(i686) || defined(__i686) || defined(__i686__)
#define __BUILD32__ 1
#endif

#ifndef __cplusplus //for C complier
#define bool unsigned char
#define BOOL unsigned char
#endif

#define S1 signed char
#define U1 unsigned char

#define S2 signed short int
#define U2 unsigned short int

#define S4 signed int
#define U4 unsigned int

#ifdef __BUILD64__
#define S8 signed long int
#define U8 unsigned long int
#endif

#ifdef __BUILD32__
#define S8 signed long long int
#define U8 unsigned long long int
#endif

#define s1 signed char
#define u1 unsigned char

#define s2 signed short int
#define u2 unsigned short int

#define s4 signed int
#define u4 unsigned int

#ifdef __BUILD64__
#define s8 signed long int
#define u8 unsigned long int
#endif

#ifdef __BUILD32__
#define s8 signed long long int
#define u8 unsigned long long int
#endif

#define SB signed char
#define UB unsigned char
#define DB unsigned char

#define SW signed short int
#define UW unsigned short int
#define DW unsigned short int

#define SD signed int
#define UD unsigned int
#define DD unsigned int

#ifdef __BUILD64__
#define SQ signed long int
#define UQ unsigned long int
#define DQ unsigned long int
#endif

#ifdef __BUILD32__
#define SQ signed long long int
#define UQ unsigned long long int
#define DQ unsigned long long int
#endif

#define SH signed long long int
#define UH unsigned long long int
#define DH unsigned long long int

#define sb signed char
#define ub unsigned char
#define db unsigned char

#define sw signed short int
#define uw unsigned short int
#define dw unsigned short int

#define sd signed int
#define ud unsigned int
#define dd unsigned int

#ifdef __BUILD64__
#define sq signed long int
#define uq unsigned long int
#define dq unsigned long int
#endif

#ifdef __BUILD32__
#define sq signed long long int
#define uq unsigned long long int
#define dq unsigned long long int
#endif

#define sh signed long long int
#define uh unsigned long long int
#define dh unsigned long long int

#define SL signed long int
#define UL unsigned long int
#define sl signed long int
#define ul unsigned long int

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__) || defined(__ELF__)
#define BYTE      unsigned char
#define SBYTE     signed char
#define UBYTE     unsigned char

#define WORD      unsigned short int
#define SWORD     signed short int
#define UWORD     unsigned short int

#define DWORD     unsigned int
#define SDWORD    signed int
#define UDWORD    unsigned int

#define SLONG     signed long int
#define ULONG     unsigned long int

#ifdef __BUILD64__
#define QWORD     unsigned long int
#define SQWORD    signed long int
#define UQWORD    unsigned long int
#endif

#ifdef __BUILD32__
#define QWORD     unsigned long long int
#define SQWORD    signed long long int
#define UQWORD    unsigned long long int
#endif

#define SLONGLONG signed long long int
#define ULONGLONG unsigned long long int
#endif

#define byte      unsigned char
#define sbyte     signed char
#define ubyte     unsigned char

#define word      unsigned short int
#define sword     signed short int
#define uword     unsigned short int

#define dword     unsigned int
#define sdword    signed int
#define udword    unsigned int

#define slong     signed long int
#define ulong     unsigned long int

#ifdef __BUILD64__
#define qword     unsigned long int
#define sqword    signed long int
#define uqword    unsigned long int
#endif

#ifdef __BUILD32__
#define qword     unsigned long long int
#define sqword    signed long long int
#define uqword    unsigned long long int
#endif

#define slonglong signed long long int
#define ulonglong unsigned long long int

#define INT8   signed char
#define UINT8  unsigned char

#define INT16  signed short int
#define UINT16 unsigned short int

#define INT32  signed int
#define UINT32 unsigned int

#ifdef __BUILD64__
#define INT64  signed long int
#define UINT64 unsigned long int
#endif

#ifdef __BUILD32__
#define INT64  signed long long int
#define UINT64 unsigned long long int
#endif

#define int8   signed char
#define uint8  unsigned char

#define int16  signed short int
#define uint16 unsigned short int

#define int32  signed int
#define uint32 unsigned int

#ifdef __BUILD64__
#define int64  signed long int
#define uint64 unsigned long int
#endif

#ifdef __BUILD32__
#define int64  signed long long int
#define uint64 unsigned long long int
#endif

#define STR char*
#define str char*
#define PVD void*
#define pvd void*
#define BUF void*
#define buf void*

#endif
