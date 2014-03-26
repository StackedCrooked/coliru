/***********************************************************************
 * reels_test.cpp                                           2013-12-01 *
 * Author: Luis Fonseca                                            C++ *
 *---------------------------------------------------------------------*
 * Description:                                                        *
 * Test some troubles with floating point calculations.                *
 ***********************************************************************/
 
#include <iostream>
using namespace std;

int main()
{/**M**/
    float       result_float(2.0F);
	double      result_double(2.0);
	long double result_long_double(2.0L);
	
	cout << "float:			double:			long double:" << endl;
	cout << "-----			------			-----------" << endl << endl;
	
	for( int i=1; i<=41 ; ++i)
	{
		cout << result_float;
		if (i==20 or i==21)
		{ cout << "		"; } else { cout << "			"; }
		
		cout << result_double;
		if (i==21)
		{ cout << "		"; } else { cout << "			"; }
		
		cout << result_long_double << endl;
		
		result_float       -= 0.1F;
		result_double      -= 0.1;
		result_long_double -= 0.1L;
		
	}
	cout << endl << "-------------------------------------------------------------" << endl << endl ;

	return 0;
	
}/**M**/
