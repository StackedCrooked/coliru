#include <iostream>
#include <locale>

int main (int argc, char **argv) {
    try {
        std::locale * l1 = new std::locale("de_DE.UTF-8");
        delete l1;

        std::locale l2("de_DE.UTF-8");

    } catch(...) {
        return 0;
    }
    return 0;
};