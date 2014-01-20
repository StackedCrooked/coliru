#include <iostream>
#include <memory>

using namespace std;

struct moveonly
{
    moveonly() = default;
    moveonly(const moveonly&) = delete;
    moveonly(moveonly&&)
    {
        cout << "move-constructed" << endl;
    }
};

int main()
{
    unique_ptr<int> ptr{new int{10}};
    moveonly m{};
    [m = move(m), ptr = move(ptr), x=10]{
      cout << *ptr + x << endl;  
    }();
    
    cout << static_cast<bool>(ptr) << endl;
    
    return 0;
}