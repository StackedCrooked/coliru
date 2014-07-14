#include <iostream>
#include <unordered_map>
#include <initializer_list>

using UMap = std::unordered_map<int,int&>;

UMap baz;
int main() {
    int a{1}, b{2}, c{3};
    auto il = std::initializer_list<UMap::value_type>{ {1,a},{2,b},{3,c} };
    baz = il;
}
