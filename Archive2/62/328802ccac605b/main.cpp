namespace N {

    class C {
    public:
        friend int f(const C& c){
            return 1;
        }
        friend int g(const C& c){
            return 2;
        }
    };
    
    int f(const C& c);
    int g(const C& c);
    
    class D {
    public:
        void f(){
            g(C{});            //ADL finds this
            ::N::f(C{});       //not found dispite full qualification
        }
    };
}

int main() {}
