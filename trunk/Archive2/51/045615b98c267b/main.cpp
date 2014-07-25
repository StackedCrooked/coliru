#include <iostream>
#include <memory>
#include <iostream>

void use_it(std::unique_ptr<int> i)
{
    std::cout << "Using " << *i << "\n";
}

int main()
{
    auto p = std::make_unique<int>(10);
    
    auto lambda = [p(std::move(p))]() mutable {
        use_it(std::move(p));
    };
    
    std::function<void ()> fn(lambda);
    fn();
    
    return 0;
}
