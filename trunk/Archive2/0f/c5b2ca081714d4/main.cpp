#include <thread>

struct A {

    static void foo(char*, char*) {}

    void bar() {

        char* char_start = (char*) malloc(100 * sizeof(char));
        char* char_end = char_start + (100 * sizeof(char)) - 1;

        std::thread t(foo, char_start, char_end);
        t.join();

        return;
    }
};

int main () {A().bar();}