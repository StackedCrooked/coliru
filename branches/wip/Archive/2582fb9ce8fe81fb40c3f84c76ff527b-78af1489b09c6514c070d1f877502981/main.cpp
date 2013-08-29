struct Class2 {};

class MyClass
{
    public:
    Class2 array [100];
    MyClass (const MyClass& other) : array (other.array) {}
};

int main()
{
}
