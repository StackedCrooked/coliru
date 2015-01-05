#include <iostream>

using namespace std;


auto add = [](auto a, auto b) {
    return a+b;
};


auto c = [] (auto f, auto a) {
    return [=](auto b) {
        return f(a, b);
    };
};


int main()
{
    auto s = add(1, 2);

    auto ca3 = c(add, 3);
    auto r34 = ca3(4);

    cout << "s:   " << s   << endl;
    cout << "r34: " << r34 << endl;
    
	return 0;
};
