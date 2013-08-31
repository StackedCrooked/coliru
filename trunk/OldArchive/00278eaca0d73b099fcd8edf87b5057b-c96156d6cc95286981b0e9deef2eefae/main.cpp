#include <string>
#include <tuple>

class MyClass {
    std::string a;
    int b;
    std::pair<char, wchar_t> c;
public:
    // some other stuff...

    bool operator<(MyClass param){
        return std::tie(a, b, c)<std::tie(param.a, param.b, param.c);
    }
};

#include <map>
int main() {
    std::map<MyClass, char> a;
}