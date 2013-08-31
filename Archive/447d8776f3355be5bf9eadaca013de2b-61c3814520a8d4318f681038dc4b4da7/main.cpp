struct base
{
     virtual base* foo() {}
};

struct derrive : base
{
     virtual derrive* foo() {}
};


int main()
{
     base* der = new derrive;

     auto x = static_cast<derrive*>(der->foo());//Compiler thinks i return base here.
}