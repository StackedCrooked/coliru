struct X {
    int fancy = 42;
    X* operator++() { fancy+=42; return nullptr; };
};

int main()
{
    X x;
    delete ++x;
}
