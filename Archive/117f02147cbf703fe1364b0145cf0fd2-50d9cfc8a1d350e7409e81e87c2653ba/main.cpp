#include <iostream>
#include <Windows.h>
#include <AclAPI.h>
#include <string>

std::string GetLastErrorString() {
  DWORD error = GetLastError();
  if (error)
  {
    LPVOID lpMsgBuf;
    DWORD bufLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL ) * 2;
    if (bufLen)
    {
      LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
      std::string result(lpMsgStr, lpMsgStr+bufLen);
      
      LocalFree(lpMsgBuf);

      return result;
    }
  }
  return std::string();
}
void GenerateWin32Error() {
    auto es = GetLastErrorString();
	throw std::runtime_error(es);
}

int main() {
	std::cout << "Starting\n";

	std::cout << "Gaining security privelages...\n";
	//SetSecurityInfo(GetCurrentProcess(),
	//	            SE_PROCESS

	std::cout << "Finding window...\n";
	LPWSTR window_name = L"Untitled - Unreal Development Kit (64-bit, DX9)";
	HWND window_handle = FindWindowEx(nullptr, nullptr, nullptr, window_name);
	if(window_handle == nullptr) {
		GenerateWin32Error();
	} else {
		std::cout << "Done.\n";
	}

	std::cout << "Finding process and thread associated with window...\n";
	DWORD proc_id = 0;
	DWORD thread = 0;
	thread = GetWindowThreadProcessId(window_handle, &proc_id);
	if(thread == 0) {
		GenerateWin32Error();
	};

	std::cout << "Getting the process handle...\n";
	HANDLE proc_handle = OpenProcess(PROCESS_VM_OPERATION,
					                             false,
												 proc_id);
	if(proc_handle == NULL) {
		GenerateWin32Error();
	}

	std::cout << "Getting the address of LoadLibrary function...\n";
	auto load_library = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA"));
	if(load_library == NULL) {
		GenerateWin32Error();
	}

	std::cout << "Allocating memory for dll name to load in remote process...\n";
	std::string dllname("DXTestDll.dll");
	auto remote_string = reinterpret_cast<LPVOID>(VirtualAllocEx(proc_handle, nullptr, dllname.size(), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE));
	if(remote_string == NULL) {
		GenerateWin32Error();
	}
	
	std::cout << "Writing dll name string to recently allocated memory...\n";
	auto write_success = WriteProcessMemory(proc_handle, remote_string, dllname.c_str(), dllname.size(), nullptr);
	if(write_success == 0) {
		GenerateWin32Error(); // Error here because no privelage
	}
	

	std::cout << "Creating a remote thread in the process...\n";
	auto success = CreateRemoteThreadEx(proc_handle, //process handle
		                                nullptr, //default security descriptor
					               	    0, //default stack size
										reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library), // start the thread by loading our dll
						                reinterpret_cast<LPVOID>(remote_string), //pass our dll name as paremeter
						                0, //run thread immediately
										0, //Attribute list
						                nullptr); // Don't need to receive the thread identifier
	
	system("pause");
	return 0;
}
