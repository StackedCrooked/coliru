#include <iostream>
#include <string>
#include <vector>
#include <functional>

class ContainsObj
{
public:
    ContainsObj() { }
    ~ContainsObj() { }
    std::string lhs;
    std::string rhs;
    
    operator bool() const {
        return lhs.find(rhs) != std::string::npos;
    }
} containsobj;

ContainsObj& operator+(const std::string& lhs, ContainsObj& rhs) {
    rhs.lhs = lhs;
    return rhs;
}

ContainsObj& operator+(ContainsObj& lhs, const std::string& rhs) {
    lhs.rhs = rhs;
    return lhs;
} 

#define contains + containsobj +

class InObj {
public:
    InObj() { }
    ~InObj() { }
    int lhs;
    std::vector<int> rhs;
} inobj;

#define in + inobj +

InObj& operator+(const int& lhs, InObj& rhs) {
    rhs.lhs = lhs;
    return rhs;
}

InObj& operator+(InObj& lhs, const std::vector<int>& rhs) {
    lhs.rhs = rhs;
    return lhs;
} 

class PerformObj {
    int counter;
public:
    PerformObj() : counter(0) { }
    ~PerformObj() { }
    InObj lhs;
    std::function<int(int)> rhs;
    
    operator int() const {
        return rhs(lhs.rhs[counter]);
    }
} performobj;

#define perform + performobj +

PerformObj& operator+(const InObj& lhs, PerformObj& rhs) {
    rhs.lhs = lhs;
    return rhs;
}

PerformObj& operator+(PerformObj& lhs, const std::function<int(int)>& rhs) {
    lhs.rhs = rhs;
    return lhs;
} 

int main()
{
    std::vector<int> nums = {1,2,3};
    int x = 0;
    
    auto cube = [] (int n) {
        return n * n * n;
    };
    
    std::cout << x in nums perform cube << std::endl;
}
