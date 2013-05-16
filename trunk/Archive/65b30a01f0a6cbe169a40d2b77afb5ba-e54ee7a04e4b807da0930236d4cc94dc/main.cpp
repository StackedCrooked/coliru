#include <vector>

struct foo {
    std::vector<int> x;

    template<typename T>
    void bar(T) {
        decltype(x)::value_type y;
    }
};

int main() {
    foo f;
    f.bar(0);
}