#include <iostream>
#include <unordered_map>
#include <functional>

struct MyClass {
    char a;
};

int main() {
    std::unordered_map<int, std::reference_wrapper<MyClass> > MyMap;
    MyClass obj;
    obj.a = 'a';
    MyMap.emplace(1, obj);
    std::cout << MyMap[1].get().a;
}
