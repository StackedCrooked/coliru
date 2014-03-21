#include <iostream>
#include <ctime>
#include <memory>

class CMatrix{

public:
    explicit CMatrix( int rows, int cols ){
		m_pArray = new float[ rows * cols ];
		m_nRows  = rows;
		m_nCols  = cols;
	}

	~CMatrix(){
		delete [] m_pArray;
	}

	float& operator()( int i, int j ){
		return m_pArray[ (i + j * m_nRows) ];
	}

	float operator()(int i, int j) const{
		return m_pArray[ (i + j * m_nRows) ];
	}

	float *GetPr(){
		return m_pArray;
	}

private:
	float *m_pArray;
	int m_nRows, m_nCols;
};

int main()
{
	int nRows(16384), nCols(8192);
	CMatrix src( nRows, nCols ), dst( nRows, nCols );
	float *psrc( src.GetPr() ), *pdst( dst.GetPr() );
    
    // to avoid distortion in results due to cache misses 
    // when accessing the chunk of memory for the first time 
    std::uninitialized_copy( psrc, psrc+(nRows*nCols), pdst ) ;

	auto start = std::clock() ;
	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			dst( i, j ) = src( i, j );
		}
	}
	auto end = std::clock() ;
	std::cout << "Operator Access: " << double(end-start) / CLOCKS_PER_SEC << " secs.    " ;

	start = std::clock() ;
	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			pdst[ i + j*nRows ] = psrc[ i + j*nRows ];
		}
	}
	end = std::clock() ;
	std::cout << "Direct Access: " << double(end-start) / CLOCKS_PER_SEC << " secs.\n\n" ;
}
