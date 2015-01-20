#include <string>
#include <list>
#include <iostream>

template <typename T>
T & ListGet(std::list<T> &List, int Position)
{
    auto i = List.begin();
    std::advance(i, Position);
    return *i;
}

int main() {
    std::list<int> ints{1, 2, 3};
    std::list<std::string> words{"one", "two", "three"};
    auto second_int = ListGet(ints, 1);
    auto third_word = ListGet(words, 2);
    std::cout << second_int << ", " << third_word;
}
