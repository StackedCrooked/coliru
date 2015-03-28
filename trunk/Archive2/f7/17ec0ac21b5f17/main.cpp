#include <iostream>

class Test {
private:
    static int id;
public:
    static int get_id() { return id; }
};

int Test::id = 1;

int main() {
    Test testing;
    std::cout << testing.get_id() << '\n';
    
    return 0;
}
