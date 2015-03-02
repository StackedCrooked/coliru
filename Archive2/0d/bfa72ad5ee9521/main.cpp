template<class T, class U>
struct Outer {
template<class X, class Y> struct Inner;
template<class Y> struct Inner<T, Y>; // #1a
template<class Y> struct Inner<T, Y> { }; // #1b; OK: valid redeclaration of #1a
template<class Y> struct Inner<U, Y> { }; // #2
};
Outer<int, char> outer;
int main(){ }