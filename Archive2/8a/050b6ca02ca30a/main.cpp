#include <cstdio>
#include <cwchar>

class A
{
    public: union { int i; };
    public:
        A(int x) : i(x) {}
};

int main()
{
    wchar_t buf[64];
    swprintf(buf, sizeof(buf), L"%f", 4.7f);
    wprintf(L"%ls\n", buf);
}
