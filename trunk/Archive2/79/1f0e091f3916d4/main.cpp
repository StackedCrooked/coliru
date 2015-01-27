struct A
{
    operator auto(){ return 1l; }
};

int main()
{
    A().operator auto();
}