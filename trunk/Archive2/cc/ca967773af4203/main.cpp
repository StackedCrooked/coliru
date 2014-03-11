#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;
struct employee {
    string name; double salary;
    void print() const {
        cout << name << ": " << salary << endl;
    }
};

int main() {
    vector<employee> emps = {{{"Anton"}, 100000}, {{"Berta"}, 72000}, {{"Claus"}, 42000}};
    auto comp_salary = [](auto const& e1, auto const& e2) {
                         return e1.salary < e2.salary;
                       };
    
    sort(begin(emps), end(emps), comp_salary);
    cout << "employees: " << endl;
    for (auto const& e : emps) e.print();

    map<employee, float, decltype(comp_salary)> happiness {
        {{emps[0], 1.0f}, {emps[1], 0.2f}, {emps[2], 0.9f}}, comp_salary
    };
    vector<employee> happy_emps;
    
    copy_if(begin(emps), end(emps), back_inserter(happy_emps),
            [&happiness](auto const& e){ return happiness[e] > 0.5f; });
    cout << "happy employees: " << endl;
    for (auto const& e : happy_emps) e.print();
}