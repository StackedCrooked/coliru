#include <stdexcept>
#include <iostream>
#include <type_traits>

class Celsius;
class Fahrenheit;

template <typename Unit>
class Temperature
{
private:
    constexpr static double k_min = Unit::k_min;
    constexpr static double k_max = Unit::k_max;
    double temp;

public:

    explicit Temperature(double d)
      : temp(d)
    {
        if(d < k_min) {
            throw std::invalid_argument("Below min");
        }
        if(d > k_max) {
            throw std::invalid_argument("Above max");
        }        
    }

    template <typename Other, typename Converter>
    Temperature(Other other, Converter conv)
      : temp(conv((double)other))
    { }

    operator double() const 
    {
        return temp;
    }

    Temperature<Unit> operator+(Temperature<Unit> value) const
    {
        return Temperature<Unit>(temp + value.temp);
    }

    Temperature<Unit>& operator+=(Temperature<Unit> value)
    {
        temp += value.temp;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Temperature<Unit> t)
    {
        constexpr char type = std::is_same<Unit, Celsius>::value ? 'C' : 'F';
        return os << t.temp << type; 
    }
};

class Celsius : public Temperature<Celsius>
{
public:

    constexpr static double k_min = -273.15;
    constexpr static double k_max = 1.4e32;

    explicit Celsius(double d)
      : Temperature<Celsius>(d)
    { }

    Celsius(Fahrenheit f);
};

class Fahrenheit : public Temperature<Fahrenheit>
{
public:

    constexpr static double k_min = -459.67;
    constexpr static double k_max = 2.5e32;

    explicit Fahrenheit(double d)
      : Temperature<Fahrenheit>(d)
    { }

    Fahrenheit(Celsius c);
};

Celsius::Celsius(Fahrenheit f)
  : Temperature<Celsius>(f, [](double d) { return (d - 32.0) / 9 * 5; })
{ }

Fahrenheit::Fahrenheit(Celsius c)
  : Temperature<Fahrenheit>(c, [](double d) { return (d / 5.0) * 9.0 - 32.0; })
{ }

int main()
{
    Celsius c(50);
    Fahrenheit f(100);
    std::cout << c << "\n";
    std::cout << f << "\n";
    Celsius c2(f);
    std::cout << c2 << "\n";
}