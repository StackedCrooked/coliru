#include <stdlib.h>

struct Object {
    int color;
    Object() : color(rand()) { }
    void fillBg(int color = this->color);
};

int main() {
    Object();
}