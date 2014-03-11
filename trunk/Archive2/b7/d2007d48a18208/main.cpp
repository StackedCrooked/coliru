#include <string>
#include <iostream>
#include <list>

struct test {
    std::string name;
    int value;
    const std::string& GetName() const {return name;}
    int GetValue() const {return value;}
};

struct test_comp {
    bool operator() (const test* a, const test* b) const {
        if(a->GetValue() == a->GetValue()) {
            return a->GetName() < b->GetName();
        } else {
            return a->GetValue() > a->GetValue();
        }

    }
};

int main() {
    std::list<test*> test_list = {new test{"A",1}, new test{"B",4}, new test{"C",1}, new test{"A",3}, new test{"B",3},  new test{"B",3},  new test{"C",3},  new test{"A",4},  new test{"B",1},  new test{"C",4} };
    
    for(test* it : test_list)
        std::cout << it->GetName() << it->GetValue() << "  ";
    std::cout << '\n';
    
    test_list.sort(test_comp());
    
    for(test* it : test_list)
        std::cout << it->GetName()  << it->GetValue() << "  ";
    std::cout << '\n';
    
    return 0;
}