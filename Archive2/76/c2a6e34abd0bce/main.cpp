

template<typename T>
struct TT : private T
{
};


struct X
{
};


struct XX : TT<X>
{
    int size() const
    {
        return sizeof(X);
    }
};



