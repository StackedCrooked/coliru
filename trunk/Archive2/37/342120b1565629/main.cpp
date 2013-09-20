struct Car
{
};

int GenerateId()
{
    static int id = 0;
    return id++;
}

int main(int, char**)
{
    auto name = "Jane";       // const char*
    auto age  = 32U;          // unsigned int
    auto car  = new Car();    // Car*
    auto id   = GenerateId(); // int
    return 0;
}