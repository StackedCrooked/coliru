#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

namespace io {
    template<typename T>
    T read(std::istream& stream) {
        T t;
        stream.read(reinterpret_cast<char*>(&t), sizeof(T));
        return t;
    }
    
    template<typename T>
    void write(std::ostream& stream, T const& t) {
        stream.write(reinterpret_cast<char*>(&t), sizeof(T));
    }
}

int main() {
    // For the sake of this test.
    static_assert(sizeof(int) == 4, "sizeof(int) is not 4.");
    
    std::string data = {'\x20', 0, 0, 0, '\x30', 0, 0, 0};
    std::istringstream stream(data);
    
    int i = io::read<int>(stream);
    int j = io::read<int>(stream);
    
    assert(i == 0x20);
    assert(j == 0x30);
    
    return EXIT_SUCCESS;
}