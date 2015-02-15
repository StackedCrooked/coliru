#include <cstddef>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

struct field {
    std::size_t size;
    std::size_t alignment;
};

int main() {
    std::vector<field> fields{
        { 2, 2 },
        { 4, 4 },
        { 2, 2 },
        { 4, 8 },
    };

    std::size_t offset = 0;
    std::unordered_set<std::size_t> computed;
    while (computed.size() < fields.size()) {
        std::size_t max_alignment = 0;
        for (std::size_t i = 0; i < fields.size(); ++i) {
            if (computed.count(i)) {
                continue;
            }
            if (offset % fields[i].alignment == 0) {
                std::cout << "field i" << i << ": s" << fields[i].size << ": a" << fields[i].alignment << ": o" << offset << '\n';
                offset += fields[i].size;
                computed.insert(i);
                break;
            }
            if (fields[i].alignment > max_alignment) {
                max_alignment = fields[i].alignment;
            }
        }
        if (max_alignment != 0) {
            std::cout << "A " << offset << '\n';
            offset += offset - offset % -max_alignment;
            std::cout << "B " << offset << '\n';
        }
    }

    return 0;
}