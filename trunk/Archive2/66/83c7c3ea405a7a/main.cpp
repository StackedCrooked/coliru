
#include <iostream>

#include <vector>


struct SomeInfo {
    int someDetail;
    
    std::vector<int> map;
};

SomeInfo DoThing(unsigned int resolution) {
    SomeInfo result = {};
    
    for(unsigned int i = 0; i < resolution; i++) {
        result.map.insert(result.map.begin()+i, (int)i);
    }
    
    result.someDetail = 200;

	return result;
}

int main()
{
    SomeInfo myResult = DoThing(5);
   
    std::cout << myResult.someDetail << std::endl;
    std::cout << myResult.map.size() << std::endl;
    std::cout << myResult.map[3] << std::endl;
   
    return 0;
}

