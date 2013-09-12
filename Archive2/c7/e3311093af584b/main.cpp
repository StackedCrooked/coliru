#include <iostream>

namespace stuff {
    struct base {
        virtual void bar() {
            std::cout << "base";
        }
        void me() {
            base::bar();
        }
    };
    struct derived {
        void bar() override {
            std::cout << "derived";
        }
    };
}

int main() {
    stuff::derived d;
    d.me();
}
