
struct A { int a; };

void TakesA ( A& arf ) {
    arf.a += 1;
}

struct B : private A  {
    
    void doit () {
        // static_cast
        A& a = static_cast<A&>(*this);
        TakesA( a );
    }
    
    void doit2 () {
        // c-style cast -- what is it resolving too?
        A& a = (A&)(*this);
        TakesA( a );
    }
    
};

int main() {
    
    
}