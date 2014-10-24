template<class A>
struct B { 
    friend typename A;
};

class C{};

int main(){
    B<C> b1;
}