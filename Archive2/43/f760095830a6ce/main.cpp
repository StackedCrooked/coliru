#include <fstream>

class binary_reader {
private:
    std::ifstream reader;
public:
    binary_reader() = default;
    binary_reader(const std::string& filename): reader(filename, std::ios_base::binary | std::ios_base::in) {}

    void open(const std::string& filename) {
        reader.open(filename, std::ios_base::binary | std::ios_base::in);
    }

    void seek(size_t offset, std::ios_base::seekdir dir) {
        reader.seekg(offset, dir);
    }

    void seek(size_t position) {
        reader.seekg(position);
    }

    int tell() {
        return reader.tellg();
    }

    bool eof() const {
        return reader.eof();
    }

    bool bad() const {
        return reader.bad();
    }

    bool good() const {
        return reader.good();
    }

    bool fail() const {
        return reader.fail();
    }

    bool is_open() const {
        return reader.is_open();
    }

    void clear() {
        reader.clear();
    }

    template<typename T>
    void read(T& t) {
        reader.read(reinterpret_cast<char*>(&t),sizeof(T));
    }
    
    template<typename T, unsigned N>
    void read(T (&arr)[N]) {
        reader.read(reinterpret_cast<char*>(arr), N);
    }
    
    template<typename T>
    void read(T& t, unsigned N) {
        reader.read(reinterpret_cast<char*>(t), N);
    }
};

int main() {}