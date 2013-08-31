#include <ctime>
int main() {
do {
    int x = time(nullptr);
    (void)x;
} while (x != -1); // x not in scope ;_;
}