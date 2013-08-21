#include <string>

class MyClass {
    std::string a;
    int b;
    std::pair<char, wchar_t> c;
public:
    // some other stuff...

    bool operator<(MyClass param){
        if(a != param.a) return a<param.a;
        if(b != param.b) return b<param.b;
        return c<param.c;
    }
};

#include <map>
int main() {
    std::map<MyClass, char> a;
}