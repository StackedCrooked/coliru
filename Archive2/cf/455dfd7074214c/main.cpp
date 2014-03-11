#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
struct employee {
    string name; double salary;
    void print() const {
        cout << name << ": " << salary << endl;
    }
};

template <typename Range, typename Comp>
void sort_reverse(Range& rng, Comp comp) {
  std::sort(begin(rng), end(rng),
    [comp](auto const& a, auto const& b){
      return comp(b, a);
    });
}

int main() {
    vector<employee> emps = {{{"Berta"}, 72000}, {{"Claus"}, 42000}, {{"Anton"}, 100000}};
    auto comp_salary = [](auto const& e1, auto const& e2) {
                         return e1.salary < e2.salary;
                       };
    
    sort_reverse(emps, comp_salary);
    cout << "employees: " << endl;
    for (auto const& e : emps) e.print();
}