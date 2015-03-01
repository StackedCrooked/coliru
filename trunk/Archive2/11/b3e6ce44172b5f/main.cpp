template<class T, class U>
struct Outer { };

template<class T> struct Outer<T, T>;

template<class T> struct Outer<T, T>;
int main(){ }