#include <memory>
#include <list>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

std::ostream &operator<<(std::ostream &os, std::string* p) { return os << *p; }


int main(){
    
    std::string str("Hello World\n");
    std::vector<std::string*> vec;
    vec.push_back(&str);
    
    for (std::size_t i = 0; i < vec.size(); i++){
        std::cout << vec[i];
    }
    
    std::transform(begin(vec), end(vec), std::ostream_iterator<std::string>(std::cout), [](const std::string* foo){return *foo;});
        
        
}