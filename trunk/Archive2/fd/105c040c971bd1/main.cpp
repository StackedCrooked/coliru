#include <iostream>

struct tls {
    ~tls() { std::cout << "destroy tls\n"; }
    void dont_opt_out() {}
};

thread_local tls tls_obj;

int main(int argc, char **argv) {
    tls_obj.dont_opt_out();
}
