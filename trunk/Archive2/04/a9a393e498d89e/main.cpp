#include <iostream>
#include <string>
#include <list>
#include <vector>

template<class... Args, template<class...> class Container>
void sort(Container<Args...>&) {
    std::cout << "With a generic Container\n";
}

template<class... Args>
void sort(std::list<Args...>&) {
    std::cout << "With a list Container\n";
}

int main() {
    std::vector<int> a;
    std::list<int> b;
    sort(a);
    sort(b);
}