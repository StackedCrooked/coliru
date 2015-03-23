//intarray.h

#ifndef __INTARRAY__
#define __INTARRAY__

#include <iostream>
#include <iterator>
using namespace std;

class Array_Error {
private:
     string err_msg;
public:
     Array_Error(const string &s): err_msg(s) {}
     string get_message() { return err_msg; }
};

class IntArray {
private:
     int *p; //pointer to int array data
     unsigned size; //Actual size of the array
     unsigned cap; //Number of elements array can store

public:
     typedef int * iterator;
     typedef const int * const_iterator;
     typedef reverse_iterator<iterator> rev_iterator;
     typedef reverse_iterator<const_iterator> const_rev_iterator;

     //Constructors
     IntArray(); //Default constructor
     IntArray(unsigned n);
     IntArray(unsigned n, int val);
     IntArray(const int *a, unsigned n);
     IntArray(const IntArray &a); //Copy constructor 
     IntArray(IntArray &&a); //Move constructor

     //Destructor
     ~IntArray();

     //Assignment operators
     IntArray &operator=(const IntArray &a);
     IntArray &operator=(IntArray &&a);  //Move assignment
     void assign(const int *a, unsigned n);

     //Subscript operators
     int &operator[](unsigned pos);
     const int &operator[](unsigned pos) const; //const version

     //Size functions
     unsigned length() const { return size; }
     bool empty() const { return size == 0; }
     void resize(unsigned sz, int val = 0);

     //Access functions
     iterator begin(); 
     const_iterator begin() const;
     iterator end();
     const_iterator end() const;
     rev_iterator rbegin();
     const_rev_iterator rbegin() const;
     rev_iterator rend();
     const_rev_iterator rend() const;
     int &front();
     const int &front() const;
     int &back();
     const int &back() const;

    //Memory functions
    unsigned capacity() const {return cap; } //returns the number of possible elements
    void reserve(unsigned n); //enlarges capacity to n
	void swap(IntArray &a); //swaps data with IntArray a

	//Insert and delete functions
	void insert(unsigned pos, int x); //insert x before 'pos'
	void insert(unsigned pos, unsigned n, int x); //n x's
	void push_back(int x); //add x to end of array
	void pop_back(); // Removes the last element in array
	void erase(unsigned pos); //remove the element at 'pos'
	void erase(unsigned first, unsigned last);
	void clear(); //erase all elements

};

//I/O functions
ostream& operator<<(ostream& out, const IntArray &a);
istream& operator>>(istream& in, IntArray &a);

//Relational operators
bool operator==(const IntArray &a1, const IntArray &a2);
bool operator!=(const IntArray &a1, const IntArray &a2);
bool operator<(const IntArray &a, const IntArray &b);
bool operator<=(const IntArray &a, const IntArray &b);
bool operator>(const IntArray &a, const IntArray &b);
bool operator>=(const IntArray &a, const IntArray &b);

//Global memberwise addition and multiplication operators

IntArray operator+(const IntArray &a, const IntArray &b);
IntArray operator*(const IntArray &a, const IntArray &b);

//Inline member functions of IntArray

//Default constructor, creates array of size 0
inline IntArray::IntArray(): p(0), size(0), cap(0) {}


//Creates array of n elements
inline IntArray::IntArray(unsigned n): p(new int[n]), size(0),cap(n)
{}

//Creates array of n elements all initialized to val
inline IntArray::IntArray(unsigned n, int val): p(new int[n]), size(n),cap(n)
{
     for(unsigned i = 0; i < n; i++) p[i] = val;
}

//Creates a copy of integer array a
inline IntArray::IntArray(const int *a, unsigned n):
                              p(new int[n]), size(n), cap(n)
{
     for(unsigned i = 0; i < n; i++) p[i] = a[i];
}

//Creates a copy of IntArray a
inline IntArray::IntArray(const IntArray &a):
                              p(new int[a.cap]), size(a.size), cap(a.cap)
{
     for(unsigned i = 0; i < size; i++) p[i] = a.p[i];
}

//Destructor
inline IntArray::~IntArray()
{
     delete [] p;
}

//Subscript operators
inline int &IntArray::operator[](unsigned pos)
{
     if (pos >= size)
		throw Array_Error("Out of range");
     return(p[pos]);
}

//The following works for const arrays
inline const int &IntArray::operator[](unsigned pos) const
{
     if (pos >= size)
		throw Array_Error("Out of range");
     return(p[pos]);
}
#endif

//The following code would be in a .cpp file intarray.cpp

#include <iomanip> //For output formatting
//#include "intarray.h"
using namespace std;

//Assignment operators
IntArray &IntArray::operator=(const IntArray &a)
{
     if (&a != this) { //Avoids self-assignment
          delete [] p;
          p = new int [a.cap];
          size = a.size;
          cap = a.cap;
          for(unsigned i = 0; i < size; i++) p[i] = a.p[i];
     }
     return *this;
}

//I/O functions
ostream& operator<<(ostream& out, const IntArray &a)
{
     unsigned size = a.length();

     for(unsigned i = 0; i < size; i++)
          out << setw(6) << a[i];
     return out;
}

istream& operator>>(istream& in, IntArray &a)
{
     unsigned size = a.length();

     for(unsigned i = 0; i < size; i++)
          in >> a[i];
     return in;
}

//Relational operators
bool operator==(const IntArray &a1, const IntArray &a2)
{
     bool equal = false;

     if (a1.capacity() == a2.capacity() && a1.length() == a2.length()) {
          unsigned size = a1.length();
          unsigned i;

          for(i = 0; i < size && a1[i] == a2[i]; i++)
                         ;
          if (i == size) equal = true;
     }
     return equal;
}

bool operator!=(const IntArray &a1, const IntArray &a2)
{
     return !(a1 == a2);
}

//(a) Accessor member functions

//Return pointer beginning of the array
IntArray::iterator IntArray::begin()
{
	return p;
}

//Const version of begin()
IntArray::const_iterator IntArray::begin() const
{
	return p;
}

IntArray::rev_iterator IntArray::rbegin()
{
	return rev_iterator(end());
}

IntArray::const_rev_iterator IntArray::rbegin() const
{
	return const_rev_iterator(end());

}

//Returns reference to first element
int &IntArray::front()
{
	return p[0];
}

//Const version of front()
const int &IntArray::front() const
{
	return p[0];
}

//Returns pointer to one past last element in array
IntArray::iterator IntArray::end()
{
	return p+size;
}

//Const version of end()
IntArray::const_iterator IntArray::end() const
{
	return p+size;
}

IntArray::rev_iterator IntArray::rend()
{
	return rev_iterator(begin());
}
/*
IntArray::const_rev_iterator rend() const
{
	return const_rev_iterator(begin());
}
*/

//Returns reference to last element in array
int &IntArray::back()
{
	return p[size-1];
}

//Const version of back()
const int &IntArray::back() const
{
	return p[size-1];
}

//(b) Assignment member function

//Copies array a to p
void IntArray::assign(const int *a, unsigned n)
{
	delete [] p;
	p = new int [n];
	size = n;
            cap = n;
	for(unsigned i = 0; i < size; i++) p[i] = a[i];

} 

//Move functions

//Move construtor
IntArray::IntArray(IntArray &&a): p(new int[a.cap]), size(a.size), cap(a.cap) 
{
     for(unsigned i = 0; i < size; i++) p[i] = a.p[i];
     delete [] a.p; 
     a.size = a.cap = 0;
}

//Move assignment
IntArray &IntArray::operator=(IntArray &&a)
{
     if (&a != this) { //Avoids self-assignment
          delete [] p;
          p = new int [a.cap];
          size = a.size;
          cap = a.cap;
          for(unsigned i = 0; i < size; i++) p[i] = a.p[i];
     }
     delete [] a.p; 
     a.size = a.cap = 0;

     return *this;
}

//(d) Size functions

//Enlarges the capacity to n
void IntArray::reserve(unsigned n)
{
	if (n > cap) {
		int *temp = new int[n];

		for(unsigned i = 0; i < size; i++)
			temp[i] = p[i];
		delete [] p;
		p = temp;
		cap = n;
	}
}

//Swaps contents with IntArray a
void IntArray::swap(IntArray &a)
{
	int *temp = a.p;
	int temp_size = a.size, temp_cap = a.cap;

	a.p = p;  p = temp;
	a.size = size;  size = temp_size;
	a.cap = cap;	cap = temp_cap;
}

//(e) Insert and delete member functions

//Insert x before position pos in array, array is resized
void IntArray::insert(unsigned pos, int x)
{
     if (pos >= size)
		throw Array_Error("Out of range");

	if (size == cap) { //Make array larger
		int *temp = new int[2*cap];
		unsigned i;

		//Copy first pos elements
		for(i = 0; i < pos; i++) temp[i] = p[i];

		//Insert x
		temp[i] = x;

		//Copy rest of array p
		for( ; i < size; i++) temp[i+1] = p[i];

		delete [] p;
		p = temp;
		size++;
		cap *= 2;
	}
	else { //Insert into current array
		//Shift array elements over
		for(unsigned int i = size; i > pos; i--)
			p[i] = p[i-1];
		p[pos] = x;
		size++;
	}
}

//Insert n copies of x before position pos
void IntArray::insert(unsigned pos, unsigned n, int x)
{
     	if (pos >= size)
		throw Array_Error("Out of range");
     	if (size+n > cap) {//Make array larger
		int new_size = cap+n > 2*cap 
						? cap+n: 2*cap;
		int *temp = new int[new_size];
		unsigned i,j;

		//Copy first pos elements
		for(i = 0; i < pos; i++) temp[i] = p[i];

		//Insert n x's
		for(j = 0; j < n; j++) temp[i+j] = x;

		//Copy rest of array p
		for( ; i < size; i++) temp[i+n] = p[i];

		delete [] p;
		p = temp;
		size += n;
		cap += n;
}
else { //Insert into current array
		//Move array elements over
        unsigned i;
		for(i = size+n; i > pos; i--) p[i] = p[i-n];
		for(i = 0; i < n; i++) p[pos+i] = x;
		size += n;
	}
}

//Insert element at end of array
void IntArray::push_back(int x)
{
	if(size < cap)
		p[size++] = x;
	else { //Resize array
		int *temp = new int[2*cap];

		//Copy elements
        unsigned i;
		for(i = 0; i < size; i++) temp[i] = p[i];

		//Insert x
		temp[i] = x;

		if (size > 0) delete [] p;
		p = temp;
 		size++;
		cap++;
	}
}

//Erase element at 'pos'
void IntArray::erase(unsigned pos)
{
     if (pos >= size)
		throw Array_Error("Out of range");

	for(unsigned i = pos; i < size; i++) p[i] = p[i+1];
	size--;
}

//Erase elements in the range, first upto (but not including) last
void IntArray::erase(unsigned first, unsigned last)
{
	if (first >= last)
		throw Array_Error("Invalid subscript interval");
     	if (last >= size)
		throw Array_Error("Out of range");

	unsigned diff = last-first;
	for(unsigned i = last; i < size; i++) p[i-diff] = p[i];
	size -= diff;
}

//Resize array, initialize new elements to val
void IntArray::resize(unsigned n, int val)
{
	if (n > cap) {
		int new_size = n > 2*cap ? n: 2*cap;
		int *temp = new int[new_size];

     		unsigned i;

		for(i = 0; i < size; i++) temp[i] = p[i];
		for( ; i < n; i++) temp[i] = val;

     		delete [] p;
     		p = temp;
		size = n;
		cap = new_size;
	}
	else {
		if (n > size) { //Array is increasing in size
     	     		for(unsigned i = size; i < n; i++) p[i] = val;
		}
		size = n;
	}
}

//Erase entire array
void IntArray::clear()
{
	size = 0;
}

//(f) Global comparison functions
//Less than operator using dictionary order
bool operator<(const IntArray &a, const IntArray &b)
{
	unsigned i = 0;

	while(i < a.length() && i < b.length() && a[i] < b[i]) i++;

	if (i == a.length() || i == b.length()) return true;
	else return false;
}

//Less than or equal operator
bool operator<=(const IntArray &a, const IntArray &b)
{
	unsigned i = 0;

	while(i < a.length() && i < b.length() && a[i] <= b[i]) i++;

	if (i == a.length() || i == b.length()) return true;
	else return false;
}

//Greater than operator using dictionary order
bool operator>(const IntArray &a, const IntArray &b)
{
	return !(a <= b);
}

//Greater than or equal operator using dictionary order
bool operator>=(const IntArray &a, const IntArray &b)
{
	return !(a < b);
}

//(g) Global memberwise addition and multiplication operators

//Add memberwise two arrays of same size
IntArray operator+(const IntArray &a, const IntArray &b)
{
	if (a.length() != b.length())
		throw Array_Error("Unequal array sizes");

	IntArray temp(a);
	unsigned n = a.length();

	for(unsigned i = 0; i < n; i++) temp[i] += b[i];

	return temp;
}

//Multiply memberwise two arrays of same size
IntArray operator*(const IntArray &a, const IntArray &b)
{
	if (a.length() != b.length())
		throw Array_Error("Unequal array sizes");

	IntArray temp(a);
	unsigned n = a.length();

	for(unsigned i = 0; i < n; i++) temp[i] *= b[i];

	return temp;
}

//Test program
#include <iostream>
#include <utility>
//#include "intarray.h"
using namespace std;

int main()
{
	IntArray a;
	int b[5] = {7,10,3,2,13};

	//Check assign function
	a.assign(b,5);
	cout << "Assignment check\n";
	cout << a << endl;

	//Check move functions
	IntArray temp(a);
	
	cout << "Source before move ctor" << endl;
	cout << temp << endl;

	IntArray c(move(temp)); //Calls move ctor

	cout << "Source after move ctor" << endl;
	cout << temp << endl;

	cout << "Destination after move ctor" << endl;
	cout << c << endl;

	temp = move(c);  //Move assignment

	cout << "Source before move assign" << endl;
	cout << c << endl;

	cout << "Source after move assign" << endl;
	cout << temp << endl;

	//Check front and back functions
	cout << "\nFirst element = " << a.front() << endl;
	cout << "Last element = " << a.back() << endl;

	//Check begin and end functions
	cout << "\nBegin and end checks\n";
	IntArray::iterator p;
	for(p = a.begin(); p != a.end(); p++) cout << *p << '\t';
	cout << endl;

//Check reverse begin and end functions
	cout << "\nBegin and end checks\n";
	IntArray::rev_iterator q;
	for(q = a.rbegin(); q != a.rend(); p++) cout << *q << '\t';
	cout << endl;


	//Check erase and clear functions
	cout << "Original array: " << a << endl;

	a.erase(1); //Erase element a[1]
	cout << "Array after element [1] erased: " << a << endl;

	a.erase(0,2); //Erase elements a[0],a[1],a[2]
	cout << "Array after elements [0],[1],[2] erased: " 
		<< a << endl;

	a.clear(); //Array empty
	cout << "Array after being emptied: " << a << endl;

	//Check push_back and insert functions
	a.push_back(2); a.push_back(4); a.push_back(6);
	cout << "\nNew Array: " << a << endl;

	a.insert(1,5); //Insert a 5 at position 1
	cout << "\nArray after 5 inserted: " << a << endl;

	a.insert(2,3,7); //Insert 3 7's at position 2
	cout << "\nArray after 7\'s inserted: " << a << endl;

	//Check relational operators
	IntArray r[3];
	r[0].push_back(3); r[0].push_back(5); r[0].push_back(7);
	r[1].push_back(3); r[1].push_back(5); r[1].push_back(6);
	r[2].push_back(4); r[2].push_back(5); r[2].push_back(6);

	cout << "\nArrays before sorting\n";
	cout << "Array 1: " << r[0] << endl;
	cout << "Array 2: " << r[1] << endl;
	cout << "Array 3: " << r[2] << endl;

	if (r[0] > r[1]) swap(r[0],r[1]);
	if (r[1] > r[2]) swap(r[1],r[2]);
	if (r[0] > r[1]) swap(r[0],r[1]);

	cout << "\nArrays after sorting\n";
	cout << "Array 1: " << r[0] << endl;
	cout << "Array 2: " << r[1] << endl;
	cout << "Array 3: " << r[2] << endl;

	//Check add and multiply operators
	r[0] = r[1]+r[2];
	cout << "Array 2 + Array 3 " << r[0] << endl;

	r[0] = r[1]*r[2];
	cout << "Array 2 * Array 3 " << r[0] << endl;
	return 0;
}

