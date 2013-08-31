struct base
{
    virtual base* foo();
};

struct derrive : virtual base
{
    virtual derrive* foo();
};


int main()
{
    base* der = new derrive;
    dynamic_cast<derrive*>(der->foo());
}