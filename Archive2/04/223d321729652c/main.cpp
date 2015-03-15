#include <iostream>
#include <string>
#include <vector>

using namespace std;

void* operator new(size_t num, int x, int y) {
    static int array[100][100];
    return &array[x][y];    
}


int main() {
    int* p = new (1,2) int;
    *p = 6;
    cout << *p;
    return 0;
}