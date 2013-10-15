#include <set>

template<typename T>
class Problem
{
    public:
        void f();

        std::set<int> dummyvalue;
};

template<typename T>
void Problem<T>::f()
{
    auto mytestlambda = [this](){
        dummyvalue.clear();
    };
}

int main()
{
    return 0;
}