#include <iostream>
using namespace std;


void askValues(int a[], int); // << changed fron int to void
void dispValues(int a[], int);
int countOdd(int a[], int);
int countEven(int a[], int);
void copyOdd(int a[], int b[], int); // changed from int to void
void copyEven(int a[], int b[], int); // changed from int to void
void dispSmallest(int a[], int);
void dispLargest(int a[], int);

int main()
{

    const int size = 10;
    int num[size];

    int oddCount = 0;
    int evenCount = 0;

    askValues(num,size);                        //This function will ask the user to put values in the array.
    cout << endl << "The numbers are: ";

    dispValues(num,size);                       //This function will display all values of the array.
    oddCount = countOdd(num,size);              //This function will return the number of odd numbers.
    evenCount = countEven(num,size);            //This function will return the number of even numbers.

    int odd[oddCount];                          //This array will store all odd numbers.
    int even[evenCount];                        //This array will store all even numbers.
    copyOdd(num,odd,size);                    //This function will copy all ODD numbers found in the first array to the second array
    copyEven(num,even,size);                  //This function will copy all EVEN numbers found in the first array to the second array

    cout << endl << "All Odd Numbers: ";
    dispValues(odd,oddCount);

    cout << endl << "All Even Numbers: ";
    dispValues(even,evenCount);

    cout << endl << "Smallest number in ALL numbers: ";
    dispSmallest(num,size);                     //This function will display the smallest number in the array.

    cout << endl << "Smallest ODD number: ";
    dispSmallest(odd,oddCount);

    cout << endl << "Smallest EVEN number: ";
    dispSmallest(even,evenCount);

    cout << endl << "Largest number in ALL numbers: ";
    dispLargest(num,size);                      //This function will display the largest number in the array.

    cout << endl << "Largest ODD number: ";
    dispLargest(odd,oddCount);

    cout << endl << "Largest EVEN number: ";
    dispLargest(even,evenCount);

    return 0;
}

void askValues(int a[], int s)
{
    cout << endl << "Type 10 numbers: ";
    for (int i = 0; i < s; i++)
        {
            cin >> a[i];
        }
}

void dispValues(int a[], int s)
{
    for (int i = 0; i < s; i++)
        {
            cout << a[i] << " ";
        }
}

int countOdd(int a[], int s)
{/*
    for (int i = 0; i < s; i++)
        {
            if (i %2 != 0)
                {
                    a[i] = i;
                }
        }
    */
    int numberOfOdd = 0;
    for( int i = 0; i < s; i++ )
    {
        if( a[ i ] % 2 != 0 ) // if odd
        {
            ++numberOfOdd; // increment numberOfOdd
        }
    }
    return numberOfOdd; // return
}

int countEven(int a[], int s)
{/*
    for (int i = 0; i < s; i++)
        {
            if (i %2 == 0)
                {
                    a[i] = i;
                }
        }
    */

    //
    // ung logic d2 kaparehas lng nung countOdd() function
    //
    int numberOfEven = 0;
    for( int i = 0; i < s; i++ )
    {
        if( a[ i ] % 2 == 0 ) // tignan mo ung logic sa countOdd function
        {
            ++numberOfEven;
        }
    }
    return numberOfEven;
}

// void since the function doesnt return anything
/*int*/void copyOdd(int a[], int b[], int s)
{
    int j = 0; // index of b[ ]
    for( int i = 0; i < s; i++ )
    {
        if( a[ i ] % 2 != 0 ) // if a[ i ] is odd
        {
            b[ j ] = a[ i ]; // then copy it to b[ j ]
            j++; // increment j para sa susunod na element ma-isistore ung next odd number
        }
    }
}

/*int*/ void copyEven(int a[], int b[], int s)
{
   int j = 0;
   for( int i = 0; i < s; i++ )
   {
       if( a[ i ] % 2 == 0 )
       {
           b[ j ] = a[ i ];
           j++;
       }
   }
}

void dispSmallest(int a[], int s)
{
    //int small = a[ 1 ];
    int small = a[ 0 ]; // sa 0 lagi ang start ng array
    for (int i = 0; i < s; i++)
        {
            if (a[i] < small)
                {
                    small = a[i];
                }
        }
    cout << small;
}

// follows the same logic like dispSmallest
void dispLargest(int a[], int s)
{
    int largest = a[ 0 ];
    for( int i = 0; i < s; i++ )
    {
        if( a[ i ] > largest )
        {
            largest = a[ i ];
        }
    }
    cout << largest;
}