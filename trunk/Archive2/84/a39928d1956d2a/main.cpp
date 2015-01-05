#include <iostream>

using namespace std;

auto add = [](auto a, auto b) {
    return a+b;
};


auto addf = [](auto x) {
  return [=](auto y) { 
    return x+y; 
  };
};

auto c = [] (auto f, auto a, auto b) {
    return [=](auto b) {
        return f(a, b);
    };
};

int main()
{
    auto s = add(1, 2);

    auto ca3 = c(add, 3, 0);
    auto r34 = ca3(4);

    cout << "s:   " << s   << endl;
    cout << "r34: " << r34 << endl;

    auto a4  = addf(4);
    auto a45 = a4(5);
    
    cout << "a45: " << a45 << endl;
    
	return 0;
};
