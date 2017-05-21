#pragma once
#ifndef PROCESS_HELPER_HPP_
#define PROCESS_HELPER_HPP_

#include <list>
#include <vector>

#include <windows.h>
#include <tlhelp32.h>

namespace Wotan
{
	typedef DWORD pid;

	struct windowDescription
	{
		HWND handle;
		std::string name;

	};

	struct EnumTopWindowsCallbackArgs
	{
		EnumTopWindowsCallbackArgs(Wotan::pid pid) : pid_(pid) {}
		const Wotan::pid pid_;
		std::vector<windowDescription> handles;
	};

	struct EnumChildWindowsCallbackArgs
	{
		EnumChildWindowsCallbackArgs(const windowDescription & desc) : desc_(desc) {}
		const windowDescription desc_;
		std::vector<windowDescription> handles;
	};

	static BOOL CALLBACK EnumTopWindowsCallback(HWND hnd, LPARAM lParam)
	{
		EnumTopWindowsCallbackArgs *args = (EnumTopWindowsCallbackArgs *)lParam;
		Wotan::pid windowPID;
		(void)::GetWindowThreadProcessId(hnd, &windowPID);

		if (windowPID == args->pid_)
		{
			int bufsize = GetWindowTextLength(hnd) + 1;
			LPSTR title = new CHAR[bufsize];
			GetWindowText(hnd, title, bufsize);

			windowDescription wd;
			wd.handle = hnd;
			wd.name = std::string(title);
			args->handles.push_back(wd);
		}

		return TRUE;
	}

	static BOOL CALLBACK EnumChildWindowsCallback(HWND hnd, LPARAM lParam)
	{
		EnumChildWindowsCallbackArgs *args = (EnumChildWindowsCallbackArgs *)lParam;

		// WE NEED TO FILTER BASED ON THE PARENT WINDOW
		if (IsChild(args->desc_.handle, hnd))
		{
			int bufsize = GetWindowTextLength(hnd) + 1;
			LPSTR title = new CHAR[bufsize];
			GetWindowText(hnd, title, bufsize);
			windowDescription wd;
			wd.handle = hnd;
			wd.name = std::string(title);
			args->handles.push_back(wd);
		}

		return TRUE;
	}

	class processHelper
	{
	public:
		void getProcessIds(std::list<pid> & pids, const std::string & processName);
		pid launchProcess(const std::string & path);
		bool terminateProcess(pid path, unsigned int & exitCode);
		std::vector<windowDescription> getToplevelWindows(Wotan::pid pid);
		std::vector<windowDescription> getChildWindows(const windowDescription & desc);
	};
}

#endif