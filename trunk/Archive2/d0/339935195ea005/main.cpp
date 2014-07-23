#include <vector>
#include <string>
#include <random>
#include <cstdint>

std::vector<std::string> onsets {
    "", "m", "p", "b", "f", "v", "th", "n", "t", "d", "s", "z", "ch", "j", "sh", "y", "k", "g", "w", "r", "l", "h", "si", "ti",
    "pl", "bl", "cl", "gl", "pr", "br", "tr", "dr", "cr", "gr", "tw", "dw", "gu", "qu", "pu",
    "fl", "sl", "thl", "fr", "thr", "shr", "wh", "sw", "thw",
    "sp", "st", "sk",
    "sm", "sn",
    "sph", "sth",
    "spl", "scl", "spr", "str", "scr", "squ",
    "sphr",
    "psh", "fw", "vr",
};

std::vector<std::string> nuclei {
    "a", "e", "i", "o", "u",
    // other stuff
};

std::vector<std::string> codas {
    "", "m", "p", "b", "f", "v", "th", "n", "t", "d", "s", "z", "sh", "k", "g", "r", "l", "si", "ti",
    // other stuff
};

std::string make_syllable(std::uint16_t u) {
    int onset_code = ((u & 0xF300) >> 10) % onsets.size();
    int nucleus_code = ((u & 0x03C0) >> 6) % nuclei.size();
    int coda_code = ((u & 0x003F) >> 0) % codas.size();
    
    return onsets[onset_code] + nuclei[nucleus_code] + codas[coda_code];
}

#include <iostream>

int main(int argc, char** argv) {
    std::cout << make_syllable(0x1234) << make_syllable(0x4321);
}
