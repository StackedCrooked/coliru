#include <functional>

struct woof;

class test {
    std::reference_wrapper<woof> w;
};

struct woof {
    int a;
};

int main () {
    
}