#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <memory>
#include <windows.h>

std::string Utf16ToUtf8(const std::wstring& s)
{
    std::string r(WideCharToMultiByte(CP_UTF8, 0, s.c_str(), s.size(), NULL, 0, NULL, NULL), '\0');
    WideCharToMultiByte(CP_UTF8, 0, s.c_str(), s.size(), &r[0], r.size(), NULL, NULL);
    return r;
}

struct CConsumer {
    CConsumer() 
        :Log(new std::wostringstream(std::ios::in | std::ios::out))
    {
        *Log << 'a';
    }
    ~CConsumer() 
    {
        delete Log;
    }
    CConsumer(const CConsumer& nocopy) = delete;
    CConsumer& operator=(const CConsumer& nocopy) = delete;


    static std::locale GetUtf8Locale()
    {
        static std::unique_ptr<std::codecvt_utf8_utf16<wchar_t>> code_cvt(new std::codecvt_utf8_utf16<wchar_t>(std::codecvt_mode::generate_header | std::codecvt_mode::little_endian));
        return std::locale(std::locale(), code_cvt.get());
    }

    void WriteToLog() {
        std::wostringstream* new_log = new std::wostringstream(std::ios::in | std::ios::out);
        new_log->imbue(CConsumer::GetUtf8Locale());

        std::wostringstream* old_log = (std::wostringstream*)Log;

        while((std::wostringstream *)::InterlockedCompareExchangePointer((PVOID volatile *)&Log, new_log, (PVOID)old_log) != new_log)
        {
            ::SleepEx(10, FALSE);
        }

        std::string logtext(Utf16ToUtf8(old_log->str()));

        delete new_log;
    }

    std::wostringstream* Log;
};

int main() {
    CConsumer c;
    for(int i=0; i<100000; ++i)
        c.WriteToLog();
    return 0;
}