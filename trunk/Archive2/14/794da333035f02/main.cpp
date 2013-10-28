#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

struct Value
{
    int* value1_;
    int value2_;
};


int main()
{
    std::vector<Value> values;
    values.push_back(Value{new int(10), 20});
    
    using namespace std::placeholders;
    std::for_each(values.begin(), values.end(), std::bind(std::default_delete<int>(), std::bind(&Value::value1_, _1)));
}
