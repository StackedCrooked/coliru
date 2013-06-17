#include <memory>
#include <functional>

void MyFunction(std::unique_ptr<int> arg)
{

}

int main()
{
    std::function<void(std::unique_ptr<int>)> f = std::bind(&MyFunction, std::placeholders::_1);
    std::unique_ptr<int> p(new int(42));
    f(std::move(p));
    return 0;
}
