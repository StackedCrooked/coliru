template<class A>
struct B { 
    friend typename A::D;
};

struct C {
    struct D {};
};

int main(){
    B<C> b1;
}