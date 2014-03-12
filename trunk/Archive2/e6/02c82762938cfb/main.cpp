#include <memory>



int main () {
    struct {} _ = std::pointer_traits<int>::element_type();
}