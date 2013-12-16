#include <iostream>

thread_local struct tls {
    tls() {
        std::cout << "construct\n";
    }

    ~tls() {
        std::cout << "destruct\n";
    }

    void dont_opt_out() {}
} tls_obj;

int main(int argc, char **argv) {
    tls_obj.dont_opt_out();
}