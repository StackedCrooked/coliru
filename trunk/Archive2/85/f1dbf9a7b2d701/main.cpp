struct X
{
    int* begin() { return v; }
    int* end() { return v + 5; }
    int v[5] = { 1, 2, 3, 4, 5 };
};

int main()
{
    for (auto c : X{}) { throw 42; };
}