#include <iostream>
#include <string>
#include <vector>

class Foo
{
    int x;
    
public:
    int& get() const { return x; }
};

int main() {
    const Foo obj;
}