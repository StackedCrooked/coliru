#include <string>

#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace model
{
    using std::string;

    namespace ublas = boost::numeric::ublas;

    class Vector2D
    {
        public:
            Vector2D( float x, float y );
            Vector2D( const Vector2D& rhs );
            Vector2D& operator=( const Vector2D& rhs );
            virtual ~Vector2D();

            /// Operators:
            Vector2D operator*( const float rhs );
            Vector2D operator-();
 
            /// Other methods:
            string toString(); 
        protected:
            ublas::vector<float> underwater_vector;
        private:
    };
}

#include <boost/numeric/ublas/blas.hpp> 
#include <sstream>

namespace model
{
    Vector2D::Vector2D( float x, float y ) : underwater_vector( 2 )
    {
        this->underwater_vector.insert_element( 0, x );
        this->underwater_vector.insert_element( 1, y );
    }

    Vector2D::Vector2D( const Vector2D& rhs )
    {
        ublas::blas_1::copy( this->underwater_vector, rhs.underwater_vector );
    }

    Vector2D& Vector2D::operator=( const Vector2D& rhs )
    {
        if( this != &rhs )
        {
            ublas::blas_1::copy( this->underwater_vector, rhs.underwater_vector );
        }
        return *this;
    }

    Vector2D::~Vector2D()
    {
    }

    /** @brief operator*
      *
      */
    Vector2D Vector2D::operator*( const float rhs )
    {
        Vector2D lhs = *this;
        lhs.underwater_vector[0] = lhs.underwater_vector[0] * rhs;
        lhs.underwater_vector[1] = lhs.underwater_vector[1] * rhs;
        return lhs;
    }

    /** @brief operator-
      *
      */
    Vector2D Vector2D::operator-()
    {
        Vector2D lhs = *this;
        lhs.underwater_vector[0] *= -1;
        lhs.underwater_vector[1] *= -1;
        return lhs;
    }

    /** @brief toString
      *
      */
    string Vector2D::toString()
    {
        std::stringstream ss;
        ss << this->underwater_vector;
        return ss.str();
    }
}

#include <iostream>
#include <exception>

int main( int argc, char* argv[] )
{
    using std::cout;
    using std::cin;
    using std::cerr;
    using std::endl;
    using std::string;
    using std::exception;
 
    using model::Vector2D;

    Vector2D* vectorA = nullptr;
    Vector2D* vectorB = nullptr; 

    try
    {
        vectorA = new Vector2D( 10.45f, 3.3f ); 

        cout << vectorA->toString() << endl; 

        vectorB = ( vectorA * 2.0f );

        cout << vectorB->toString() << endl; 
    }
    catch( exception& ex )
    {
        cout << "exception:" << endl;
        cout << ex.what() << endl;
        cin.get();
    }

    return EXIT_SUCCESS;
}