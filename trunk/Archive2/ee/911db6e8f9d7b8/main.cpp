#include <iostream>
#include <utility>
#include <tuple>
#include <string>
#include <memory>
#include <map>
#include <functional>

using namespace std;

struct Parameter
{
    double& operator()()
    {
        return d;
    }
    
    double d;
};

struct Setup
{
    double field;

    map<string, function<double&()>> m;
    
    Setup()
    {
        m["field"] = [this]()->double&{ return field; };
        m["none"] = [val=0.0]() mutable -> double& {
            return val;
        };
    }
};
    

int main()
{
    Setup s1;
    Setup s2;
    
    cout << s1.m["none"]() << endl;
    s1.m["none"]() = 20;
    cout << s1.m["none"]() << endl;
    
    Setup s3 = s1;
    cout << s3.m["none"]() << endl;
}
