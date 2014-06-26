class A {
public:

    class B fun1() const;

    class B* m_b;
};

extern void myfun( const class B& b );

int main() { 
    A a; 
    myfun(*a.m_b); 
} 