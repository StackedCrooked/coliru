#include <iostream>
#include <memory>

struct Point
{
    ~Point() { std::cout << "Destroy the Point." << std::endl; }
    int x = 0, y = 0;
};

int main()
{
    auto p = std::make_shared<Point>();
    std::shared_ptr<int> px(p, &p->x);
    
    std::cout << "Reset p" << std::endl;
    p.reset();
    
    std::cout << "Reset px" << std::endl;
    px.reset();
}