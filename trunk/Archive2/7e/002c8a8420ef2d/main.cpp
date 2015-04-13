class Derived;

class Base{
     public:
     void dosomestuff(Derived instanceOfDerived);
};

class Derived : public Base{
     //Something
};

void Base::dosomestuff(Derived instanceOfDerived){
}

int main(){
    Derived d;
    d.dosomestuff(d);
}