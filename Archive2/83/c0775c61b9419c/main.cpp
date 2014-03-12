#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

template<class Container>
void do_something(Container c) {
    typename Container::iterator it = c.begin();
    (decltype(it)) it;
    // etc
}

int main() {
    std::vector<int> x;
    std::list<int> y;
    std::deque<int> z;
    do_something(x);
    do_something(y);
    do_something(z);
    return 0;
}