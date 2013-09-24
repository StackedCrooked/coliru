#include <iostream>
#include <future>

using namespace std;
int main()
{
    auto accum = async([]{});
    for (auto ch : "hello world")
        accum = async([](future<void>&& before, char ch) { before.get(); cout << ch; }, move(accum), ch);
    accum.get();
}
