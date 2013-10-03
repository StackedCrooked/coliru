#include <vector>
#include <iostream>
#include <cstdint>
#include <bitset>

template<class byte_type = char>
class BitValues {
    private:
    std::vector<byte_type> bytes;
    public:
        static const auto bits_per_byte = 8;
        BitValues(std::vector<byte_type> bytes) : bytes(bytes) {
        }
        template<class return_type>
        return_type get_bits(int start, int end) {
            auto byte_start = (start - (start % bits_per_byte)) / bits_per_byte;
            auto byte_end = (end - (end % bits_per_byte)) / bits_per_byte;
            auto byte_width = byte_end - byte_start;
            return_type value = 0;
            
            unsigned char first = bytes[byte_start];
            first &= (0xff >> start % 8);
            return_type first_wide = first;
            first_wide <<= byte_width;
            value |= first_wide;
            
            for(auto byte_i = byte_start + 1; byte_i <= byte_end; byte_i++) {
                auto byte_offset = (byte_width - byte_i) * bits_per_byte;
                unsigned char next_thin = bytes[byte_i];
                return_type next_byte = next_thin;
                next_byte <<= byte_offset;
                value |= next_byte;
            }
            value >>= (((byte_end + 1) * bits_per_byte) - end) % bits_per_byte;
            
            return value;
        }
};

int main() {
    BitValues<char> bits(std::vector<char>({'\x78', '\xDA', '\x05', '\x5F', '\x8A', '\xF1', '\x0F', '\xA0'}));
    std::cout << bits.get_bits<unsigned>(15, 29) << "\n";
    return 0;
}