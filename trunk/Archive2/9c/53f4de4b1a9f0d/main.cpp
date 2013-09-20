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
    
    std::cout << "Rob is ";
    for (unsigned int i = 0; i < pRob->name.size(); i++)
        calcRetard((int)(pRob->name.at(i)));
    average();
    
    std::cout << "Silas is ";
    for (unsigned int i = 0; i < pSilas->name.size(); i++)
        calcRetard((int)(pSilas->name.at(i)));
    average();
    
    std::cout << "Leon is ";
    for (unsigned int i = 0; i < pLeon->name.size(); i++)
        calcRetard((int)(pLeon->name.at(i)));
    average();
    
    std::cout << "Toon is ";
    for (unsigned int i = 0; i < pToon->name.size(); i++)
        calcRetard((int)(pToon->name.at(i)));
    average();
    
    std::cout << "Floris is ";
    for (unsigned int i = 0; i < pFloris->name.size(); i++)
        calcRetard((int)(pFloris->name.at(i)));
    average();
    
    std::cout << "Frank is ";
    for (unsigned int i = 0; i < pFrank->name.size(); i++)
        calcRetard((int)(pFrank->name.at(i)));
    average();
    
    
    
    return 0;
}
