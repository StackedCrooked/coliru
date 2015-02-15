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
 
std::size_t round_up(std::size_t num, std::size_t factor) {
    return factor - num % factor;
}
 
int main() {
    std::vector<field> fields{
        { 8, 2 },
        { 1, 1 },
        { 1, 1 },
        { 1, 1 },
        { 1, 1 },
        { 4, 4 },
        { 2, 2 },
        { 4, 8 },
        { 4, 8 },
        { 8, 8 },
        { 4, 8 },
        { 4, 8 },
        { 4, 8 },
        { 2, 2 },
        { 2, 2 },
    };
 
    std::sort(fields.begin(), fields.end(), [] (auto a, auto b) { return a.alignment > b.alignment; });
 
    std::size_t offset = 0;
    std::unordered_set<std::size_t> computed;
    for (std::size_t i = 0; i < fields.size(); ++i) {
        auto padding = round_up(offset, fields[i].alignment);
        offset += padding;
        std::cout << "PADDING: " << padding << '\n';
        std::cout << "field i" << i << ": s" << fields[i].size << ": a" << fields[i].alignment << ": o" << offset << "-" << offset + fields[i].size << '\n';
        offset += fields[i].size;
    }
 
    return 0;
}