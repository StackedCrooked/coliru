struct X {
    X* operator++() { return this; };
};

int main()
{
    X* x = new X;
    delete ++(*x);
}
