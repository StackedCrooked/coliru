struct foo
{
    template<class T>
    int operator[](int p) { return p; }
};

int main()
{
    foo f;
    f.operator[] <double> (42);
}