#include <iostream>

struct whatever {
    ~whatever() {
        std::cout << "whatever";
    }
};

int main()
{
    new whatever;
}
