#pragma once

#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#if defined(WIN64) || defined(_WIN64) || (__WORDSIZE == 64) || defined(x86_64) || defined(__x86_64) || defined(__x86_64__) || defined(amd64) || defined(__amd64) || defined(__amd64__)
#define __BUILD64__ 1
#endif

#if defined(WIN32) || defined(_WIN32) || (__WORDSIZE == 32) || defined(i386) || defined(__i386) || defined(__i386__) || defined(i486) || defined(__i486) || defined(__i486__) || defined(i586) || defined(__i586) || defined(__i586__) || defined(i686) || defined(__i686) || defined(__i686__)
#define __BUILD32__ 1
#endif

#ifdef __cplusplus //for C++ complier
typedef bool BOOL;
#endif

typedef signed char            S1;
typedef unsigned char          U1;

typedef signed short int       S2;
typedef unsigned short int     U2;

typedef signed int             S4;
typedef unsigned int           U4;

#ifdef __BUILD64__
typedef signed long int        S8;
typedef unsigned long int      U8;
#endif

#ifdef __BUILD32__
typedef signed long long int   S8;
typedef unsigned long long int U8;
#endif

typedef signed char            s1;
typedef unsigned char          u1;

typedef signed short int       s2;
typedef unsigned short int     u2;

typedef signed int             s4;
typedef unsigned int           u4;

#ifdef __BUILD64__
typedef signed long int        s8;
typedef unsigned long int      u8;
#endif

#ifdef __BUILD32__
typedef signed long long int   s8;
typedef unsigned long long int u8;
#endif

typedef signed char            SB;
typedef unsigned char          UB;
typedef unsigned char          DB;

typedef signed short int       SW;
typedef unsigned short int     UW;
typedef unsigned short int     DW;

typedef signed int             SD;
typedef unsigned int           UD;
typedef unsigned int           DD;

#ifdef __BUILD64__
typedef signed long int        SQ;
typedef unsigned long int      UQ;
typedef unsigned long int      DQ;
#endif

#ifdef __BUILD32__
typedef signed long long int   SQ;
typedef unsigned long long int UQ;
typedef unsigned long long int DQ;
#endif

typedef signed long long int   SH;
typedef unsigned long long int UH;
typedef unsigned long long int DH;

typedef signed char            sb;
typedef unsigned char          ub;
typedef unsigned char          db;

typedef signed short int       sw;
typedef unsigned short int     uw;
typedef unsigned short int     dw;

typedef signed int             sd;
typedef unsigned int           ud;
typedef unsigned int           dd;

#ifdef __BUILD64__
typedef signed long int        sq;
typedef unsigned long int      uq;
typedef unsigned long int      dq;
#endif

#ifdef __BUILD32__
typedef signed long long int   sq;
typedef unsigned long long int uq;
typedef unsigned long long int dq;
#endif

typedef signed long long int   sh;
typedef unsigned long long int uh;
typedef unsigned long long int dh;

typedef signed long int        SL;
typedef unsigned long int      UL;
typedef signed long int        sl;
typedef unsigned long int      ul;

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__) || defined(__ELF__)
typedef unsigned char          BYTE;
typedef signed char            SBYTE;
typedef unsigned char          UBYTE;

typedef unsigned short int     WORD;
typedef signed short int       SWORD;
typedef unsigned short int     UWORD;

typedef unsigned int           DWORD;
typedef signed int             SDWORD;
typedef unsigned int           UDWORD;

typedef signed long int        SLONG;
typedef unsigned long int      ULONG;

#ifdef __BUILD64__
typedef unsigned long int      QWORD;
typedef signed long int        SQWORD;
typedef unsigned long int      UQWORD;
#endif

#ifdef __BUILD32__
typedef unsigned long long int QWORD;
typedef signed long long int   SQWORD;
typedef unsigned long long int UQWORD;
#endif

typedef signed long long int   SLONGLONG;
typedef unsigned long long int ULONGLONG;
#endif

typedef unsigned char          byte;
typedef signed char            sbyte;
typedef unsigned char          ubyte;

typedef unsigned short int     word;
typedef signed short int       sword;
typedef unsigned short int     uword;

typedef unsigned int           dword;
typedef signed int             sdword;
typedef unsigned int           udword;

typedef signed long int        slong;
typedef unsigned long int      ulong;

#ifdef __BUILD64__
typedef unsigned long int      qword;
typedef signed long int        sqword;
typedef unsigned long int      uqword;
#endif

#ifdef __BUILD32__
typedef unsigned long long int qword;
typedef signed long long int   sqword;
typedef unsigned long long int uqword;
#endif

typedef signed long long int   slonglong;
typedef unsigned long long int ulonglong;

typedef signed char            INT8;
typedef unsigned char          UINT8;

typedef signed short int       INT16;
typedef unsigned short int     UINT16;

typedef signed int             INT32;
typedef unsigned int           UINT32;

#ifdef __BUILD64__
typedef signed long int        INT64;
typedef unsigned long int      UINT64;
#endif

#ifdef __BUILD32__
typedef signed long long int   INT64;
typedef unsigned long long int UINT64;
#endif

typedef signed char            int8;
typedef unsigned char          uint8;

typedef signed short int       int16;
typedef unsigned short int     uint16;

typedef signed int             int32;
typedef unsigned int           uint32;

#ifdef __BUILD64__
typedef signed long int        int64;
typedef unsigned long int      uint64;
#endif

#ifdef __BUILD32__
typedef signed long long int   int64;
typedef unsigned long long int uint64;
#endif

typedef char* STR;
typedef char* str;
typedef void* PVD;
typedef void* pvd;
typedef void* BUF;
typedef void* buf;

#endif
