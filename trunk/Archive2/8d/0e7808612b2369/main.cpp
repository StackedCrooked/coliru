#include <vector>
#include <iostream>
#include <initializer_list>

using namespace std;

struct A {
    A(int=0)      { cout << "A::A" << endl; }        
    ~A()          { cout << "A::~A" << (heavy?"(heavy)":"(light)") << endl; }               
    A(const A& t) { cout << "A::A(A&)" << endl;  heavy = t.heavy; }              
    A(A&& t)      { cout << "A::A(A&&)" << endl; t.heavy=false; }           
private:
    bool heavy = true;
};

struct B {
    vector<A> va;
    B(const vector<A>& va) : va(va)                { cout << "var" << endl; }
    B(const initializer_list<A>& ila) : va(ila)    { cout << "ilr" << endl; }
    B(vector<A>&& va) : va(move(va))               { cout << "vam" << endl; }
    B(initializer_list<A>&& ila) : va(move(ila))   { cout << "ilm" << endl; }
    B()                                            { cout << "nil" << endl; }  
    
    void add_A ( A&& a ) { va.push_back( move(a) ); }
    
    ~B() { cout << "B::~B" << (va.size()?"(heavy)":"(light)") << endl;   }
};

template <typename Cont, typename Item>
Cont&& move_back_return( Cont&& cont, Item&& item )
{
    cont.push_back( move(item) );
    return move(cont);
}

int main(void) {
    B b{};
    b.va.reserve(7);
    b.va.emplace_back();
    b.add_A( A{} );
    cout << " basically done\n";
    return 0;
}