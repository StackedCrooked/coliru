#include <vector>
#include <algorithm>

struct Bar
{
    int x = 0;
};

std::vector<Bar*> mBars;

void foo(Bar const * const bar)
{
    const int I_AM_CONST = 21;
    auto duplicateBars = std::remove_if(mBars.begin(), mBars.end(),
        [bar, I_AM_CONST] (const Bar* const &element) mutable
        {
            bar->x = 42;
            bar++;
            I_AM_CONST = 10;
            return bar == element;
        });

    mBars.erase(duplicateBars, mBars.end());
}

int main()
{
    Bar b;
    foo(&b);
}
