#include <iostream>
#include <string>
#include <vector>

struct O{
    O(int i) : i(i){};
    int i;
};


class A{
    mutable std::vector<O> data;
public:
    const O& get(int id) const{
        return data[id];
    }
    
    void push(O &&value){
        data.emplace_back(value);
    }
};

int main()
{
    A a;
    a.push(O(0));
    a.get(0);
}
