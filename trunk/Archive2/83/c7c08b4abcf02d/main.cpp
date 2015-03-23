#include <array>
#include <algorithm>
#include <cassert>

class Perfect_Hash {
    /* C++ code produced by gperf version 3.0.4 */
    /* Command-line: gperf -L C++ -7 -C -E -m 100 table  */
    /* Computed positions: -k'1-4' */

    /* maximum key range = 16, duplicates = 0 */
  private:
    static inline unsigned int hash(std::array<char, 4> const &str)
    {
        static const unsigned char asso_values[] = {
            27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
            27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 15, 7,  3,  1,  0,  27,
            27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
            27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
            27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27};
        return asso_values[(unsigned char)str[3] + 2] + asso_values[(unsigned char)str[2] + 1] +
               asso_values[(unsigned char)str[1] + 3] + asso_values[(unsigned char)str[0]];
    }

  public:
    static char hexchar(std::array<char, 4> const &binary_nibble)
    {
        static char const lut[] = "???????????fbead9c873625140";
        assert(Perfect_Hash::validate(binary_nibble)); // for DEBUG only
        return lut[hash(binary_nibble)]; // no validation!
    }
    static bool validate(std::array<char, 4> const &str)
    {
        static constexpr std::array<char, 4> vocab[] = {
            {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
            {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
            {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
            {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
            {{'1', '1', '1', '1'}}, {{'1', '0', '1', '1'}},
            {{'1', '1', '1', '0'}}, {{'1', '0', '1', '0'}},
            {{'1', '1', '0', '1'}}, {{'1', '0', '0', '1'}},
            {{'1', '1', '0', '0'}}, {{'1', '0', '0', '0'}},
            {{'0', '1', '1', '1'}}, {{'0', '0', '1', '1'}},
            {{'0', '1', '1', '0'}}, {{'0', '0', '1', '0'}},
            {{'0', '1', '0', '1'}}, {{'0', '0', '0', '1'}},
            {{'0', '1', '0', '0'}}, {{'0', '0', '0', '0'}},
        }; 
        int key = hash(str);

        if (key <= 26 && key >= 0)
            return std::equal(str.begin(), str.end(), vocab[key].begin());
        else
            return false;
    }
};

#include <iostream>

int main()
{
    std::array<char, 4> nibble;
    while (std::cin.read(nibble.data(), nibble.size()))
        std::cout << Perfect_Hash::hexchar(nibble);
}
