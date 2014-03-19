struct S {
    virtual void f();
};
void (S::*pmf)();
void g(S* sp) {
    sp->f();         // 1: polymorphic
    sp->S::f();      // 2: non-polymorphic
    (sp->S::f)();    // 3: non-polymorphic
    (sp->*pmf)();    // 4: polymorphic
    (sp->*&S::f)();  // 5: polymorphic
}

int main()
{
}