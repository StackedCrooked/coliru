#include <cmath>
#include <iostream>   
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>

struct CatIdentifier{
    std::string id;
    size_t start;
};

int main()
{
    std::vector<CatIdentifier> vec;
    auto id = CatIdentifier{"ciao", 5u};
    
    if(std::end(vec) == std::find(std::begin(vec), std::end(vec), id)){
        std::cout << "not there" << std::endl;
    }
    else{
        std::cout << "there" << std::endl;
    }
    
    return 0;
}


