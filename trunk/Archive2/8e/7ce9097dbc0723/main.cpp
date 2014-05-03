#include <iostream>

struct GIF{};
struct Silas{};

int main() {
    Silas *silas = nullptr;
    
    
    std::cout << reinterpret_cast<GIF*>(silas);
}