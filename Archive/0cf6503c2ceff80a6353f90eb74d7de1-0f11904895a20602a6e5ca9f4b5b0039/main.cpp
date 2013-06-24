#include <iostream>
#include <vector>

template<class Stream, class Cont>
void print(Stream& out, Cont&& cont) {
    auto first = std::begin(std::forward<Cont>(cont));
    auto last = std::end(std::forward<Cont>(cont));
    out << '[';
    if(first != last) {
        out << *first++;
    }
    while(first != last) {
        out << ", " << *first++;
    }
    out << ']';
}



int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    float f[] = {11.2f, 43.f, 10.1f};
    print(std::cout, v);
    std::cout << '\n';
    print(std::cout, f);
}