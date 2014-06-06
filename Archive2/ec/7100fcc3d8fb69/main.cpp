#include <type_traits>

class S {
    S() = default;
    S(int i) : i_{i} {}
 
    int getI() const {
        return i_;
    }
 
private:
    int i_;
};

int main() {
    static_assert(std::is_pod<S>::value, "S is not POD!");   
}