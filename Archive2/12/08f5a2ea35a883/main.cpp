#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Car;


class Handling
{
    public:
        virtual void add_car() = 0;
        virtual void erase_car() = 0;
        virtual void show_car(vector<Car> _carvector) = 0;
};


class Car : virtual public Handling
{
    public:

        Car(){};

        void add_car()
        {

        }

        void erase_car()
        {

        }

        void show_car(vector<Car> cv)
        {
            for (vector<Car>::const_iterator i = cv.begin(); i != cv.end(); ++i)
            {
                std::cout << a << ", " << b << std::endl;
            }
        }

        string a;
        int b;
};

int main()
{
    vector<Car> carvector;
    Car c;
    c.a = "A";
    c.b = 42;
    carvector.push_back(c);
    c.show_car(carvector);
}
