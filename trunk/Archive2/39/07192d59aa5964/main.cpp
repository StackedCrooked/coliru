
struct args{};

struct A {
    A(A* next_=nullptr) :next(next_) {}
    void B() {C(this);}
protected:
    A* next;

    static args C(A* self, args a=args()) {
        self->C_impl(a);
    }
private:
    virtual args C_impl(args a) =0;
};

struct D : public A {   
    virtual args C_impl(args a) {
        if (next)
            C(next, a);
        return a;
    }
};

int main() {
    D one;
    D two(one);    
    two.B();
}