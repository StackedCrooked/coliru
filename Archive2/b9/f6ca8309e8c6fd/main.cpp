#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

struct Employee
{
    std::string Name;
    int jobGrade;
};

std::function<bool(const Employee&)> isEmployeeWithJobGrade5 = [](const Employee& a){return (5 == a.jobGrade);};
std::function<void(const Employee&, bool)> printNameIf = [](const Employee& a, bool cond){if (cond) {std::cout << a.Name << std::endl;}};

int main()
{       
    std::vector<Employee> employees = {Employee{"James", 5}, Employee{"John", 4}, Employee{"Alain", 5}};
    
    std::for_each(employees.begin(), employees.end(), [](const Employee& a){std::cout << a.Name << " " << a.jobGrade << std::endl;});
    
    std::for_each(employees.begin(), employees.end(), std::bind(printNameIf, std::placeholders::_1, std::bind(isEmployeeWithJobGrade5, std::placeholders::_1)));
}