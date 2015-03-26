
#include <iostream>

struct SomeInfo {
    int someDetail;
    
    int mapSize;
    int *map;
};

SomeInfo DoThing(unsigned int resolution, SomeInfo result) {
    for(unsigned int i = 0; i < resolution; i++) {
        result.map[i] = i;
    }
    
    result.someDetail = 200;

	return result;
}

int main()
{
    SomeInfo myInfo = {};
    myInfo.mapSize = 5;
    int myMap[5];
    myInfo.map = myMap;
    SomeInfo myResult = DoThing(5, myInfo);
   
    std::cout << myResult.someDetail << std::endl;
    std::cout << myResult.mapSize << std::endl;
    std::cout << myResult.map[3] << std::endl;
   
    return 0;
}