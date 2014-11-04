#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

struct gen
{
    gen(int n, int increase) : n(n), increase(increase) {}
    
    operator int() const { return n; }
    gen& operator ++() { n += increase; return *this; }
private:
    int n;
    int increase;
};

int main()
{
    const int N1 = 10;    // This can vary
    const int offset = 3; // This also can vary
    std::vector<int> chans(10);
    std::iota(chans.begin(), chans.end(), gen(offset, N1));
    std::copy(chans.begin(), chans.end(), std::ostream_iterator<int>(std::cout, " "));
}
