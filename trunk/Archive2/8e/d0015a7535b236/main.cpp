#include <iterator>
#include <functional>
#include <algorithm>
#include <iostream>

template<class comparitor>
struct deref_comparitor {
    deref_comparitor(comparitor comp={}): comp(comp) {}
    template<class pointer>
    bool operator()(pointer left, pointer right) {return comp(*left, *right);}
private:
    comparitor comp;
};


int main() {
    std::vector<int> AList = {4, 7, 1, 3, 9};
    std::vector<int> BList = {1, 2, 6, 9, 0, 3, 5, 7, 2, 8};

    std::vector<int*> combined;
    for(int& i : AList)
        combined.push_back(&i);
    for(int& i : BList)
        combined.push_back(&i);
    std::sort(combined.begin(), combined.end(), deref_comparitor<std::less<int>>());
    
    for(int* p : combined) 
        std::cout << *p << ',';
}