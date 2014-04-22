#include <iostream>
#include <boost/optional.hpp>

auto enumFromTo = [](int start, int end){
    return [=]() mutable -> boost::optional<int>{
        if (start <= end)
            return start++;
        return boost::none;
    };
};

int main(){
  auto xs = enumFromTo(1, 10);
  while(auto x = xs())
    std::cout << x << ' ';
}