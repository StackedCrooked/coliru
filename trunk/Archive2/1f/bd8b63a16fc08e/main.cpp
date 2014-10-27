#include <memory>

struct S {

    S(int X = 0, int Y = 0):x(X), y(Y){}

    int x;

	int y;

};

struct S2 {
    S2(int X = 0, int Y = 0):x(X), y(Y){}

    // S(const S&) {}
    // S& operator=(const S&) { return *this; }

    int x;
    int y;
    std::unique_ptr<int> ptr;
};

int main()
{
    S a;
    auto copy = a;
    
    S2 b;
    auto no_copy = b;
}