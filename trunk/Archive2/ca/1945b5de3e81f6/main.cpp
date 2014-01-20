struct T
{
    friend void foo(const T& t);
};

int main()
{
    T t;
    foo(t);
}

void foo(const T&) {}