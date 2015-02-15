#include <algorithm>
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
        { 1, 1 },
        { 1, 1 },
        { 1, 1 },
        { 1, 1 },
        { 4, 4 },
        { 2, 2 },
        { 16, 8 },
        { 16, 8 },
        { 16, 8 },
        { 8, 8 },
        { 32, 8 },
        { 8, 8 },
        { 2, 2 },
        { 2, 2 },
    };
 
    std::sort(fields.begin(), fields.end(), [] (auto a, auto b) { return a.alignment < b.alignment; });
 
    std::size_t offset = 0;
    std::unordered_set<std::size_t> computed;
    for (std::size_t i = 0; i < fields.size(); ++i) {
        while (offset % fields[i].alignment != 0) {
            ++offset;
            std::cout << "PADDING\n";
        }
        std::cout << "field i" << i << ": s" << fields[i].size << ": a" << fields[i].alignment << ": o" << offset << "-" << offset + fields[i].size << '\n';
        offset += fields[i].size;
    }
 
    return 0;
}