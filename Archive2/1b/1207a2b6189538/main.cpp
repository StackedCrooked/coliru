#include <iostream>
#include <map>

int main() {
    std::map<int, int> channel_map;
    for (unsigned ch = 0; ch < 3; ++ch) {
        channel_map[ch] = ch * 8;
    }
    
    // using ch again unintentionally (probably, due to copy-pasting)
    std::cout << channel_map[ch] << std::endl;
}