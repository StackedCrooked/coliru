template<typename T> class Matrix;

template<typename T>
Vector<T> operator*(const Matrix<T>& m, const Vector<T>& v)
{
    Vector<T> r;
    // ... m.v[i] and v.v[i] for direct access to elements ...
    return r;
}

template<typename T>
class Vector {
    T v[4];
public:
    friend Vector operator*<>(const Matrix<T>&, const Vector&); /* line 7 */
    // ...
};

template<typename T>
class Matrix {
    Vector<T> v[4];
public:
    friend Vector<T> operator*<>(const Matrix&, const Vector<T>&); /* line 14 */
    // ...
};

int main()
{
    Vector<int> v;
}