#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <list>
#include <exception>
#include <string>
#include <string.h>

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
		// connect the gateway
		std::string appLocation = "C:\\Jts\\ibgateway\\964\\";
		std::string appName = "ibgateway.exe";
		std::list<DWORD> processes;
		Wotan::processHelper hlp;
		getProcesses(processes, appName);
		
		if (processes.size() > 0)
		{
			// process already started
			// quit all ?
			return 0;
		}
		
		// launch a new instance
		launchProcess(appLocation + appName);
	}
	catch (std::exception & e)
	{

	}

	system("pause");
	return ret;
}
#endif
