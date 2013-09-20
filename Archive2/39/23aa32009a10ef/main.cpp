#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <string>

class Rob {public:std::string name = "Rob";};
class Silas {public:std::string name = "Silas";};
class Leon {public:std::string name = "Leon";};
class Toon {public:std::string name = "Toon";};
class Floris {public:std::string name = "Floris";};
class Frank {public:std::string name = "Frank";};

#define OBJ_CALL(A) {std::cout << (A)->name << " is "; for (unsigned int i = 0; i < (A)->name.size(); i++) {calcRetard((int)((A)->name.at(i))); if ((A)->name == "Frank") {listOfNumbers.push_back(100);} } average();}

int main() {
    std::cout << "Retard calculator!" << std::endl;
    
    auto pRob = std::make_shared<Rob>();
    auto pSilas = std::make_shared<Silas>();
    auto pLeon = std::make_shared<Leon>();
    auto pToon = std::make_shared<Toon>();
    auto pFloris = std::make_shared<Floris>();
    auto pFrank = std::make_shared<Frank>();
    
    std::vector<int> listOfNumbers;
    
    std::function<void(int)> calcRetard = [&](int i){((i % 10 == 1) ? (listOfNumbers.push_back(10)) : (listOfNumbers.push_back(5)));};
    std::function<void(void)> average = [&](){int q = 0; for(auto& i : listOfNumbers) {q += i;} std::cout << (double)(q / listOfNumbers.size()) << "% retarded \n"; listOfNumbers.clear();};
    
    OBJ_CALL(pRob)
    OBJ_CALL(pSilas)
    OBJ_CALL(pLeon)
    OBJ_CALL(pToon)
    OBJ_CALL(pFloris)
    OBJ_CALL(pFrank)

    return 0;
}
