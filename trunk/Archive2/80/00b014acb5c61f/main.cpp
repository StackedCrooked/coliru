
#include <iostream>


struct A;
struct B;
struct C;


void Dispatch(const B*, const B*);
void Dispatch(const C*, const C*);
void Dispatch(const B*, const C*);
void Dispatch(const C*, const B*);
void Dispatch(const A*, const A*);


struct IDispatcher
{
    virtual ~IDispatcher() {}
    virtual void Dispatch(const B* b) const = 0;
    virtual void Dispatch(const C* c) const = 0;
};

template<class T>
struct Dispatcher : public IDispatcher
{
private:
    const T* t;

public:
    Dispatcher(const T* _t) : t(_t) {}

    void Dispatch(const B* b) const override {
        return ::Dispatch(t, b);
    }

    void Dispatch(const C* c) const override {
        return ::Dispatch(t, c);
    }
};


struct A
{
    virtual ~A() {}
    virtual void Dispatch(const A*) const = 0;
    virtual void Dispatch(const IDispatcher*) const = 0;
};

struct B : public A
{
    void Dispatch(const A* other) const override {
        Dispatcher<B> disp(this);
        return other->Dispatch(&disp);
    }
    void Dispatch(const IDispatcher* disp) const override {
        return disp->Dispatch(this);
    }
};

struct C : public A
{
    void Dispatch(const A* other) const override {
        Dispatcher<C> disp(this);
        return other->Dispatch(&disp);
    }
    void Dispatch(const IDispatcher* disp) const override {
        disp->Dispatch(this);
    }
};

void Dispatch(const B*, const B*) {
    std::cout << "B,B\n";
}

void Dispatch(const C*, const C*) {
    std::cout << "C,C\n";
}

void Dispatch(const B*, const C*) {
    std::cout << "B,C\n";
}

void Dispatch(const C* c, const B* b) {
    return Dispatch(b, c);
}

void Dispatch(const A* a1, const A* a2) {
    return a1->Dispatch(a2);
}


int main()
{
    B b;
    C c;
    Dispatch( (A*)&b, (A*)&c );
    return 0;
}