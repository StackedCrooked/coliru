#include <iostream>
#include <vector>

class A{};
class B{};
class Group
{
public:
    Group(): index_{0,2,1}
    {
    }

    template<typename Functor>
    void each(Functor f)
    {
        for (int n : index_)
            f(n);
    }
private:
    std::vector<int> index_;
};

//
template <typename cClass>
class BaseTest{
public:
    BaseTest():data_{100,200,300}
    {
    }
    template<typename Functor>
    void foo(Functor& f, int id)
    {
        f(data_[id]);
    }

    std::vector<int> data_;
};

/*
class Test : private BaseTest
*/
class Test : private BaseTest<A>,
             private BaseTest<B>
{
public:
    template<typename Functor>
    void test(Functor f){
        group->each([&](int n)
        {
            //foo(f,n);
            BaseTest<A>::foo(f,n);
        });
    }
    Group* group;
};

int main()
{
    Test t;
    Group g;
    t.group = &g;
    t.test([](int n){std::cout<<n;});
}