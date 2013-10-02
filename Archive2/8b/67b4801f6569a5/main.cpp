#include <vector>
#include <iostream>
#include <cstdint>

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
            return_type value = bytes[byte_start];
            value >>= (start - byte_start * bits_per_byte);
            for(auto byte_i = byte_start + 1; byte_i < byte_end - 1; byte_i++) {
                value |= (bytes[byte_i] << (byte_i * bits_per_byte));
            }
            return value;
        }
};

int main() {
    BitValues<char> bits(std::vector<char>({'\x78', '\x00', '\x05', '\x5F', '\x00', '\x00', '\x0F', '\xA0'}));
    std::cout << "First byte: " << bits.get_bits<int32_t>(15, 28) << "\n";
    return 0;
}