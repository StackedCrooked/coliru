#include <functional>

template<typename ...Args>
void caller(std::function<void(Args&&...)> function)
{

}

int main()
{
    caller([&] () { });
}
