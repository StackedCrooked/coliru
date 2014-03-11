struct X {
    X* operator++() { return const_cast<X* const>(this); };
};

int main()
{
    X* x = new X;
    delete ++x;
}
