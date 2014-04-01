#include <cstdlib>

int main() {
    int *i = static_cast<int*>(malloc(sizeof(int)));
    if (i==NULL) {
        free(i);
    }
}
