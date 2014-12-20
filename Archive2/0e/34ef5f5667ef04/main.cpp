#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <array>

struct Component{};

int main()
{
    using namespace std;
    
    vector<pair<int, array<unique_ptr<Component>, 32>>> components;
    
    int count = 0;
    pair<int, array<unique_ptr<Component>, 32>> component_set;
    
    component_set.first = ++count;
    components.emplace_back(move(component_set));
}