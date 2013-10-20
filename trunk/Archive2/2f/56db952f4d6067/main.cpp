     void func ();
     
    namespace N {
    class C {
    int val;
    friend void func ();
    };
    }
     
    void func () {
    N::C o; o.val = 123; /* error */
    }
     
    int main() { }