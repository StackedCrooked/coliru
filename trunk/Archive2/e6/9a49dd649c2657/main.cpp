#include <string>
#include <vector>

struct A {
private:
    struct B {
        int a;
        std::string s;
    };
public:
    std::vector<B> collection;
    template<typename... Ts>
    void add(Ts... ts) {
        collection.push_back({ts...});
    }
};

int main () {
    A a;
    a.add(1, "");
    //a.add("", "");//breaks
}