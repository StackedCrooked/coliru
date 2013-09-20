#include <cassert>

template<typename X, typename Y>
X bitcast(Y y) { return *(X*)&y; }

int main()
{
    assert(bitcast<bool>(1) != bitcast<bool>(2));
    assert(bitcast<bool>(1) == bitcast<bool>(2));
}