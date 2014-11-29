#include <iostream>
using namespace std;

struct Logger {
    Logger(int) { cout << "Construct " << this << '\n'; }
    Logger(const Logger&) { cout << "Copy construct " << this << '\n'; }
    ~Logger() { cout << "Destruct " << this << '\n'; }
};

int f(Logger)
{
    cout << "Inside f\n";
    return 0;
}

int main()
{
    f(f(f(10)));
}