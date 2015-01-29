#include <iostream>

class Mine 
{
public:
    Mine(int state):
        _state(state)
    {
    }
    
    int getState()
    {
        return _state;
    }
    
private:
    int _state;
};

template<typename TObject, typename TRes>
auto invoke(TObject& object, TRes (TObject::*getter)()) -> TRes
{
    return (object.*getter)();
}

int main()
{
    Mine mine(10);
    std::cout << "State of mine is: " << invoke(mine, &Mine::getState) << std::endl; //(mine.*stateGetter)() << std::endl;
}