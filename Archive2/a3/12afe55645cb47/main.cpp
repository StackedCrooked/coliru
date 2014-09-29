struct X
{
    X(): val(1) {}
    int val;
};

struct Y
{
    Y() = default;
    int val = 1;
};

int main()
{
    X const x;  // OK, user-provided default constructor
    Y const y;  // ERROR, default constructor only user-declared
}
