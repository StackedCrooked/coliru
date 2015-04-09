#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

int main() {
    using std::begin;
    using std::end;
    
    std::string s("Some! string!s.");
    std::copy_if(
        begin(s), end(s), std::ostream_iterator<char>(std::cout),
        [](unsigned char c) {return !std::ispunct(c);}
    );
}