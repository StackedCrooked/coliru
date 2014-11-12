#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdexcept>

int main() {
    
    std::vector<double> extract;
    
    std::string sentence = " Asdf 1 1.3825 4.0000 12.0000 1.9133 0.1853 0.9000 1.1359 4.0000 ";
    std::istringstream iss(sentence);
    std::for_each(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             [&](const std::string &str) {
                 double v;
                 try {
                    v = stod(str);
                 }
                 catch(std::invalid_argument &ia) { return; }
                 catch(std::out_of_range &oor) { return; }
                 extract.push_back(v);
             });
    
    std::copy(extract.begin(), extract.end(), std::ostream_iterator<double>(std::cout, "\n"));
}