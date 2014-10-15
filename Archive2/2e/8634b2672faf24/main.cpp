#include <stack>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int bitArray[6][24]; //the Array of bits, can only be a 1 or 0
int ex=0; //ex keeps track of the current exponent to use to calculate the decimal value of a binary digit
int decArray[18]; //array to store decimals
int byteToDecimal(int pos, int row) //takes two variables so you can give it an array column and row
{
  int numholder=0; //Temporary number for calculations

  for(int x=pos; x<pos+8;x++) //pos is used to adjust where we start and stop looking at 1's and 0's in a row
  {
    if(bitArray[row][x] != 0)//if the row and column is a 1
    {
      numholder += pow(2, 7-ex);//2^(7-ex), meaning the first bit is worth 2^7, and the last is 2^0      
    }
    ex++;
  }
  ex=0;
  return numholder;
}

int main(){
    bitArray[0][0] = 1;
    cout << byteToDecimal(0,0) << endl;
}
