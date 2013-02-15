#include <utility>

struct bar {    
    ~bar() {}
};

int main()
{
    bar a;
    bar b(std::move(a));
}
