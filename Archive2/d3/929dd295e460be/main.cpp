

template<typename T>
struct TT : private T
{
};


struct X
{
    int n = 0;
};


struct XX : TT<X>
{
    int size() const
    {
        return sizeof(X);
    }
};



