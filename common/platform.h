#pragma once

#ifndef __PLATFORM_H__   //__PLATFORM_H__ begin
#define __PLATFORM_H__

/****** COMPILER ******/

/****** CPU ******/
#if defined(x86_64) || defined(__x86_64) || defined(__x86_64__)
#define _ARCH_IA64_  1
#endif

#if defined(amd64) || defined(__amd64) || defined(__amd64__)
#define _ARCH_AMD64_ 1
#endif

#if defined(i386) || defined(__i386) || defined(__i386__)
#define _ARCH_I386_  1
#endif

#if defined(i486) || defined(__i486) || defined(__i486__)
#define _ARCH_I486_  1
#endif

#if defined(i586) || defined(__i586) || defined(__i586__)
#define _ARCH_I586_  1
#endif

#if defined(i686) || defined(__i686) || defined(__i686__)
#define _ARCH_I686_  1
#endif

#if defined(__arm__)
#define _ARCH_ARM_   1
#endif

/****** OS ******/
#if defined(WIN32) || defined(_WIN32)
#define WINDOW32 1
#endif

#if defined(WIN64) || defined(_WIN64)
#define WINDOW64 1
#endif

#ifdef _WINDOWS //GUI-APP
#define WIN_GUI 1
#endif

#ifdef _CONSOLE //CGI-APP
#define WIN_CGI 1
#endif

#ifdef _WIN32_WINDOWS //MFC-APP
#define WIN_MFC 1
#endif

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__ELF__)
#define UNIX  1
#endif

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__) || defined(__ELF__)
#define LINUX 1
#endif

#endif                   //__PLATFORM_H__ begin
