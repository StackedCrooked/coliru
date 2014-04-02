#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
 
struct Employee {
    Employee(int age, std::string name) : age(age), name(name) { } 
    int age;
    std::string name;  // Does not particpate in comparisons
};
 
bool operator<(const Employee &lhs, const Employee &rhs) {
    return lhs.age < rhs.age;
}
 
int main()
{
    std::vector<Employee> v = { 
        Employee(108, "Zaphod"),
        Employee(32, "Arthur"),
        Employee(108, "Ford"),
    };  
 
    std::stable_sort(v.begin(), v.end());
 
    for (const Employee &e : v) {
        std::cout << e.age << ", " << e.name << '\n';
    }   
}