#include <iostream>
#include <vector>
using namespace std;

struct S {
    struct iterator {
        using const_iterator = int *;
    };
    
    iterator begin() {return {};}
    iterator end() {return {};}
};

// This function should take 2 iterators of a vector/list and sum the elements between them
template <typename T >
double Sum1(typename T::const_iterator start, typename T::const_iterator end){
    double sum = 0;
    // For g++, "typename is needed before T::const_iterator"
    for(typename T::const_iterator I = start; I <= end;I++){
        sum += *I;
    }
    return sum;
}

int main() {
    S b;// and it is pushed by numbers 1-9 later
    cout<<Sum1(b.begin(), b.end())<<endl;   
}