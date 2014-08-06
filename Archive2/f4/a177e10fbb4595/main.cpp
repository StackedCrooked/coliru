#include <iostream>
#include <boost/optional/optional_io.hpp>
#include <boost/signals2.hpp>

int foo(int i) { std::cout << "(foo)"; return i*2; }
int bar(int i) { std::cout << "(bar)"; return i+2; }

template <typename Sig, typename F> void try_connect(Sig& sig, F&& f) {
    if (!sig.num_slots()) sig.connect(std::forward<F>(f));
}

template <typename Sig, typename F> void re_connect(Sig& sig, F&& f) {
    sig.disconnect_all_slots();
    sig.connect(std::forward<F>(f));
}

int main()
{
    using namespace boost::signals2;
    signal<int(int)> sig;
    std::cout << sig(42) << "\n"; // should be none ("--")

    try_connect(sig, foo);
    std::cout << sig(42) << "\n"; // should return 42*2

    try_connect(sig, bar);
    std::cout << sig(42) << "\n"; // should still return 42*2
    
    re_connect(sig, bar);
    std::cout << sig(42) << "\n"; // should return 42+2
}
