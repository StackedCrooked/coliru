#include <iostream>
#include <map>
#include <string>

int main() {
    const size_t termCount = 2;
    const size_t gradeCount = 3;
    //you associate a name with a block of numbers (all grades of all terms)
    //if the counts vary for each student you can use vector, but you will get salad in memory
    std::map<std::string, std::array<std::array<int, gradeCount>, termCount>> students{
        {"John",{{ {{1,2,1}},{{2,2,3}} }} }//note that you need doubles braces to initialize an array
        //^name,   ^1. term ,^2. term
    };
    std::string student{"John"};
    for (size_t term = 0; term < termCount; ++term) {
        for (const auto & grade : students[student][term]) {
            std::cout << student << ", term " << term << ", grade " << grade << '\n';
        }
    }
}