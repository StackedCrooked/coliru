#include <iostream>

#include <forward_list>

template<typename T>
T getItem(typename std::forward_list<T>::const_iterator it) {
    return *it;
}


template<typename T>
void foo() {
    std::forward_list<T> list;
    auto item = getItem(list.cbegin());
}

template<typename T>
void bar(const std::forward_list<T>& list) {
    auto item = getItem(list.cbegin());
}

int main() {
    std::forward_list<int> list;
    foo<int>();
}