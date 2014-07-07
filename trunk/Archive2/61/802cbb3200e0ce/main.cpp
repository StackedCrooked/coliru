#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Matrix
{
private:
protected:
    
    unsigned int rows, columns;
    std::vector< std::vector<double> > elements;
public:

    Matrix( const int r = 2, const int c = 2 ) : rows( r ), columns( c )
    {
        if( ( rows > 0 ) && ( columns > 0 ) )
        {
            elements.resize( rows );
            
            for( unsigned int i = 0; i < rows; i++ )
            {
                elements[i].resize( columns );
            }
        }
        else
        {
            throw invalid_argument( "Matrix cannot have rows/columns less that one" );
        }
    }
    
    Matrix& operator=( const Matrix& rhs )
    {
        rows = rhs.rows;
        columns = rhs.columns;
        
        elements.clear();
        
        if( ( rows > 0 ) && ( columns > 0 ) )
        {
            elements.resize( rows );
            
            for( unsigned int i = 0; i < rows; i++ )
            {
                elements[i].resize( columns );
            }
            
            for( unsigned int i = 0; i < rows; i++ )
            {
                for( unsigned int j = 0; j < columns; j++ )
                {
                    elements[i][j] = rhs( i, j );
                }
            }
        }
        else
        {
            throw invalid_argument( "Matrix cannot have rows/columns less that one" );
        }
        
        return ( *this );
    }
    
    Matrix( const Matrix& mat ) : rows( mat.rows ), columns( mat.columns )
    {
        if( ( rows > 0 ) && ( columns > 0 ) )
        {
            elements.resize( rows );
            
            for( unsigned int i = 0; i < rows; i++ )
            {
                elements[i].resize( columns );
            }
            
            for( unsigned int i = 0; i < rows; i++ )
            {
                for( unsigned int j = 0; j < columns; j++ )
                {
                    elements[i][j] = mat( i, j );
                }
            }
        }
        else
        {
            throw invalid_argument( "Matrix cannot have rows/columns less that one" );
        }
    }

    double& operator()( const unsigned int row, const unsigned int column )
    {
        if( row >= rows || column >= columns )
        {
            cerr << "row: " << row << " Rows: " << rows << " col: " << column << " Columns: " << columns << endl;
            throw invalid_argument( "Row/Column exceeds matrix dimensions" );
        }
        
        return elements[row][column];
    }
    
    const double operator()( const unsigned int row, const unsigned int column ) const
    {
        if( row >= rows || column >= columns )
        {
            cerr << "row: " << row << " Rows: " << rows << " col: " << column << " Columns: " << columns << endl;
            throw invalid_argument( "Row/Column exceeds matrix dimensions" );
        }
        
        return elements[row][column];
    }
    
    friend const Matrix operator*( const Matrix& lhs, const Matrix& rhs );
    
    Matrix& operator*=( const Matrix& rhs )
    {
       ( *this ) = ( ( *this ) * rhs );
        
        return ( *this );
    }
    
    //operator +, -
    
    void MakeIdentity( void )
    {
    }
    
    void Invert( void )
    {
        ( *this ) = Inverse();
    }
    
    const Matrix Inverse( void )
    {
        if( !( IsSquare() ) ){ throw exception( ); }
        
        if( rows == 1 )
        {
            //If matrix is 1x1, return the reciprocal of the value;
            return ( 1 / elements[0][0] );
        }
        
        cout << rows << "x" << columns << endl;
        Matrix temp( rows, columns );
        
        short int sign = 1;
        //*
        for( unsigned int r = 0; r < rows; r++ )
        {
            for( unsigned int c = 0; c < columns; c++ )
            {
                //r/c == current row/column being ignored
                
                //Alternate sign
                sign *= -1;
                
                Matrix _minor( ( rows - 1 ), ( columns - 1 ) );
                
                unsigned int rowIndex = 0, colIndex = 0; //These need better names
                
                for( unsigned int j = 0; j < rows; j++ )
                {
                    colIndex = 0;
                    
                    for( unsigned int k = 0; k < columns; k++ )
                    {   
                        if( ( j != r ) && ( k != c ) )
                        {
                            _minor( rowIndex, colIndex ) = elements[j][k];
                            colIndex++;
                            
                            if( colIndex >= _minor.columns )
                            {
                                rowIndex++;
                            }
                        }
                    }
                }
                
                //Get determinant of minor, multiply by alternating sign
                temp( r, c ) = ( MatrixDeterminant( _minor ) * sign );
            }
        }
        //*/
        cout << this->rows << "x" << this->columns << endl;
        return ( ( 1 / ( this->Determinant() ) ) * temp );
        return temp;
    }
    
    void Transpose( void ){}
    
    Matrix Transposed( void )
    {
        Matrix temp;
        
        return temp;
    }
    
    friend double MatrixDeterminant( const Matrix& mat );
    
    double Determinant( void )
    {
        return MatrixDeterminant( *this );
    }
    
    double Trace( void )
    {
        return 0.0f;
    }
    
    const bool IsSquare( void ) const
    {
        return ( rows == columns );
    }
};

double MatrixDeterminant( const Matrix& mat )
{
    if( !( mat.IsSquare() ) )
    {
        //if not an nxn square matrix
        throw exception( );
    }
    
    if( mat.rows == 1 )
    {
        //If matrix is 1x1, return the only value in the matrix;
        return mat( 0, 0 );
    }
    
    double det = 0.0f;
    int sign = 1;
    
    for( unsigned int i = 0; i < mat.columns; i++ )
    {
        double cofactor = ( mat( 0, i ) * sign );
        
        sign *= -1;
        
        //Build minor - (n-1)x(n-1) matrix
        cout << mat.rows << "x" << mat.columns << endl;
        Matrix _minor( ( mat.rows - 1 ), ( mat.columns - 1 ) );
        
        unsigned int rowIndex = 0, colIndex = 0; //These need better names
        
        for( unsigned int j = 0; j < mat.rows; j++ )
        {
            colIndex = 0;
            
            for( unsigned int k = 0; k < mat.columns; k++ )
            {   
                if( ( j != 0 ) && ( k != i ) )
                {
                    _minor( rowIndex, colIndex ) = mat( j, k );
                    colIndex++;
                    
                    if( colIndex >= _minor.columns )
                    {
                        rowIndex++;
                    }
                }
            }
        }
        
        //Get determinant of minor
        double detMinor = MatrixDeterminant( _minor );
        
        det += ( cofactor * detMinor );
    }
    
    return det;
}

const Matrix operator*( const Matrix& lhs, const Matrix& rhs )
{
    if( lhs.columns != rhs.rows )
    {
        throw invalid_argument( "Incompatible matrices cannot be multiplied" );
    }
    
    Matrix temp( lhs.rows, rhs.columns );
    
    for( unsigned int i = 0; i < lhs.rows; i++ )
    {
        for( unsigned int j = 0; j < lhs.columns; j++ )
        {
            for( unsigned int k = 0; k < lhs.columns; k++ )
            {
                temp( i, j ) += ( lhs( i, k ) * rhs( k, j ) );
            }
        }
    }
    
    return temp;
}

const Matrix operator*( const double scalar, const Matrix& rhs )
{
    Matrix temp = rhs;
    
    for( unsigned int i = 0; i < rhs.rows; i++ )
    {
        for( unsigned int j = 0; j < rhs.columns; j++ )
        {
            temp( i, j ) *= scalar
        }
    }
    
    return temp;
}

int main()
{
    std::cout << "Testing\n";
    
    Matrix test1( 3, 3 ), test2( 3, 3 );
    
    test1( 0, 0 ) = 1;
    test1( 0, 1 ) = 0;
    test1( 0, 2 ) = 0;
    test1( 1, 0 ) = 0;
    test1( 1, 1 ) = 1;
    test1( 1, 2 ) = 0;
    test1( 2, 0 ) = 0;
    test1( 2, 1 ) = 0;
    test1( 2, 2 ) = 1;
    
    test2( 0, 0 ) = 4;
    test2( 0, 1 ) = 3;
    test2( 0, 2 ) = 3;
    test2( 1, 0 ) = 2;
    test2( 1, 1 ) = 1;
    test2( 1, 2 ) = 3;
    test2( 2, 0 ) = 9;
    test2( 2, 1 ) = 1;
    test2( 2, 2 ) = 5;
    
    Matrix test3 = test1 * test2;
    
    test3.Invert();
    
    //cout << test3( 0, 0 ) << " " << test3( 0, 1 ) << "\n" << test3( 1, 0 ) << " " << test3( 1, 1 ) << "\n" << test3.Determinant();
    cout << test3.Determinant();
}
