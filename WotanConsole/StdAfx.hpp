#pragma once
#ifndef STD_AFX_HPP_
#define STD_AFX_HPP_

#include <boost/system/config.hpp>

#ifdef _MSC_VER

#ifdef TWSAPIDLL
#ifndef TWSAPIDLLEXP
#define TWSAPIDLLEXP __declspec(dllexport)
#endif
#endif

//#define assert ASSERT
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

#endif