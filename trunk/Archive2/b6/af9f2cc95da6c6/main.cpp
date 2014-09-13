#include <stdio.h>

namespace outer {
    namespace first {
        void doit() {printf("Success!\n");}
    }
    namespace second {
        void doit() {first::doit();}
    }
}

int main() {
    outer::second::doit();
}