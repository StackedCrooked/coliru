#include <string>
#include <sstream>
#include <windows.h>

inline void throw_windows_exception(const std::string& detail, DWORD code=GetLastError()) {
    std::string result(200,'\0');
    int size = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
        0, code, 0, &result[0], result.size(), 0);
    result.resize(size);

    if (result.size())
        throw std::runtime_error(result+" "+detail);
    else
        throw std::runtime_error("unknown windows error code: " + to_string(code)+" "+detail);

}

inline std::string wtoa(const std::wstring& s, int codepage=CP_UTF8) {
    std::string r(WideCharToMultiByte(codepage, WC_ERR_INVALID_CHARS, s.c_str(), s.size(), 0, 0, 0, 0), '\0');
    if (r.size()==0 && s.size()!=0) throw_windows_exception("error converting wide string to narrow");
    WideCharToMultiByte(codepage, WC_ERR_INVALID_CHARS, s.c_str(), s.size(), &r[0], r.size(), 0, 0);
    return r;
}

inline std::wstring atow(const std::string& s, int codepage=CP_UTF8) {
    std::wstring r(MultiByteToWideChar(codepage, WC_ERR_INVALID_CHARS, s.c_str(), s.size(), 0, 0), '\0');
    if (r.size()==0 && s.size()!=0) throw_windows_exception("error converting narrow string to wide: \""+s+"\"");
    MultiByteToWideChar(codepage, WC_ERR_INVALID_CHARS, s.c_str(), s.size(), &r[0], r.size());
    return r;
}