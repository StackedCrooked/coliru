struct X {
    X* operator++() const { return nullptr; };
};

int main()
{
    X x;
    delete ++x;
}
