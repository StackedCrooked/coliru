class Var
{
public:
    
    operator int () const
    { return 0; }
    
    template <typename T>
    operator T () const
    { return T(); }

};

int main()
{
    Var v;
    switch (v)
    { }
}