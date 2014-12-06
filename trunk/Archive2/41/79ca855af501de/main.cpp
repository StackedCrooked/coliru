class Base
{
public:
   Base(void);
   virtual ~Base(void);
};

class Derived : public Base
{
public:
   Derived(void) {}
   virtual ~Derived(void);
};


int main(int argc, char **argv)
{
    Base * A;
    A = new Derived();
}