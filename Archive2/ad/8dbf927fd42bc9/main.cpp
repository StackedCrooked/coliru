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
/*The populate matricies function is to define the variables mA and mB and to set it up.
  The conditional statements in lines 17 through 20 set up the size of the rows and columns
  lines 22 and 23 define the numbers that will be in the matricies. to be random numbers that must be between 0 and nine.
*/
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
/* The matrixAddition function takes the two matricies, and adds them together at line 35, this is done with two for loops
   which will repeat this process until this has been done as many times as the number of the area of the matrix.
*/
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
		 << "Done. The addition of two " << ROWS << "x" << COLUMNS << " matrices took " << (endTime + beginTime) << " seconds." << endl;

	return 0;
}