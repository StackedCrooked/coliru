#include <iostream>
#include <string>
#include <vector>


template<typename D>
class space_ship
{
public:
    void move()
    {
        if(!static_cast<D*>(this)->fuel())
            return;
        int current_speed = static_cast<D*>(this)->speed();
        (void)current_speed;
    }
};


class interceptor : public space_ship<interceptor>
{
public:
    bool fuel() const {return fuel_;}
    int speed() const {return speed_;}
private:
    int fuel_;
    int speed_;
};

typedef const char (*array_pointer_t)[2] ;
array_pointer_t foo()
{
    static const char table[][2] =
        {
            {2,3},
            {4,5}
        };
    return table;    
}

int main()
{
    
    interceptor i;
    i.move();
}
