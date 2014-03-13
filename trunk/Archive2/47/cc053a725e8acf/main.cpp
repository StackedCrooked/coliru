#include <iostream>
#include <functional>
using namespace std;

int data[] = { 1, 3, 4, 2, 7 };
const int N = 5;

#if 0
void print_if(int* from, int *to, function<bool(int)> when) {
    while (from < to) {
        int value = *from++;
        if(when(value)) 
            cout << value << endl;
    }
}
#else
template<typename Condition>
void print_if(int* from, int *to, Condition when) {
    while (from < to) {
        int value = *from++;
        if(when(value)) 
            cout << value << endl;
    }
}
#endif

bool even(int v) { return ((v % 2) == 0); }

struct Even {
    bool operator()(int v) const { return ((v % 2) == 0); }
};

int main() {
//    print_if(data, data+N, even);
    print_if(data, data+N, Even());
//    print_if(data, data+N, [](int v) { return ((v % 2) == 0); });
}
