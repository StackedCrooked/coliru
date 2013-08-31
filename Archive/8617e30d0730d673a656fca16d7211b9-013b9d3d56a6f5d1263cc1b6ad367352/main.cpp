class A;

class B
{
    A* const member2;
public:
    B(A* const myA) : member2(myA)
    { }

    ~B()
    { }
};

class A
{
    B member1;

public:
    A() : member1(this)
    { }

    ~A()
    { }
};

int main()
{
    A* objectToDelete = new A();
    delete objectToDelete;
}
