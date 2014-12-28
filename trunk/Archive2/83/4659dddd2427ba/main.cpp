#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<char> shit = {'A', 'I', 'T', 'S', 'A', 'W', 'N', 'G'};
    shit.resize(shit.size() + 1);
    std::copy(shit.begin(), shit.end() - 1, shit.begin() + 1);
    shit[0] = 'G';
    for (auto ch : shit) {
        std::cout.put(ch);
    }
}
