#ifndef __MYVECTOR_CLASS__
#define __MYVECTOR_CLASS__

template<class Type>
class MyVector{
public:
    //....
    MyVector& operator=(const MyVector& source); //works
    
    template<typename T>
    friend MyVector<T> operator+(MyVector<T> lhs, const MyVector<T> &rhs); //doesnt
    //....
};

template<class Type>
MyVector<Type>& MyVector<Type>::operator=(const MyVector &v){
    /*if (_d != v._d){
        _d = v._d;
        _deleteArray();
        _createArray(_d);
    }
    _assignValues(v._vector, (v._vector + _d));*/
    return *this;
}


template<class Type>
MyVector<Type> operator+(MyVector<Type> lhs, const MyVector<Type> &rhs){
    /*if (lhs._d == rhs._d){
        for (int index = 0; index < lhs._d; index++){
            lhs._vector[index] += rhs._vector[index];
        }
    }*/
    return lhs;
}

#endif // __MYVECTOR_CLASS__

int main()
{
	MyVector<float> a;
    MyVector<float> b;
    a = b; // works alone
    a = a + b; //breaks
}