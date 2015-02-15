#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <vector>

int roundUp(int numToRound, int multiple) {
   return ((numToRound + multiple - 1) / multiple) * multiple;
}

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
    for(size_t i = 0; i < fields.size(); ++i) {
        offset = roundUp(offset, fields[i].alignment);
        std::cout << "field i" << i << ": s" << fields[i].size << ": a" << fields[i].alignment << ": o" << offset << "\n";
        offset += fields[i].size;
    }

    return 0;
}