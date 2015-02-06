template < typename NUMERIC_TYPE > struct Vector3
{
    typedef NUMERIC_TYPE type ;
    
    template < typename T > Vector3( T a , T b, T c ) : x(a), y(b), z(c) {}
    
    template < typename T > operator Vector3<T>() const { return Vector3<T>(x,y,z) ; }
    
    template < typename OTHER_VECTOR > OTHER_VECTOR as() const 
    { return OTHER_VECTOR(x,y,z) ; } // can acees typename OTHER_VECTOR::type if needed
    
    NUMERIC_TYPE x ;
    NUMERIC_TYPE y ;
    NUMERIC_TYPE z ;
};

typedef Vector3<double> Vector3d;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

int main()
{
    Vector3d dblVec(3.2, 5.4, 9.5) ;
    Vector3i intVec = dblVec ;
    
    intVec = dblVec.as<Vector3i>() ;
}
