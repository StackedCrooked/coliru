class Base
{};

class Derived: public Base
{
    public:
        // Try uncommenting this line
        //Derived(const Base&) {}
};

int main()
{
    Base b;
    Derived d1 = b;
    Derived d2 = static_cast<Derived>(b);
    Derived d3 = dynamic_cast<Derived>(b);
}
