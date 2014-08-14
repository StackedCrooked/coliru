#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void pVector(const std::vector<int> &arg)
{
    std::for_each(arg.begin(), arg.end(), [](int n){std::cout << n << " ";});
    std::cout << std::endl;
}
void test1()
{
    std::vector<int> t{1,2,3,4};
    pVector(t);
    std::for_each(t.begin(), t.end(), [](int &n){ ++n; });
    pVector(t);
}

class Sum {
public:
    Sum(): total(0) {};
    void operator()(int n) {total += n;}
    
    int total;
};
void test2()
{
    std::vector<int> t={4,5,6,7,8,9,10};
    Sum cnt;
    cnt = std::for_each(t.begin(), t.end(), Sum());
    std::cout << cnt.total << std::endl;
}

void fun(int) {std::cout << "OK" << std::endl;}
typedef void (*f)(int);
void test3()
{
    std::vector<int> t{1,2,3};   
    f ff = std::for_each(t.begin(), t.end(), fun);
    (*ff)(0);
}

void test4()
{
    int array[2] = {1,2};
    f ff = std::for_each(array, array+2, fun);
    ff(0);
}
int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
