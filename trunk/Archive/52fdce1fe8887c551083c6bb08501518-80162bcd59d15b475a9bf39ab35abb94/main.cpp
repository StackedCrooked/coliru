#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class TestClass{

public:
    TestClass(int s):
        size(s), arr(new int[s]){
    }
    ~TestClass(){
        if (arr)
            delete arr;
    }
    // copy constructor
    TestClass(const TestClass& other) :
            size(other.size), arr(new int[other.size]){
        std::copy(other.arr, other.arr + other.size, arr);
        assert(false);
    }

    // move constructor
    TestClass(TestClass&& other) noexcept {
        arr=other.arr;
        size=other.size;

        other.arr=nullptr;
        other.size=0;
    }

private:
    int size;
    int * arr;
};

int main(){
    vector<TestClass> vec;

    clock_t start=clock();
    for(int i=0;i<50000;i++){
        vec.push_back(TestClass(1000));
    }
    clock_t stop=clock();
    cout<<stop-start<<endl;

    return 0;
}