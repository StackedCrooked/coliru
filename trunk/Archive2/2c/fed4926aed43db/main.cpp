class A
{
public:
    typedef void (A::*FunctionP) (int);
};

class B : A 
{
public:
    void Test(int )
    {
        //Do stuff
    }
    B()
    {
        FunctionP theFunc = static_cast<FunctionP>(&B::Test);
    }

};

int main() {
}
