struct A2;

struct A1 {
    A1(){}
    A1(A1 *){};  
    A1(A2 &){};
};

struct A3 {
    A3(){}
    A3(A1){}
    A3(A3 *){}
};

struct A2 {
    A2(A1 &){};  
    A2(A3 *){};
};

int main() {
    A1 a1 = new A1();
    A2 a2= a1;
    A3 a3 = a1 =a2 = new A3();
}