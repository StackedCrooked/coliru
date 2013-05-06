#include <iostream>
#include <string>
#include <vector>
#include<utility>
#include <type_traits>

class Factory
{

private:
    Factory();
    static Factory* self_inst;

public:
    ~Factory();

    //IPortIO* getStrategy(int portType);
    static Factory *getInstance()
    {           
        if(self_inst == NULL)
            self_inst = new Factory();
        return self_inst;       
    }

};

Factory::Factory()
{
}
//Initialize member
Factory* Factory::self_inst = NULL;

int main()
{
    Factory* f = Factory::getInstance();
    return 0;
}
