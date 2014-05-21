#include <iostream>

class file_handle {
public:
    file_handle() { std::cout << "open file\n"; }
    ~file_handle() { std::cout << "close file\n"; }
};

int main() {
    file_handle fh;
    return 0;
}
