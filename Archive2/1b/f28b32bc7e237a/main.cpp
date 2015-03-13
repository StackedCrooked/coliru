struct Bar {};

void Foo(const Bar b) {}

int main()
{
    Foo(Bar());
}