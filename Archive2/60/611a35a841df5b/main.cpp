#include <vector>
#include <algorithm>

struct Bar
{
    int x = 0;
};

std::vector<Bar*> mBars;

void foo(Bar const * const bar)
{
    auto duplicateBars = std::remove_if(mBars.begin(), mBars.end(),
        [bar] (const Bar* const &element)
        {
            bar->x = 42;
            return bar == element;
        });

    mBars.erase(duplicateBars, mBars.end());
}

int main()
{
    Bar b;
    foo(&b);
}
