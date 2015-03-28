template <class T, class V>
class A{ }

typedef A<T, int> MyPartialSpecializa<T>; 

int main(){ a.foo(); }