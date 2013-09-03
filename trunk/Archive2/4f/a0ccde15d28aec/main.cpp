struct A {
    void B();
};

void C();
void A::B() 
{C();}

int main() {
    A a;
}