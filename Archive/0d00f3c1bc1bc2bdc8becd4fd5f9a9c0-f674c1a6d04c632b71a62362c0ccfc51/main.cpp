#include <iostream>
#include <memory>


struct WithLifetimeChecker
{
    explicit WithLifetimeChecker():
        ref_counter_(this, [](WithLifetimeChecker*){})
    {
    }

    WithLifetimeChecker(const WithLifetimeChecker&) :
        ref_counter_(this, [](WithLifetimeChecker*){})
    {
    }

    WithLifetimeChecker& operator=(const WithLifetimeChecker& rhs)
    {
        return *this;
    }

    std::weak_ptr<void> getLifetimeChecker() const
    {
        return ref_counter_;
    }
    
private:
    std::shared_ptr<void> ref_counter_;
};


int main()
{
    
    std::weak_ptr<void> checker;
    {
        WithLifetimeChecker lt;
        checker = lt.getLifetimeChecker();
        std::cout << "checker.expired: " << checker.expired() << std::endl;
    }
    std::cout << "checker.expired: " << checker.expired() << std::endl;
}