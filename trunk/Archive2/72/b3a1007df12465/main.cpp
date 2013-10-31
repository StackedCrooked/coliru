template<int> struct A { };

template<typename T>
int& int_if_addable(A<sizeof(T() + T())>*);

template<typename T>
float& int_if_addable(...);

using nullptr_t = decltype(nullptr);

template<typename T, typename Sfinae = nullptr_t>
struct B {
    static float& int_if_addable();
};

template<typename T>
struct B<T, decltype( (T() + T()), nullptr )> {
    static int& int_if_addable();
};

struct X { };

struct Y { };
Y operator+(Y, Y);

struct Z { };
Z operator+(Z, Z) = delete;

int main()
{
 float& x = int_if_addable<X>(0);
 int& y = int_if_addable<Y>(0);
 float& z = int_if_addable<Z>(0);

 float& a = B<X>::int_if_addable();
 int& b = B<Y>::int_if_addable();
 float& c = B<Z>::int_if_addable();
}