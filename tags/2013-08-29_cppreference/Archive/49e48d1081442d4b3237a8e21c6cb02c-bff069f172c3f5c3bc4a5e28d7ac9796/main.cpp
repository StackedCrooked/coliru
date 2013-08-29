#include <memory>

struct a {
    a() = delete;
};

int main() {
    // a* lol = new a[100];
    // delete lol; 
    // ^ this actually errors
    a* lol = std::get_temporary_buffer<a>(100).first; // :)
    std::return_temporary_buffer(lol);
}