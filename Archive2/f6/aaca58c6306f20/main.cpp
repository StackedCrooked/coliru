//
//    Austin Jensen
//	Intro to Computer Programming, C++
//	4/28/14
//
//
//
//
//
//
//
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	char letter;
	float number;
	ifstream istream;
	ofstream ostream;

	istream.open ("inLab6.dat");
	ostream.open ("outLab6.out");
	
	istream>>letter>>number;

	ostream<<letter<<endl<<number;
return(0);
}