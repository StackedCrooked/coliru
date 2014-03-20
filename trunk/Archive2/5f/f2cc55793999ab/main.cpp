#include <chrono>
#include <iostream>

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

	inline float& operator()( int row, int col ){
		return m_pArray[ (row + col * m_nRows) ];
	}

	float operator()(int row, int col) const{
		return m_pArray[ (row + col * m_nRows) ];
	}

	float *GetPr(){
		return m_pArray;
	}

public:
	float *m_pArray;
	int m_nRows, m_nCols;
};

std::chrono::high_resolution_clock::time_point
timeGetTime(){
	return std::chrono::high_resolution_clock::now();
}

static inline std::chrono::high_resolution_clock::time_point myclock();

int main()
{
	using namespace std::chrono;
	using std::cout;
	high_resolution_clock::time_point t, dt;
	duration<double> time_span;

	int nRows(16384), nCols(8192);
	CMatrix src( nRows, nCols ), dst( nRows, nCols );
	float *psrc( src.GetPr() ), *pdst( dst.GetPr() );

	t = myclock();

	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			dst( i, j ) = src( i, j );
		}
	}

	dt = myclock();
	//printf("Operator Access %ld.%ld s\n",  dt / 1000, dt % 1000);

	time_span = duration_cast< duration<double> >(dt-t);
	cout << "operator " << time_span.count() << '\n';

	t = myclock();
	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			pdst[ i + j*nRows ] = psrc[ i + j*nRows ];
		}
	}
	dt = myclock();
	time_span = duration_cast< duration<double> >(dt-t);
	cout << "direct " << time_span.count() << '\n';

	t = myclock();

	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			dst( i, j ) = src( i, j );
		}
	}

	dt = myclock();
	//printf("Operator Access %ld.%ld s\n",  dt / 1000, dt % 1000);

	time_span = duration_cast< duration<double> >(dt-t);
	cout << "operator " << time_span.count() << '\n';

	t = myclock();
	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			pdst[ i + j*nRows ] = psrc[ i + j*nRows ];
		}
	}
	dt = myclock();
	time_span = duration_cast< duration<double> >(dt-t);
	cout << "direct " << time_span.count() << '\n';
	t = myclock();

	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			dst( i, j ) = src( i, j );
		}
	}

	dt = myclock();
	//printf("Operator Access %ld.%ld s\n",  dt / 1000, dt % 1000);

	time_span = duration_cast< duration<double> >(dt-t);
	cout << "operator " << time_span.count() << '\n';

	t = myclock();
	for( int j = 0; j < nCols; j++ ){
		for( int i = 0; i < nRows; i++ )
		{
			pdst[ i + j*nRows ] = psrc[ i + j*nRows ];
		}
	}
	dt = myclock();
	time_span = duration_cast< duration<double> >(dt-t);
	cout << "direct " << time_span.count() << '\n';
	return 0;
}

static inline std::chrono::high_resolution_clock::time_point myclock()
{
	return std::chrono::high_resolution_clock::now();
}
