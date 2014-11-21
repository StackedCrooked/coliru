#include <iostream>
#include <string>

class Ship
{

public: 
        static int id;
        Ship(std::string name="Ship")
        {
          ++id;
        }
};
