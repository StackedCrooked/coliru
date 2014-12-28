#include <iostream>
#include <fstream>
#include <stdint.h>
#include <errno.h>
#include <cstring>
#include <bitset>
#include <vector>

using namespace std;


char * buffer(string path, int position)
{
	static char buffer[102400];

	ifstream myfile;
	myfile.open(path, ios::in | ios::out | ios::binary);
	myfile.seekg(102400 * position, ios::beg); //Depending on the position (for later when it has to read another chunk of the file (in 100MB)
	myfile.read(buffer, 102400); //Read the first 100MB into buffer)
	myfile.close();
	cout << "The size of a random value in buffer before is " << uint64_t(buffer[5253]) << "\n"; //Proof that it's reading the same values.

	return buffer; //Return said buffer array (though I'm told it has to be a pointer and not the actual array)
}

//Create an array and every time there is a new byte, store it in the array.
//Check every single byte to make sure there's nothing the same
vector<uint64_t> bytes; //New byte storage
bool everRun(false); //First run check.

int compare(char buffer[102400])
{
	if (!everRun)
	{
		bytes.push_back(uint64_t(buffer[0]));
		//If it's never run, read the first byte into the vector.
	}
	for each (char bufferByte in buffer) //For each byte in the buffer...
	{
		for each (uint64_t byte in bytes) //and for each byte in NewByte Storage
		{
			if (bufferByte != byte) //Compare the current bufferByte with the current byte in NewByte Storage (the vector)
			{
				uint64_t byteT(bufferByte); //If its new, turn it into a uint and..
				bytes.push_back(byteT); //..put it in newByte storage
			}
			//else...return to the loop to check the next byte in the buffer
		}
	}

	cout << "The size of a random value in buffer before is " << uint64_t(buffer[5253]) << "\n"; //Proof that it's reading the same values.
	
	cout << "The size of the vector is " << bytes.size(); 
	return 0;
}


int main()
{
	string filepath ("C:\\Users\\Amaze SUCH WOW\\Desktop\\Recording_2014-12-24_20-47-31_0002.ts"); //Test run. Static file path randomly chosen by me.
	cout << "Number of passes on said file: " << passes(filepath, 102400); //Get the number of passes.
	compare(buffer(filepath, 0)); //Test run. Test first 100MB before running it by the number of passes actually required. 
	cin.get();
	return 0;
}