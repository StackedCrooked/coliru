#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>

std::wstring mb2ws(const std::string& s)
{
    size_t dlen = std::mbstowcs(NULL, s.c_str(), 0) + 1;
    std::vector<wchar_t> dst(dlen);
    std::mbstowcs(&dst[0],s.c_str(),dlen);
    std::wstring result = &dst[0];
    return result;
}

int main()
{
    setlocale(LC_CTYPE, "en_US.UTF-8");

    std::string s = "Forlì";
    std::wstring ws = mb2ws(s);
    
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
        printf("%d ", static_cast<int>(*it));
    fputc('\n', stdout);
    
    for (std::wstring::const_iterator it = ws.begin(); it != ws.end(); ++it)
        printf("%d ", static_cast<int>(*it));
    fputc('\n', stdout);
    return 0;
}