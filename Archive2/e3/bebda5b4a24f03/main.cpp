
struct A
{
    A() = default;

    A(const A&) = default;
    A& operator =(const A&) = default;

    A(A&&) = delete;
    A& operator =(A&&) = delete;
};

int main()
{
    A a;
    A a2;
    
    a2 = a;
    
    //a = A(); // error C2280
}