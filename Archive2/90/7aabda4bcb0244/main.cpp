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

void sort(std::vector<std::string> &names, std::vector<float> &grades) { // selection sort
    for (int i = (grades.size() > names.size() ? grades.size() : names.size()) - 1; i > 0; i--) {
        int first = 0;
        
        for (int j = 1; j <= i; j++) {
            if (grades.at(j) < grades.at(first)) {
                first = j;
            }
        }
        
        float tempgrade = grades.at(first);
        grades.at(first) = grades.at(i);
        grades.at(i) = tempgrade;
        
        std::string tempname = names.at(first);
        names.at(first) = names.at(i);
        names.at(i) = tempname;
    }
}

int main(void) {
    std::vector<std::string> names({ "johnny", "casio", "donald" });
    std::vector<float> grades({ 25.0, 100.0 , 7.0 });
    
    sort(names, grades);
    std::cout << names << '\n' << grades;
}
