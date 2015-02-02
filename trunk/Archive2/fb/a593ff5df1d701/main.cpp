#include <thread>
#include <iostream>

int main() {
    int data = 0;
    std::thread writer{[&]{
        for (int i = 0; i < 100; ++i) {
            ++data;
        }
    }};
    writer.detach();
    std::thread reader{[&]{
        for (int i = 0; i < 100; ++i) {
            std::cout << "data = " << data << std::endl;
        }
    }};
    reader.detach();
}
