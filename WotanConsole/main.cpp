#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <exception>

#ifdef _WIN32
#include "StdAfx.hpp"
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char ** argv)
{
	int ret = 1;

	try
	{
		ret = 0;
	}
	catch (std::exception & e)
	{

	}

	system("pause");
	return ret;
}
#endif
