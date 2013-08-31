#include <iostream>
#include <windows.h>

template<typename Ret, typename... Args>
Ret callStdcallDllFunction(const std::wstring &dllName, const std::string &funcName, Args... args) {
    auto dll = LoadLibraryW(dllName.c_str());
    if (!dll) {
        std::cout << "LoadLibraryW error\n";
        return {};
    }

    using FuncType = Ret(__stdcall *)(Args...);
    auto func = (FuncType)GetProcAddress(dll, funcName.c_str());
    if (!func) {
        std::cout << "GetProcAddress error\n";
        FreeLibrary(dll);
        return {};
    }

    auto ret = func(std::forward<Args>(args)...);

    if (!FreeLibrary(dll)) {
        std::cout << "FreeLibrary error\n";
    }

    return ret;
}

template<typename... Args>
void callStdcallDllFunction(const std::wstring &dllName, const std::string &funcName, Args... args) {
    auto dll = LoadLibraryW(dllName.c_str());
    if (!dll) {
        std::cout << "LoadLibraryW error\n";
        return;
    }

    using FuncType = void(__stdcall *)(Args...);
    auto func = (FuncType)GetProcAddress(dll, funcName.c_str());
    if (!func) {
        std::cout << "GetProcAddress error\n";
        FreeLibrary(dll);
        return;
    }

    func(std::forward<Args>(args)...);

    if (!FreeLibrary(dll)) {
        std::cout << "FreeLibrary error\n";
    }
}

int main() {
    int result = callStdcallDllFunction<int, HWND, const wchar_t *, const wchar_t *, UINT>(L"user32", "MessageBoxW", nullptr, nullptr, nullptr, 0);
    callStdcallDllFunction(L"user32", "MessageBoxW", nullptr, nullptr, nullptr, 0);
}
