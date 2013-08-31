#include <vector>
template<typename T>
class MyClass {
    T a;
};

class OtherClass {
public:
    template<typename T>
    std::vector<MyClass<T>> member; //error
};

int main() {
    OtherClass v;
    v.member.push_back(MyClass<int>()); //I wish.
}