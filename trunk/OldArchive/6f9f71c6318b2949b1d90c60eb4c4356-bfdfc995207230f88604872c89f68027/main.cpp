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
    std::cout << 
    
    std::cout << "\nbefore reset p. Use count p: " << p.use_count() << ", px: " << px.use_count() << std::endl;
    p.reset();
    std::cout << "after reset p. Use count p: " << p.use_count() << ", px: " << px.use_count() << std::endl;
    
    std::cout << "before reset px. Use count p: " << p.use_count() << ", px: " << px.use_count() << std::endl;
    px.reset();
    std::cout << "After reset px. Use count p: " << p.use_count() << ", px: " << px.use_count() << std::endl;
}