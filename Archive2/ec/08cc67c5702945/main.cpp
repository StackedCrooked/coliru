struct lol
{
    bool nope;
};
#include <cstdio>
#include <new>
int main ()
{
    int x = 0;
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x += 1000000;
    };
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x += 100000;
    };
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x += 10000;
    };
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x += 1000;
    };
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x += 100;
    };
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x += 10;
    };
    while (true)
    {
        lol* derp = new (std::nothrow) lol [x];
        if (!derp) break;
        delete [] derp;
        x++;
    };
    printf("No memory. (Last chunk size was %d.)",x);
    return 0;
};