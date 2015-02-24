#include <iostream>
#include <algorithm>
#include <memory>




void question() {
 const int len = 10;
 
 std::unique_ptr<int[]> p(new int[len]);
 int x = 0;
 std::for_each(p.get(), std::next(p.get(), len), [&](int& a) { a = ++x; });
 std::for_each(p.get(), std::next(p.get(), len), [](int a) { std::cout << a << "\n" ;});
 
}

int main()
{
    question();
}
