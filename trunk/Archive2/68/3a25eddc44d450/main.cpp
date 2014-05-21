#include <iostream>
 
bool operator"" _print ( const char* str )
{
    return (str[0] != '0');
}


enum class bit {low, high, undefined, high_impedance};

bit char_to_bit(char c) {
    switch (c) {
        case '0' : return bit::low;
        case '1' : return bit::high;
        case 'x' : return bit::undefined;
        case 'z' : return bit::high_impedance;
    }
    
    return bit::undefined;
}

char bit_to_char(bit b) {
    switch (b) {
        case bit::low: return '0';
        case bit::high: return '1';
        case bit::undefined: return 'x';
        case bit::high_impedance: return 'z';
    }
    
    return 'x';
}

bit operator "" _b(const char *str) {
     return char_to_bit(*str);
}
 
int main(){
    std::cout << 0x123ABC_print << std::endl;
    
    std::cout << bit_to_char("0"_b) << std::endl;
    std::cout << bit_to_char("1"_b) << std::endl;
    std::cout << bit_to_char("x"_b) << std::endl;
    std::cout << bit_to_char("z"_b) << std::endl;
}