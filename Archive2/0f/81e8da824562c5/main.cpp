#include <iostream>
#include <memory>

class Work
{
};

class A 
{
public:

    void doWork(Work w)
    {
        std::cout << " - - ";
        return;
    }

    void doWork2(std::unique_ptr<Work> w)
    {
        std::cout << " - - ";
        return;
    }
};

int main()
{
    A a;
    std::unique_ptr<Work> w2 = std::unique_ptr<Work>(new Work());

    Work w;
    auto func = std::bind(&A::doWork, a, std::placeholders::_1);
    auto func2 = std::bind(&A::doWork2, a, std::placeholders::_1);
    func(w);
    func2(std::move(w2));
    return 0;
}
