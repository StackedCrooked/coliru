#include <memory>
#include <vector>
#include <iostream>

struct MyFakeAppender
{
    int id;

    ~MyFakeAppender() { std::cout << __FUNCTION__ << " id:" << id << "\n"; }
};

int main() {
    using namespace std;

    {
        vector<shared_ptr<MyFakeAppender>> v;
        v.emplace_back(new MyFakeAppender{ 1});
        v.emplace_back(new MyFakeAppender{ 2});
        v.emplace_back(new MyFakeAppender{ 3});
        v.emplace_back(new MyFakeAppender{ 4});
        v.emplace_back(new MyFakeAppender{ 5});
        v.emplace_back(new MyFakeAppender{ 6});
        v.emplace_back(new MyFakeAppender{ 7});
        v.emplace_back(new MyFakeAppender{ 8});
        v.emplace_back(new MyFakeAppender{ 9});
        v.emplace_back(new MyFakeAppender{10});
    }
};
