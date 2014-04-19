struct A{
    explicit operator bool() const {return false;}
};

int main() {
    A a;
    if (a)
       throw 1;
   else 
       throw 2;
}