#include <iostream>
#include <memory>


struct Machine
{
    virtual ~Machine() { }

    virtual void make_noise() = 0;

    template<typename T>
    void transform_to(T t)
    {
        static_assert(std::is_base_of<Machine, T>::value, "");
        auto this_ptr = this;
        this_ptr->~Machine();
        new (this_ptr) T(std::move(t));
    }
};


struct Robot : Machine
{
    void make_noise() override
    {
        std::cout << "I'M A ROBOT" << std::endl;
    }
};


struct Truck : Machine
{
    void make_noise() override
    {
        std::cout << "Vroom vroom!" << std::endl;
    }

};


int main()
{
    Machine* machine = new Truck();
    machine->make_noise();

    machine->transform_to(Robot());
    machine->make_noise();

    machine->transform_to(Truck());
    machine->make_noise();
}
