#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

int main() {
    {
        std::stringstream sstr;
        sstr << "0123456789";
        std::istreambuf_iterator<char> i(sstr);
        
        std::copy_n(i, 10, std::ostreambuf_iterator<char>(std::cout));
    }
    std::cout << "\n";
    {
        std::stringstream sstr;
        sstr << "0123456789";
        std::istreambuf_iterator<char> i(sstr);
        
        std::vector<char> dat(10);
        std::copy_n(i, 10, dat.begin());
        i++;
                
        std::copy_n(dat.begin(), 10, std::ostreambuf_iterator<char>(std::cout));
    }
    return 0;
}