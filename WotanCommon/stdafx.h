// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#ifdef _MSC_VER

#ifdef TWSAPIDLL
#ifndef TWSAPIDLLEXP
#define TWSAPIDLLEXP __declspec(dllexport)
#endif
#endif

#define assert ASSERT
#if _MSC_VER == 1900
#else
#define snprintf _snprintf
#endif
#include <WinSock2.h>
#include <Windows.h>
#define IB_WIN32

#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifndef TWSAPIDLLEXP
#define TWSAPIDLLEXP
#endif

// TODO: reference additional headers your program requires here
