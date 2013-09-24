#include <vector>
#include <istream>
#include <iterator>

struct bigint
{
    std::vector<char> v; // or whatever representation you use (binary? bcd?)
};

std::istream& operator>>(std::istream& in, bigint& array)
{
    for (std::istream_iterator<char> f(in), l; f != l; ++f) {
        if (*f>='0' && *f<='9')
            array.v.push_back(*f - '0');
        else if (*f==';')
            break;
        else
            throw "invalid input";
    }

    return in;
}

#include <iostream>
#include <sstream>

int main()
{
    std::istringstream iss(
            "10000000000000000000000000000000000345;\n"
            "299793000000\n"
            "00000000000000000000067;\n"
            "4208574289572473098273498723475;\n"
            "28375039287459832728745982734509872340985729384750928734590827098752938723;\n"
            "99999999;  99999999;\n");

    bigint value;
    while (value.v.clear(), iss >> value)
        std::cout << "read " << value.v.size() << " digits\n";
}
