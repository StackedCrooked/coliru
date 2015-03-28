template <class T, class V>
class A{ };

typedef template <class T> A<T, int> MyPartialSpecializa<T>; 

int main(){ }