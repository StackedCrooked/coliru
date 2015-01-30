namespace N
{
    struct B
    {
        template<class V> friend int g(struct C*); // #3
    };

    C* c;
}

int main() {}