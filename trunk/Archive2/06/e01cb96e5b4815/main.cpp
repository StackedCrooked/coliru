#include <utility>

template < int I, class=std::enable_if_t< (I<5) > >
struct foo
{
    typedef foo<I> type;
};

int main() {
    using f = foo<5>;
}