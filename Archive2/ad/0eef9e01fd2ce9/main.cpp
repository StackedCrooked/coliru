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
    #if 0
    std::vector<CatIdentifier> vec;
    auto id = CatIdentifier{"ciao", 5u};
    
    if(std::end(vec) == std::find(std::begin(vec), std::end(vec), id)){
        std::cout << "not there" << std::endl;
    }
    else{
        std::cout << "there" << std::endl;
    }
    #else
    auto id1 = CatIdentifier{"ciao", 5u};
    auto id2 = CatIdentifier{"ciao", 5u};
    
    if(id1 == id2){
        std::cout << "not there" << std::endl;
    }
    else{
        std::cout << "there" << std::endl;
    }
    
    
    return 0;
}
