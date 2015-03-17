#include <iostream>
using namespace std;

class apple {
    public:
    int color;
};

apple & SingleApple() {
    static apple a;
    return a;
}

int main() {
    {
        SingleApple().color = 100;
    }
    
    cout << SingleApple().color;
    return 0;
}