#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Car
{
    public:
        explicit Car(std::string name) : mName(name) {}
        Car() : Car("") {}
        Car(Car&& other) noexcept { mName = other.mName; other.mName = ""; }
        Car& operator=(Car&& other) { mName = other.mName; other.mName = ""; return *this;}
        
        std::string mName;
};

class CarKey
{
    public:
        CarKey(Car* car) : mCar(car) {}
        CarKey() : CarKey(nullptr) {}
        CarKey(const CarKey& ) = delete;
        CarKey& operator=(const CarKey& ) = delete;
        CarKey(CarKey&& other) noexcept { mCar = other.mCar; other.mCar = nullptr; }
        CarKey& operator=(CarKey&& other ){ mCar = other.mCar; other.mCar = nullptr; return *this; }
    private:
        Car* mCar;
};

class Person
{
    public:
        Person(std::string name) : mName(name) {}
        Person() : Person("Anonymous") {}
        void getKey(CarKey&& carkey) {mCarKey = std::move(carkey);}
        CarKey& giveKey() { return mCarKey; }
    public:
        CarKey mCarKey;
        std::string mName;
};

int main()
{
    Person Joe("Joe");
    Person Mike("Mike");
    CarKey myVolvo(new Car("Volvo"));
}
