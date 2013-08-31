#include <cstdio>

struct stringref {
    stringref(const char* p, int l) :ptr(p), len(l) {}
    template<int l> stringref(const char(&p)[l]) :ptr(p), len(l) {}
    const char* get() const {return ptr;}
    operator const char*() const {return ptr;}
    int length() const {return len;}
private:
    const char* ptr;
    int len;
};

stringref header_left[] =
{
    "         |          |  Raw  |  Raw  |   ",
    "         |          | Start |  End  | ",
    "Interval#| Duration | Point | Point |      ",
    "---------+----------+-------+-------+",
};

int main()
{
    const char* ptr = header_left[0]; //conversion possible
    printf("%d\n", header_left[0].length());
    printf("%d\n", header_left[1].length());
    printf("%d\n", header_left[2].length());
    printf("%d\n", header_left[3].length());
}