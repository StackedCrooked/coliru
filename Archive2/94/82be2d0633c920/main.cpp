#include <sstream>

int main(int argc, char** argv) {
    std::basic_ostringstream<char32_t> stream;
    stream << stream.widen('0');
}
