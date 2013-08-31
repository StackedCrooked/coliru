#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

typedef std::unordered_set<std::string> referred_set_type;
typedef std::unordered_map<std::string, std::unordered_set<std::string>> employee_list_type;
typedef employee_list_type::value_type employee_type;

void get_refers(const employee_type& employee, const employee_list_type& list, referred_set_type& referred)
{
    for(const std::string& name : employee.second) {
        if (referred.find(name) == referred.end()) {
            referred.insert(name);
            get_refers(*list.find(name), list, referred);
        }
    }
}

int main() {
    employee_list_type employees = {
            {"A",{"B"}},
            {"B",{"C", "D"}},
            {"C",{}},
            {"D",{"E"}},
            {"E",{}},
            {"F",{"G"}},
            {"G",{}},
        };
    for(const employee_type& employee : employees) {
        referred_set_type referred;
        get_refers(employee, employees, referred);
        std::cout << employee.first << ' ' << referred.size() << '\n';
    }
}
    