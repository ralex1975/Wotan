#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <list>
#include <exception>
#include <string>
#include <string.h>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#ifdef _WIN32
#include "StdAfx.hpp"
#include <Windows.h>
#include <tlhelp32.h>
#else
#include <unistd.h>
#endif

#include "application/processHelper.hpp"

int main(int argc, char ** argv)
{
	int ret = 1;

	try
	{

	}
	catch (std::exception & e)
	{

	}

	system("pause");
	return ret;
}
#endif
