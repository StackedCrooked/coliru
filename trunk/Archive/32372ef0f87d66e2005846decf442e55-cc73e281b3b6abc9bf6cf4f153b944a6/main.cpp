#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

struct employee_type {
    std::string name;
    std::unordered_set<employee_type*> referred;
};

typedef std::unordered_set<std::string> referred_set_type;
void get_refers(const employee_type& employee, referred_set_type& referred)
{
    for(employee_type* recip : employee.referred) {
        if (referred.find(recip->name) == referred.end()) {
            referred.insert(recip->name);
            get_refers(*recip, referred);
        }
    }
}

int main() {
    std::unordered_map<std::string, employee_type> employees = {
            {"A",{"A",{}}}, //cant initialize referred yet until the employees are in place
            {"B",{"B",{}}},
            {"C",{"C",{}}},
            {"D",{"D",{}}},
            {"E",{"E",{}}},
            {"F",{"F",{}}},
            {"G",{"G",{}}},
        };
    employees["A"].referred.insert(&employees["B"]);
    employees["B"].referred.insert(&employees["C"]);
    employees["B"].referred.insert(&employees["D"]);
    employees["D"].referred.insert(&employees["E"]);
    employees["F"].referred.insert(&employees["G"]);
    
    
    for(const auto& employee_rec : employees) {
        referred_set_type referred;
        get_refers(employee_rec.second, referred);
        std::cout << employee_rec.first << ' ' << referred.size() << '\n';
    }
}
    