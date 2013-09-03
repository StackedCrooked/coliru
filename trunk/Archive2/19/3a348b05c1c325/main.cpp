struct A {
    void func();
};

int func2(char);

void A::func() 
{func2('a');}

int main() {
}