struct Car
{
};

int GetId()
{
    return 1;
}

template <class A, class B, class C, class D>
void eatWarnings(A, B, C, D)
{
}

int main(int, char**)
{
    auto name = "Jane";    // const char*
    auto age  = 32U;       // unsigned int
    auto car  = new Car(); // Car*
    auto id   = GetId();   // int
    eatWarnings(name, age, car, id);
    return 0;
}
