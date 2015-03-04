    template<class T>
    class A
    {
    public:
        template<class W> class Y; //declaration
        template<class V> class U{ V v; };  //definition
    };
    
    A<int> a;
    int main(){ }