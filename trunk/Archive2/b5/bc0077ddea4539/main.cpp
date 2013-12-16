template<class T>
class A
{
    operator T*() const
    {
        return p;
    }

    T* p;
};

template<class T>
class B : public A<T>
{
    using A::operator T*;
};

int main()
{}
