struct Car
{
};

int GenerateId()
{
    static int id = 0;
    return id++;
}

template <class A, class B, class C, class D>
void eatWarnings(A, B, C, D)
{
}

int main(int, char**)
{
    auto name = "Jane";       // const char*
    auto age  = 32U;          // unsigned int
    auto car  = new Car();    // Car*
    auto id   = GenerateId(); // int
    eatWarnings(name, age, car, id);
    return 0;
}