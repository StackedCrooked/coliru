struct A
{
    A(){ };
    ~A(){ };
};

A a;

A t = a; //error: call to implicitly-deleted copy constructor of 'A'

int main()
{ 

}