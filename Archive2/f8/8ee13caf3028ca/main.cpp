#include <iostream>
#include <vector>

struct Info
{
    int StudentId;
    std::string Grade; // this could easily be stored as an int or a char as well
};

int main()
{
    const std::vector<Info>::size_type SIZE_LIMIT = 5;
    
    std::vector<Info> vec;
    while(vec.size() < SIZE_LIMIT)
    {
        int StudentId;
        std::string Grade;
        
        std::cout << "Enter a Student ID:  ";
        std::cin >> StudentId;
        std::cout << "Enter a Grade:  ";
        std::cin >> Grade;
        
        if(std::cin)
        {
            vec.push_back({StudentId, Grade});
        }else
        {
            std::cout << "invalid! please try again\n\n";
        }
    }

    std::cout << "\n\nStored data:\n";
    for(auto const& i : vec)
    {
        std::cout << "Student ID:  " << i.StudentId << ", Grade:  " << i.Grade << std::endl;
    }

    return 0;
}