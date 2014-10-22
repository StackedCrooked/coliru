template<class T>
class A {
protected:
    int x;
};

template<class T>
class B : public A<T> {
public:
    B() { this->x = 3; }
};


int main(int argc, char** argv) {
    B<int> b;
    return 0;
}