#include <array>
#include <iostream>
#include <sstream>
#include <memory>
#include <thread>

class UserActionManager
{
public:
    static UserActionManager* GetUserActionManager();

    ~UserActionManager() { std::cout << "UAM destructor called.\n"; }
};

UserActionManager*
UserActionManager::
GetUserActionManager()
{
    thread_local std::unique_ptr<UserActionManager> theInstance;
    if (!theInstance)
    {
        theInstance = std::make_unique<UserActionManager>();
        std::stringstream ss;
        ss << "theInstance = " << theInstance.get() << "\n";
        std::cout << ss.str();
    }

    return theInstance.get();
}

int main() {
    const auto n_threads = 1u << 3;
    const auto n_iterations = 1u << 12;
    auto threads = std::array<std::thread, n_threads>{{}};
    auto spam = []{
        for (auto i = n_iterations; i-- > 0; ) {
            UserActionManager::GetUserActionManager();
        }
    };
    for (auto& t : threads) { t = std::thread{spam}; }
    spam();
    for (auto& t : threads) { t.join(); }
}
