#include <memory>
#include <functional>


int main()
{
    std::unique_ptr<int> p;
 
    std::function<void()> f = std::bind([](std::unique_ptr<int>& p) {}, std::move(p));
}
