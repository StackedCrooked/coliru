using uint = unsigned int;

// for each type A, there is a base class Base<A>
template <typename A>
class Base
{
public:
    virtual void f(A& ) = 0;

};


// for each type A, and for each type Sub having methods 
// Sub::f(A& ) and Sub::g(A& ), there is a special subclass 
// of Base<A>, with the name Wrap<A, Sub>.
//
// NOTE: the type Sub has more structure, it is actually
//       a subclass of Base<A>.
template <typename A, typename Sub>
class Wrap : public Base<A>
{
template <typename T1, typename T2>
friend Wrap<T1, T2>* wrap(T2& sub);

public:
    virtual void f(A& a) override 
    {
        // ... do stuff on 'a', using Sub::f() and Sub::g() ...
    }


private:
    Wrap(Sub& s) : sub_( s ) { }
    Sub& sub_;
};


// for each type A, and for each type Sub having methods
// Sub::f(A& ) and Sub::g(A& ), map this to Wrap<A, Sub>
template <typename A, typename Sub>
Wrap<A, Sub>* wrap(Sub& sub)
{
    return new Wrap<A, Sub>( sub );
}



// a subclass of Base<uint>, with the additional 
// structure of having a method Subclass::g(uint& )
class Subclass : public Base<uint>
{
public:
    virtual void f(uint& a) override { /*...*/ }

    void g(uint& a) { /*...*/ }
};



int main()
{
    Subclass sub;
    Base<uint>* w = wrap<uint>(sub);
    // ^ no matching function for call to ‘wrap(Subclass&)’
    //   template argument deduction/substitution failed:
    //   couldn't deduce template parameter ‘A’

    uint a = 0;
    w->f( a );

    // ... delete w ...
    return 0;
}
