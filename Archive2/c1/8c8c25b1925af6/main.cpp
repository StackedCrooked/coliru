#include <iostream>
#include <functional>

class Sensor{
public:
    std::function<void()> begin;
    std::function<void()> end;
};

int main()
{
   
   Sensor* sensor = new Sensor;
   sensor->begin = [](){printf("Started \n");};
   sensor->end = [](){printf("Ended \n");};
   
   sensor->begin();
   sensor->end();
   
   
   delete sensor;
   return 0;
}