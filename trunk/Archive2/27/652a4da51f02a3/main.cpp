#include <iostream>
#include <list>

class Sensor{
public:
    std::function<void()> begin;
    std::function<void()> end;
};

int main()
{
   
   Sensor* sensor = new Sensor;
   sensor->begin = [](){std::cout << "Started \n";}
   sensor->end = [](){std::cout << "Ended \n";}
   
   sensor->begin();
   sensor->end();
   
   
   delete sensor;
   return 0;
}