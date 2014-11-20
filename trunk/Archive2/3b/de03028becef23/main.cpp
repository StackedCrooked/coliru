#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Sorting {
public:
    std::vector<std::function<void(int*,int)>> functions;
    
private:
    void bubbleSort(int* a, int n){
        std::cout << "In bubble sort" << std::endl;
    }
    
public:
    Sorting(){
        std::function<void(int*, int)> myMemberFunction = [this](int* a, int n) {
            this->bubbleSort(a,n);
        };
        functions.push_back(myMemberFunction);
    }
};

int main()
{
    Sorting s;
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int b = 10;
    s.functions[0](a,b);
}