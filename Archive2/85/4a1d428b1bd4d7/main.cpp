// Where i is an istream_iterator

template<class int_type>
int_type parse_int_le() {
    std::array<char, sizeof(int_type)> bytes;
    std::copy_n(i, sizeof(bytes), std::begin(bytes));
    i++;
    int_type value = 0;
    for(int byte_offset = sizeof(int_type) - 1; byte_offset >= 0; byte_offset--) {
        value |= bytes[byte_offset] << byte_offset * bits_per_byte;
    }
    return value;
}