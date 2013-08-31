#include <cmath>
#include <string>

std::string itos1(int i)
{
    if (i == 0) { return "0"; }
    if (i < 0) { return "-" + itos1(-i); }
    // Number of characters needed
    int size = int(log10(i)) + 1;
    std::string l; // start with empty string
    l.reserve(size); // reserve space for all digits (no need to track null terminators by hand)
    for (int j = 0; j < size; j++)
        l.push_back((char) ( (int(i / pow(10, (size - j - 1))) % 10) + '0'));
    return l;
}

#include <sstream>

std::string itos2(int i)
{
    std::ostringstream ss;
    ss << i;
    return ss.str();
}

#include <iostream>

int main() {
    std::cout << itos1(423) << '\n';
    std::cout << itos2(423) << '\n';
}