#include <iterator>

namespace foo {
    struct bar {};
    void begin(bar*);
}

int main()
{
    bar b;
    using std::begin;
    begin(&b);
}