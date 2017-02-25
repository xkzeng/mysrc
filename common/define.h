#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#ifdef __cplusplus //for C++ complier
  #define TRUE  1
  #define True  1
  #define FALSE 0
  #define False 0
#else              //for C complier
  #define true  1
  #define TRUE  1
  #define True  1
  #define false 0
  #define FALSE 0
  #define False 0
#endif

#define YES   1
#define yes   1
#define Yes   1
#define NO    0
#define no    0
#define No    0
#define OK    1
#define ok    1
#define Ok    1

#ifndef STR
#define STR(X) #X
#endif
  
#ifndef STRING
#define STRING(X) STR(X)
#endif

#define offset(TYPE,MEMBER) ((unsigned int)(&(((TYPE*)0)->MEMBER)))
#define OFFSET(type,member) ((unsigned int)(&(((type*)0)->member)))
#define baseof(TYPE,MEMBER,MPTR) ((TYPE*)(((char*)(MPTR))-offset(TYPE,MEMBER)))
#define BASEOF(type,member,mptr) ((type*)(((char*)(mptr))-OFFSET(type,member)))

#define Baseof(TYPE,MEMBER,mptr) ((TYPE*)(((unsigned long)(mptr))-offset(TYPE,MEMBER)))
#define BaseOf(TYPE,MEMBER,mptr) ((TYPE*)(((unsigned long)(mptr))-OFFSET(TYPE,MEMBER)))
#define baseOf(type,member,mptr) ((type*)(((unsigned long)(mptr))-offset(type,member)))

///////////////////////
//#define offset(TYPE,MEMBER) ((unsigned int)(&(((TYPE*)(0))->MEMBER)))
//#define OFFSET(TYPE,MEMBER) ((unsigned int)(&(((TYPE*)(0))->MEMBER)))
//#define baseof(TYPE,MEMBER,mptr) ((TYPE*)(((char*)(mptr))-(offset((TYPE),(MEMBER)))))
//#define BASEOF(TYPE,MEMBER,mptr) ((TYPE*)(((char*)(mptr))-(OFFSET((TYPE),(MEMBER)))))
//#define Baseof(TYPE,MEMBER,mptr) ((TYPE*)(((unsigned long)(mptr))-(offset((TYPE),(MEMBER)))))
//#define BaseOf(TYPE,MEMBER,mptr) ((TYPE*)(((unsigned long)(mptr))-(OFFSET((TYPE),(MEMBER)))))
///////////////////////

#endif
