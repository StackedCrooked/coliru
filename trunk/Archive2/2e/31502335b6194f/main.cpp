template<class T> class A
{

};

template<class T> class B : public A<T>
{
public:  // THIS
    B(int a, int b = 0);
};

template<class T> B<T>::B(int a, int b /* =0 */)
{

}

class C : public B<int>
{
    using B::B;
};


int main() {
    C obj(5);
    C obj2(5, 3);
}