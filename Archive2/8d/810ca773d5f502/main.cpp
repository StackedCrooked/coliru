// Debugging: grades.cpp


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

const int NUM_GRADES = 10;
const int NUM_SUDENTS = 3;

int findHighest( int * );
int findLowest( int * );
void printDatabase( const int [][NUM_GRADES], const char [][ 20 ] );

int main()
{
int student1[ NUM_GRADES ] = { 0 };
int student2[ NUM_GRADES ] = { 76, 89, 81, 42, 66, 93, 104,
                                91, 71, 85 };
int student3[ NUM_GRADES ] = { 65, 69, 91, 89, 82, 93, 72,
                                76, 79, 99 };
char names[ NUM_SUDENTS ][ 20 ] = { "Bob", "John", "Joe" };

int database[ NUM_SUDENTS ][ NUM_GRADES ];
int i = 0;

srand( time( 0 ) );

// initialize student1
for ( i = 0; i < NUM_GRADES; i++ )
student1[ NUM_GRADES ] = rand() % 50 + 50;

// initialize database
for ( i = 1; i < NUM_GRADES; i++ ) {
database[ 0 ][ i ] = student1[ i ];
database[ 1 ][ i ] = student2[ i ];
database[ 2 ][ i ] = student3[ i ];

} // end for

printDatabase( database,  names );

for ( i = 0; i < NUM_SUDENTS; i++ ) {
cout << names[ i ] << "'s highest grade is: "
<< findHighest(database[i]) << endl           // This is line 44 in my program
<< names[ i ] << "'s lowest grade is: "
 << findLowest( database[ i ] ) << endl;

} // end for
} // end main

 // determine largest grade
int findHighest( int a[] )
 {

int highest =  a[ 0 ];

for ( int i = 1; i <= NUM_GRADES; i++ )
 if ( a[ i ] > highest )
 highest = a[ i ];

 return highest;

 } // end function findHighest

 // determine lowest grade
 int findLowest( int a[] )
 {
 int lowest = a[ 0 ];

 for ( int i = 1; i < NUM_GRADES; i++ )
 if ( a[ i ] < lowest )
 lowest = a[ i ];

return lowest;

 } // end lowestGrade

 // output data
void printDatabase( int a[][ NUM_GRADES ], char names[][ 20 ] )
{
cout << "Here is the grade database\n\n"
<< setw( 10 ) << "Name";

 for ( int n = 1; n <= NUM_GRADES; n++ )
cout << setw( 4 ) << n;

 cout << endl;

for ( int i = 0; i < NUM_SUDENTS; i++ ) {
cout << setw( 10 ) << names[ i ];

for ( int j = 0; j < NUM_GRADES; j++ )
cout << setw( 4 ) << a[ i, j ];

cout << endl;

} // end for

cout << endl;

} // end printDatabase
