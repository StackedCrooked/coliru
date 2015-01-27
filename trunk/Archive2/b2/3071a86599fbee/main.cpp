struct A
{
    operator auto(){}
};

int main()
{
    A().operator auto();
}