//In Maths.h file

template <class T> class Maths{
public:
    Maths<T>(T lhs);

    template<typename U>
    Maths<T>(const Maths<U>& otherMaths);

    ~Maths();

    template <typename U>
    Maths<T>& operator+(const Maths<U>& rhs);

    template <typename U> 
    Maths<T>& operator*(const Maths<U>& rhs);

    template <typename U> 
    Maths<T>& operator-(const Maths<U>& rhs);

private:
    T _lhs;
};



//In Maths.cpp file

template <class T>
Maths<T>::Maths(T lhs){
    _lhs = lhs;
    return _lhs;
}

template <class T> template <typename U>
Maths<T>::Maths(const Maths<U>& otherMaths){
    _lhs = otherMaths._lhs;
}

template <class T>
Maths<T>::~Maths(){}

template <class T> template <typename U>
Maths<T> Maths<T>::operator+(const Maths<T>& rhs){ return Maths._lhs + rhs; }

template <class T> template <typename U>
Maths<T> Maths<T>::operator-(const Maths<T>& rhs){ return Maths._lhs - rhs; }

template <class T> template <typename U>
Maths<T> Maths<T>::operator*(const Maths<T>& rhs){ return Maths._lhs * rhs; }