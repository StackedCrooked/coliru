#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
#include <cstdint>

namespace io {
    template<typename T>
    T read(std::istream& stream) {
        T t;
        stream.read(reinterpret_cast<char*>(&t), sizeof(T));
        return t;
    }
    
    template<typename T>
    void write(std::ostream& stream, T&& t) {
        stream.write(reinterpret_cast<char*>(&t), sizeof(T));
    }
}

int main() {
    std::string data = {0x20, 0, 0, 0, 0x30, 0, 0, 0};
    
    // Reading from stream.
    std::istringstream stream(data);
    uint32_t i = io::read<uint32_t>(stream);
    uint32_t j = io::read<uint32_t>(stream);
    
    // Writing to stream.
    std::ostringstream output;
    io::write(output, 1);
    io::write(output, 56);
    
    // Assert that 2 integers have been written.
    assert(output.tellp() == (sizeof(int)*2));
    
    // Assert that the values have been read correctly.
    assert(i == 0x20);
    assert(j == 0x30);
    
    return EXIT_SUCCESS;
}