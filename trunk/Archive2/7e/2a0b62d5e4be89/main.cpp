#include <functional>
#include <cassert>

int main()
{
    using namespace std;

    function<int(void)> f = [] { return 42; };

    assert(f);
    assert(42 == f());

    f = nullptr;
    assert(!f);

    f = {};
    assert(!f);
}

