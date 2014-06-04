#include <sstream>
#include <thread>
#include <cstdio>
#include <cstdarg>
#include <cwchar>
#include <cstdlib>
// #include <windows.h>

struct DebugOutImpl {
    DebugOutImpl(const char* location, int line, bool enabled_=true)
        :enabled(enabled_)
    {ss << location << line << "): " << std::this_thread::get_id() << " - "; }
    ~DebugOutImpl()  {ss << '\n'; OutputDebugStringA(ss.str().c_str());}
    void operator()(const char* msg) {if (enabled) ss<<msg;}
    void operator()(const wchar_t* msg) {if (enabled) ss<<wtoa(msg);}
    std::ostringstream& operator()() {return ss;}
    template<class char_type>
    void operator()(const char_type* format, ...) {
        if (enabled) {
            char_type buf[4096];
            va_list ap;
            va_start(ap,format);
            vsnprintf_s(buf, 4096, format, ap);
            va_end(ap);
            operator()(buf);
        }
    }
private:
    static std::string wtoa(const wchar_t* ptr, size_t len = -1){
        if (len == -1) len = wcslen(ptr);        
        std::string r(WideCharToMultiByte(CP_THREAD_ACP, 0, ptr, len, nullptr, 0, 0, 0), '\0');
        if (r.size()==0) throw std::system_error(GetLastError(), std::system_category());
        if (0 == WideCharToMultiByte(CP_THREAD_ACP, 0, ptr, len, &r[0], r.size(), 0, 0))
            throw std::system_error(GetLastError(), std::system_category(), "error converting wide string to narrow");
        return r;
    }
    static inline std::string wtoa(const std::wstring& wstr) {return wtoa(&wstr[0], wstr.size());}
    static int vsnprintf_s(char* buffer, int bufsize, const char* format, va_list ap) {return ::vsnprintf_s(buffer, bufsize, _TRUNCATE, format, ap);}
    static int vsnprintf_s(wchar_t* buffer, int bufsize, const wchar_t* format, va_list ap) {return ::vswprintf_s(buffer, bufsize, format, ap);}

    std::ostringstream ss;
    bool enabled;
};
#define DebugOut DebugOutImpl(__FILE__ "(", __LINE__)


int main() {
    // std::string name = "bob";
    // int age = 25;
    // DebugOut(L"HI");
    // DebugOut("my name is %s", name.c_str());
    // DebugOut() << name << " is age " << age;
    // One of the first C++ programs that Tiarna and I (AEM) wrote together around Tue April 22, 2014
    Chooks = 5 for $1
    Sheep = 1 for $1
    Cows = 1 for $5
    for (int iCows=1;iCows<99;iCows++)
	{
		for (int iSheep=1;iSheep<99;iSheep++)
		{
			for (int iChooks=1;iChooks<99;iChooks++)
			{
				if (iChooks+iSheep+iCows==100&&iChooks*0.2+iSheep*1+iCows*10==100)
				{
					int i=1;// found the solution
                    DebugOut() << " Chooks " << Chooks;
                    DebugOut() << " Sheep " << Sheep;
                    DebugOut() << " Cows " << Cows;
				}
			}
		}
	}
    return 0;
}