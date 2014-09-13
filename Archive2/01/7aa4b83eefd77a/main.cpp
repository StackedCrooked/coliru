#include <stdio.h>

namespace outer {
    namespace first {
        struct X{};
    }
    namespace second {
        first::X doit() {printf("Success!\n");return{};}
    }
}

int main() {
    outer::second::doit();
}