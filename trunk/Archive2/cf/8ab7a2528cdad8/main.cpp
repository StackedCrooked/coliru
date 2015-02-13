class class_A
{
    friend int FF();
private:
    int Test;
public:
    class_A();
};


int FF(class_A *nClass_A)
{
    return nClass_A->Test;
}

class_A::class_A() {}

int main() {
    class_A mClass_A;
    FF(&mClass_A);
}