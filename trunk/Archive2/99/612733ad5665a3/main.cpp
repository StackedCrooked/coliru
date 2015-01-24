//*********************************************************************
//*                                                                   *
//* Program Name: PROG0 - Show Hello World! and Manage integer ranges *
//* Author:       Straja Rosic                                        *
//* Installation: Pensacola Christian College, Pensacola, Florida     *
//* Course:       CS246, Object-Oriented Programming and Design       *
//* Date Written: January 27, 2015                                    *
//*                                                                   *
//*********************************************************************

//*********************************************************************
//*                                                                   *
//* This program prints the message "Hello World!", and then manages  *
//* integer ranges, which consist of minimum and maximum range values,*
//* and the inclusive sum of all integers in the range.               *
//*                                                                   *
//*********************************************************************

#include <iostream>
using namespace std;

//*********************************************************************
//*                         Symbolic Constants                        *
//*********************************************************************
#define COURSE_NUMBER    "CS246" // PCC assigned course number
#define PRESET_RANGE_MAX 1000    // Program preset range maximum value
#define PRESET_RANGE_MIN 1       // Program preset range minimum value
#define PROGRAM_NUMBER   0       // Teacher assigned program number

//*********************************************************************
//*                          Class Definition                         *
//*********************************************************************
// A range of integers
class integer_range
{
   int maximum, // Highest value in the integer range
       minimum, // Lowest value in the integer range 
	   sum;     // Inclusive sum of the integers in the range
public:
   // Constructor, create an integer range
		integer_range (int lower, int upper);

   // Destructor, delete an integer range
		~integer_range();

   // Get the inclusive sum of all integers in a integer range
		int get_range_sum () {return sum;}

   // Show an integer range and its sum
   void show_range    ();
};

//*********************************************************************
//*                      Create an integer range                      * 
//*********************************************************************
integer_range::integer_range(int lower, int upper)
{
   int range_counter; // Loops through every value in the range

   minimum = lower;
   maximum = upper;
   sum     = 0;

   for (range_counter=minimum; range_counter<=maximum; range_counter++)
      sum += range_counter;

   // (Constructors do not usually print what they are doing like this)
   cout << "\n\nConstructor creating an integer range from:";
   cout << "\n     "           << minimum
	    << " to "              << maximum 
		<< " with the sum of " << sum;
   cout << "\nConstructor finished - the integer range is created";
}

//*********************************************************************
//*                      Delete an integer range                      *
//*********************************************************************
integer_range::~integer_range()
{
	// (Destructors do not usually print what they are doing like this)
	cout << "\nDestructor executing for an integer range from:";
	cout << "\n     "           << minimum
		 << " to "              << maximum
		 << " with the sum of " << sum;
	cout << "\nDestructor finished - the integer range is deleted";
	cout << "\n";
}

//*********************************************************************
//*                 Show an integer range and its sum                 *
//*********************************************************************
void integer_range::show_range()
{
   cout << "\nThe integer range is " << minimum
	    << " to "                    << maximum
		<< " with the sum of "       << sum;
   return;
}

//*********************************************************************
//*                        Function Prototypes                        *
//*********************************************************************
void get_range (int *p_range_min, int *p_range_max);
   // Get an integer range

//*********************************************************************
//*                            Main Function                          *
//*********************************************************************
int main()
{
   int user_range_max, // Highest value of the user integer range
	   user_range_min; // Lowest value of the user integer range

   // Print the program heading and the required (by tradition),
   // my first C++ program, "Hello World!" message 
   cout << "\n\n\n\n\n\n        Course " << COURSE_NUMBER
	    << " - Program "                 << PROGRAM_NUMBER;
   cout << "\n      This is my first C++ program";
   cout << "\n              Hello World!";

   // Get an integer range
   cout << "\n\n";
   get_range(&user_range_min, &user_range_max);
   
   // Create an integer range with program preset range limits
   //    and an integer range with  user entered  range limits 
   integer_range preset_range (PRESET_RANGE_MIN, PRESET_RANGE_MAX);
   integer_range user_range   (user_range_min,   user_range_max);

   // Show the values of the integer ranges
   cout << "\n";
   preset_range.show_range();
     user_range.show_range();

   // Get and print the integer range sums 
   cout << "\n\nFrom main(), the program preset integer range sum is "
									    << preset_range.get_range_sum();
   cout << "  \nFrom main(), the  user entered  integer range sum is "
	                                    << user_range.get_range_sum();

   // Say goodbye and terminate the program
   cout << "\n\nThanks for running your first C++ program ;)";
   cout << "\n\n\n\n\n\n";
   return 0;
}

//*********************************************************************
//*                        Get an integer range                       *
//*********************************************************************
void get_range(int *p_range_min, int *p_range_max)
{
   cout << "\nEnter the lower value of an integer range: ";
   cin  >> *p_range_min;
   cout <<   "Enter the upper value of an integer range: ";
   cin  >> *p_range_max;

   return;
}