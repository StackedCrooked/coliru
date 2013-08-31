#include <atomic>

int x, y, r1, r2;

void thread1() {
    x = 1;
    r1 = y;
}

void thread2() {
    y = 1;
    r2 = x;
}
