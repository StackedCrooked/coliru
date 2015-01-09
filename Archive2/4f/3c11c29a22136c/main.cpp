#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct exampleStruct
{
    exampleStruct(int x, double y): mX(x), mY(y) {};

    int mX;
    double mY;
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::vector<int> scores;
    
    //Update with individual scores;
    std::cout << "Old fashion vector:" << std::endl;
    scores.push_back(11);
    scores.push_back(17);
    scores.push_back(19);
    scores.push_back(20);
    
    std::cout << scores << std::endl;
    
    //Initializer list:
    // type name = { value1, value2, ..., valueN} OR
    // type name{ value1, value2, ..., valueN}
    std::cout << "vectors:" << std::endl;
    std::vector<double> fineScores = {11.2, 17.04, 18.996, 20.16};
    std::vector<double> fineScoresAlt{11.3, 17.14, 18.896, 20.26};  //alternate, even more compact form
    std::cout << fineScores << std::endl;
    std::cout << fineScoresAlt << std::endl;
    
    //You can initilize structs as well.
    std::cout << "Struct/object:" << std::endl;
    exampleStruct myStruct = {77, 91.5};
    std::cout << myStruct.mX << " " << myStruct.mY << std::endl;
    
    //And array of objects
    std::cout << "Struct/object array:" << std::endl;
    exampleStruct myStructArray[]{ {11, 23.5}, {26, 44.6} };
    std::cout << myStructArray[0].mX << " " << myStructArray[0].mY << std::endl;
    std::cout << myStructArray[1].mX << " " << myStructArray[1].mY << std::endl;
}
