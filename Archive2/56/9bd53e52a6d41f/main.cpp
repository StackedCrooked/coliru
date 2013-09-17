
struct args{};

struct A {
    A(A* next_=nullptr) :next(next_) {}
    void B() {C();}
protected:
    A* next;
    virtual args C(args a=args()) =0;
};

struct D : public A {   
    virtual args C(args a) {
        if (next)
            next->C(a);
        return a;
    }
};

int main() {
    D one;
    D two(one);    
    two.B();
}