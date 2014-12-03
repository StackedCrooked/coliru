template<class T>
struct X{ typedef T type; };

template<class T>
struct Y : X<T> {
    typedef typename Y::type stuff;
    // error about "needed , before 'type'", fixed with
    //typedef typename X<T>::type stuff;
};