#include <iostream>

int wizard(int x, int y, int z) {
    if (x+y > 2) {
        return (x+y) * wizard(x+y-1, 0, z);//recursive call
    } else if (x+y == 2) {
        return 2 * z;//termination case 
    } else {
        return 0;//exceptional case
    }
}

int main() {
    std::cout << wizard(2, 3, 4) << '\n';
    std::cout << wizard(3, 3, 3) << '\n';
    std::cout << wizard(3, 2, 1) << '\n';
}