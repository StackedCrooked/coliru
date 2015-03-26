
#include <iostream>

struct SomeInfo {
    int someDetail;
    
    int mapSize;
    int *map;
};

template<unsigned int Resolution>
SomeInfo DoThing(int (&map)[Resolution]) {
    for(unsigned int i = 0; i < Resolution; i++) {
        map[i] = i;
    }
    
    SomeInfo result = {};
    result.someDetail = 200;
    result.mapSize = Resolution;
    result.map = map;

	return result;
}

int main()
{
    int myMap[5];
    SomeInfo myResult = DoThing<5>(myMap);
   
    std::cout << myResult.someDetail << std::endl;
    std::cout << myResult.mapSize << std::endl;
    std::cout << myResult.map[3] << std::endl;
   
    return 0;
}