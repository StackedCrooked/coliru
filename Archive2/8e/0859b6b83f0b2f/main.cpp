#include <iostream>
#include <string>
#include <vector>

struct MemberInitializer {
    MemberInitializer(int nbr): d2(nbr*2), d1(d2*3) {}
    int d1;
    int d2;
};

struct TraditionalConstructor {
    TraditionalConstructor(int nbr) {
        d2 = nbr*2;
        d1 = d2*3;
    }
    int d1;
    int d2;
};

int main() {
    MemberInitializer mi(2);
    TraditionalConstructor tc(2);

    printf("mi.d1: %d\n", mi.d1);
    printf("tc.d1: %d\n", tc.d1);
}

