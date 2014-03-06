template<typename T> class Matrix;

template<typename T>
class Vector 
{
     T v[4];
public:
     friend Vector operator* (const Matrix<T>&, const Vector&);
};


int main()
{
}