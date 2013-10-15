#include <memory>

int main()
{
    std::shared_ptr<int> p;
    auto x = [p] () mutable {p.reset();};
    x();
    auto y = [p]{p.reset();}
    y();
}
