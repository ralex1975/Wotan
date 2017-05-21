#pragma once

#include "stdafx.h"
#include "processHelper.hpp"

namespace Wotan
{
	void processHelper::getProcessIds(std::list<pid> & pids, const std::string & processName)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		// create a snapshot of the active processes
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				if (_stricmp(entry.szExeFile, processName.c_str()) == 0)
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
					pids.push_back(entry.th32ProcessID);
					CloseHandle(hProcess);
				}
			}
		}

		CloseHandle(snapshot);
	}

	pid processHelper::launchProcess(const std::string & path)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		BOOL success = FALSE;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		success = CreateProcess(
			path.c_str(),
			NULL,
			NULL,
			NULL,
			TRUE,
			0,
			NULL,
			NULL,
			&si,
			&pi);

		if (!success)
		{
			// error
			return 0;
		}
		else
		{
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			return pi.dwProcessId;
		}
	}

	bool processHelper::terminateProcess(pid path, unsigned int & exitCode)
	{
		DWORD dwDesiredAccess = PROCESS_TERMINATE;
		BOOL  bInheritHandle = FALSE;
		HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, path);
		if (hProcess == NULL)
			return FALSE;

		BOOL result = TerminateProcess(hProcess, exitCode);
		CloseHandle(hProcess);

		return result;
	}

	std::vector<windowDescription> processHelper::getToplevelWindows(Wotan::pid pid)
	{
		EnumTopWindowsCallbackArgs args(pid);
		if (::EnumWindows(&EnumTopWindowsCallback, (LPARAM)&args) == FALSE)
		{
			return std::vector<windowDescription>();				// XXX Log error here
		}
		return args.handles;
	}

	std::vector<windowDescription> processHelper::getChildWindows(const windowDescription & desc)
	{
		EnumChildWindowsCallbackArgs args(desc);
		if (::EnumChildWindows(desc.handle, &EnumChildWindowsCallback, (LPARAM)&args) == FALSE)
		{
			return std::vector<windowDescription>();				// XXX Log error here
		}
		return args.handles;
	}
}