#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>

using std::vector;
using std::cout;
using std::endl;
using std::rand;
using std::setw;
using std::endl;

void populateMatrices(vector<int>& mA, vector<int>& mB, int ROWS, int COLUMNS)
{
    for (int rowIdx = 0; rowIdx < ROWS; rowIdx++)
	{
		for (int columnIdx = 0; columnIdx < COLUMNS; columnIdx++)
		{
			mA[rowIdx + columnIdx] = rand() % 10;
			mB[rowIdx + columnIdx] = rand() % 10;
		}
	}
}

void calcMatrixAddition(vector<int>& mA, vector<int>& mB, vector<int>& mC, int ROWS, int COLUMNS)
{
	for (int rowIdx = 0; rowIdx < ROWS; rowIdx++)
	{
		for (int columnIdx = 0; columnIdx < COLUMNS; columnIdx++)
		{
			mC[rowIdx + columnIdx] = mA[rowIdx + columnIdx] + mB[rowIdx + columnIdx];
		}
	}
}

void outputMatrixC(vector<int>& mA, vector<int>& mB, vector<int>& mC, int ROWS, int COLUMNS)
{
	for (int rowIdx = 0; rowIdx < ROWS; rowIdx++)
	{
		for (int columnIdx = 0; columnIdx < COLUMNS; columnIdx++)
		{
			cout << setw(2) << mA[rowIdx + columnIdx] << ' ';
		}

		if (rowIdx == ROWS / 2) { cout << "\t+\t";}
		else {cout << "\t\t";}

		for (int columnIdx = 0; columnIdx < COLUMNS; columnIdx++)
		{
			cout << setw(2) << mB[rowIdx + columnIdx] << ' ';
		}
		
		if (rowIdx == ROWS / 2) { cout << "\t=\t";}
		else {cout << "\t\t";}

		for (int columnIdx = 0; columnIdx < COLUMNS; columnIdx++)
		{
			cout << setw(2) << mC[rowIdx + columnIdx] << ' ';
		}
		cout << endl;
	}
}

int main()
{
    const int ROWS		= 5;
	const int COLUMNS	= 5;
    time_t beginTime, endTime;

	vector<int> matrixA( ROWS * COLUMNS );
	vector<int> matrixB( ROWS * COLUMNS );
	vector<int> matrixC( ROWS * COLUMNS );

	cout << "Populating matrices; please wait..." << endl;
	populateMatrices(matrixA, matrixB, ROWS, COLUMNS);
	
	beginTime = time(0);

	cout << "Performing calculation. Timer started..." << endl;
	calcMatrixAddition(matrixA, matrixB, matrixC, ROWS, COLUMNS);
	
	endTime = time(0);

	outputMatrixC(matrixA, matrixB, matrixC, ROWS, COLUMNS);

	cout << endl 
		 << "Done. The addition of two " << ROWS << "x" << COLUMNS << " matrices took " << (endTime - beginTime) << " seconds." << endl;

	return 0;
}