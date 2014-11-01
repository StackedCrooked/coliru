struct A
{
    A(){ };
    A(const A&&){ };
    ~A(){ };
};

A a;

A t = a;

int main()
{ 
    
}

