#include <iostream>
#include <string>
#include <memory>

struct sensor
{
    virtual ~sensor() = default; // virtual dtor, prohibits destruction slicing
    
    virtual void sense(std::string const &thing) = 0; // pure virtual, must be implemented by child
};

struct foo_sensor : public sensor
{
    void sense(std::string const &thing) override // override parent's function
    { std::cout << "foo_sensing " << thing << std::endl; }
};

struct sensor_holder
{
    std::unique_ptr<sensor> ptr; // avoid raw pointers; unique_ptr will delete when it dies
};

int main()
{
    sensor_holder sh;
    sh.ptr.reset(new foo_sensor);
    sh.ptr->sense("bar");
}