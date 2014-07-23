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
    "ee", "i", "oo", "e", "u", "o", "a", "ough", "ay", "oy", "ow", "ou", "ie", "igh", "oi", "ea", 
};

std::vector<std::string> codas {
    "", "m", "p", "b", "f", "v", "th", "n", "t", "d", "s", "z", "sh", "k", "g", "r", "l",
    "lp", "lb", "lt", "ld", "lch", "lge", "lk",
    "rp", "rb", "rt", "rd", "rch", "rge", "rk", "rgue",
    "lf", "lve", "lth", "ls", "lsh",
    "rf", "rve", "rth", "rce", "rs", "rsh",
    "lm", "ln",
    "rm", "rn", "rl",
    "mp", "nt", "nd", "nch", "nge", "nk",
    "mph", "mth", "nth", "nce", "nze", "ngth",
    "ft", "sp", "st", "sk",
    "fth",
    "pt", "ct",
    "pth", "pse", "dth", "x",
    "lpt", "lfth", "lst", "lx",
    "rmth", "rpt", "rpse", "rts", "rst", "rct",
    "mpt", "mpes", "ndth", "nct", "nx",
    "xth", "xt",
};

std::string encode(std::uint16_t u) {
    int onset_code = ((u & 0xF300) >> 10) % onsets.size();
    int nucleus_code = ((u & 0x03C0) >> 6) % nuclei.size();
    int coda_code = ((u & 0x003F) >> 0) % codas.size();
    
    return onsets[onset_code] + nuclei[nucleus_code] + codas[coda_code];
}

std::uint16_t decode(std::string) {
    return 0; // TODO
}

#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
    if(argc < 3) return 17;
    if(argv[1][0] == 'e') {
        std::stringstream ss(argv[2]);
        std::uint16_t u;
        while(ss >> std::hex >> u) {
            std::cout << encode(u) << ' ';
        }
        if(!ss.eof()) return 23;
    } else if(argv[1][0] == 'd') {
        std::string s(argv[2]);
        std::cout << decode(s);
    } else return 17;
}
