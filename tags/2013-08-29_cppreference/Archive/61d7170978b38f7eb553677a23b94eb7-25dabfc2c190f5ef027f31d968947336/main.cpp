    #include<iostream>
    using namespace std;

    template<typename T>
    class X
    {
    public:
        void func(T t) const;
    };

    template<typename T>
    void X<T>::func(T b) const
    {
        cout << endl << "Default Version" << endl;
    }


    template<>
    class X<int>
    {
        public:
        void func(int y) const;
    };

    void X<int>::func(int y) const
    {
        cout << endl << "Int Version" << endl;
    }

    int main()
    {
        X<int> x;
        x.func(42);
    }
