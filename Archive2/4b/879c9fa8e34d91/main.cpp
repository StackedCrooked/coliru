#include <iostream>

const int size = 10;

#ifdef SORTED
void counter(int array[size]) {
    int counter = 0;
    
    for (int t = 0; t < size; ) {
        int prev = t;
        for (int r = t + 1; r < size && array[t] == array[r]; r++, t++)
        ;
        if (prev != t) {
            counter++;
        }
        else {
            t++;
        }
    }
    
    std::cout << counter << std::endl;        
}

#else
#include <map>

void counter(int array[size]) {
    int counter = 0;
    std::map<int, int> table;
    
    for (int t = 0; t < size; t++) {
        if (table[array[t]]++ == 1) {
            counter++;
        }
    }
    std::cout << counter << std::endl;        
}

#endif // SORTED


int main() {
    #ifdef SORTED
    int array[] = {1, 2, 3, 3, 4, 5, 6, 7, 7, 8};
    #else
    int array[] = {3, 4, 7, 2, 5, 6, 3, 5, 7, 1};
    #endif
    counter(array);
    return 0;
}
