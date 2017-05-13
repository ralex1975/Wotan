#pragma once
#ifndef PROCESS_HELPER_HPP_
#define PROCESS_HELPER_HPP_

#include <list>

#include <windows.h>
#include <tlhelp32.h>

namespace Wotan
{
	class processHelper
	{
	public:
		void getProcessIds(std::list<unsigned int> & pids, const std::string & processName)
		{
			PROCESSENTRY32 entry;
			entry.dwSize = sizeof(PROCESSENTRY32);

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

		unsigned int launchProcess(const std::string & path)
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
			}
		}
	};
}

#endif

