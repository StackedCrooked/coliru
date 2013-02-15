#include <vector>
#include <fstream>

int main() {
    std::vector<std::fstream> v;
    v.emplace_back("invalid_file_name");
    return 0;
}