#include <iostream>
#include <cassert>
#include <stdexcept>
#include <climits>
#include <sstream>

class bitbuffer {
    char buffer;
    unsigned char held_bits;
    std::istream* str;
public:
    bitbuffer(std::istream& stream) :buffer(0), held_bits(0), str(&stream) {}
    unsigned long long read(unsigned bits) { 
        assert(bits<64u);
        unsigned long long result = 0;
        //if the buffer doesn't hold enough bits
        while (bits > held_bits) {
            //grab the all bits in the buffer
            bits -= held_bits;
            result |= ((unsigned long long)buffer) << bits;
            //reload the buffer
    		if (!*str) throw std::runtime_error("reached end of stream!");
            str->get(buffer);
            held_bits = (char)str->gcount() * CHAR_BIT;
        }
        //append the bits left to the end of the result
        result |= buffer >> (held_bits-bits);
        //remove those bits from the buffer
        held_bits -= bits;
        buffer &= (1ull<<held_bits)-1;
        return result;
    };
};

int main() {
    std::stringstream ss ("65535");
	bitbuffer reader(ss);  //0x3535353335
	assert(reader.read(4) == 0x3);
	assert(reader.read(4) == 0x6);
	assert(reader.read(8) == 0x35);
	assert(reader.read(1) == 0x0);
	assert(reader.read(1) == 0x0);
	assert(reader.read(1) == 0x1);
	assert(reader.read(1) == 0x1);
	assert(reader.read(4) == 0x5);
	assert(reader.read(16) == 0x3335);
	assert(reader.read(8) == 0x0A);
    ss.str("FFFFFFFF");
	assert(reader.read(64) == 0x4646464646464646);
	return 0;
}
