struct base{ void f(){} };
struct derived : base{};

int main(){
    using bmp = void (base::*)();
    using dmp = void (derived::*)();
    bmp p = &base::f;
    dmp p2 = p;
}