#include <stdexcept>

struct a_error : std::runtime_error{
    a_error() : runtime_error("a") {}
};
struct b_error : std::runtime_error {
    b_error() : runtime_error("b") {}
};

struct ab_error : a_error, b_error {
    ab_error() : a_error(), b_error() {}
};

int main(){
    try {
        throw ab_error();
    } catch(std::exception const& e) {
    }
}