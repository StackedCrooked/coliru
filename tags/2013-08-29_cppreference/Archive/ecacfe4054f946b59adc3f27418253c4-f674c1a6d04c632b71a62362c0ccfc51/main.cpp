#include <iterator>
#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec) {
    std::copy(begin(vec), end(vec), std::ostream_iterator<int>(os, " "));
    return os;
}

// for convenience
template <typename T>
static inline void append(std::vector<T>& target, const std::vector<T>& buf)
{
    target.insert(end(target), begin(buf), end(buf));
}

template <typename T>
static inline void prepend(std::vector<T>& target, const std::vector<T>& buf)
{
    target.insert(begin(target), begin(buf), end(buf));
}

int main()
{
    std::vector<uint8_t> buf;
    
    std::vector<uint8_t> abc = { 0x0a, 0x0b, 0x0c };
    prepend(buf, abc);
    
    std::vector<uint8_t> def = { 0x0d, 0x0e, 0x0f };
    append(buf, def);
    
    std::cout << buf << std::endl;
}

