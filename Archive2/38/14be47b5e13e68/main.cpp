/*
    simple "Programming: Principles and Practice using C++" course header to
	be used for the first few weeks.
	It provides the most common standard headers (in the global namespace)
	and minimal exception/error support.

	Students: please don't try to understand the details of headers just yet.
	All will be explained. This header is primarily used so that you don't have
	to understand every concept all at once.

	Revised April 25, 2010: simple_error() added
*/

#ifndef H112
#define H112 201004L

#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<stdexcept>
#include<iomanip>

//------------------------------------------------------------------------------

#ifdef _MSC_VER
#include <hash_map>
using stdext::hash_map;
#else
#include <ext/hash_map>
using __gnu_cxx::hash_map;

namespace __gnu_cxx {

    template<> struct hash<std::string>
    {
        size_t operator()(const std::string& s) const
        {
            return hash<char*>()(s.c_str());
        }
    };

} // of namespace __gnu_cxx
#endif

//------------------------------------------------------------------------------

#define unordered_map hash_map

//------------------------------------------------------------------------------

typedef long Unicode;

//------------------------------------------------------------------------------

using namespace std;

template<class T> string to_string(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}

struct Range_error : out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};


// trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {
	typedef typename std::vector<T>::size_type size_type;

	Vector() { }
	explicit Vector(size_type n) :std::vector<T>(n) {}
	Vector(size_type n, const T& v) :std::vector<T>(n,v) {}
	template <class I>
	Vector(I first, I last) :std::vector<T>(first,last) {}

	T& operator[](unsigned int i) // rather than return at(i);
	{
		if (i<0||this->size()<=i) throw Range_error(i);
		return std::vector<T>::operator[](i);
	}
	const T& operator[](unsigned int i) const
	{
		if (i<0||this->size()<=i) throw Range_error(i);
		return std::vector<T>::operator[](i);
	}
};

// disgusting macro hack to get a range checked vector:
#define vector Vector

// trivially range-checked string (no iterator checking):
struct String : std::string {
	
	String() { }
	String(const char* p) :std::string(p) {}
	String(const string& s) :std::string(s) {}
	template<class S> String(S s) :std::string(s) {}
	String(int sz, char val) :std::string(sz,val) {}
	template<class Iter> String(Iter p1, Iter p2) : std::string(p1,p2) { }

	char& operator[](unsigned int i) // rather than return at(i);
	{
		if (i<0||size()<=i) throw Range_error(i);
		return std::string::operator[](i);
	}

	const char& operator[](unsigned int i) const
	{
		if (i<0||size()<=i) throw Range_error(i);
		return std::string::operator[](i);
	}
};

#ifndef _MSC_VER
namespace __gnu_cxx {

    template<> struct hash<String>
    {
        size_t operator()(const String& s) const
        {
            return hash<std::string>()(s);
        }
    };

} // of namespace __gnu_cxx
#endif


struct Exit : runtime_error {
	Exit(): runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
	error(s+s2);
}

inline void error(const string& s, int i)
{
	ostringstream os;
	os << s <<": " << i;
	error(os.str());
}

#if _MSC_VER<1500
	// disgusting macro hack to get a range checked string:
	#define string String
	// MS C++ 9.0 have a built-in assert for string range check
	// and uses "std::string" in several places so that macro substitution fails
#endif

template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
	void* addr = &i;	// get the address of the first byte
						// of memory used to store the object
	return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

inline void keep_window_open(string s)
{
	if (s=="") return;
	cin.clear();
	cin.ignore(120,'\n');
	for (;;) {
		cout << "Please enter " << s << " to exit\n";
		string ss;
		while (cin >> ss && ss!=s)
			cout << "Please enter " << s << " to exit\n";
		return;
	}
}



// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(string s)	// write ``error: s�� and exit program
{
	cerr << "error: " << s << '\n';
	keep_window_open();		// for some Windows environments
	exit(1);
}

// make std::min() and std::max() accessible:
#undef min
#undef max

inline ios_base& general(ios_base& b)	// to augment fixed and scientific
{
	b.setf(ios_base::fmtflags(0),ios_base::floatfield);
	return b;
}

// run-time checked narrowing cast (type conversion):
template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r)!=a) error(string("info loss"));
	return r;
}


inline int randint(int max) { return rand()%max; }

inline int randint(int min, int max) { return randint(max-min)+min; }

inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

#endif


// Bjarne Stroustrup 3/26/2009
// Chapter 4 Exercise 7
//#include "../std_lib_facilities.h"
// note that different compilers/SDEs keep header files in different places
// so that you may have to use "../std_lib_facilities.h" or "../../std_lib_facilities.h"
// the ../ notation means "look one directly/folder up from the current directory/folder"

// How do you exit?

/*
the problem here is to handle numbers written out using letters as well as numbers written using digits, e.g.
    2 + two
    two + 2
    two + five
    2 + 5
The basic idea for a solution is to try to read integers (as in exercise 5)
and if that doesn't work (the input operation fails) try reading a string
and see if that string represents a number (e.g. "nine").

You will note that a space after a number expressed as a letter is essential:
    two+ 3
will not work because the string read will also read the +

The solution uses two functions (in addition to main():
    initialize_numbers() to initialize the vector of number string representations
    get_number() to read a number that is either a string or a sequence of digits
*/

vector<string> numbers; // representation of numbers as strings
                    // numbers[i] is the string representation for i
                    // for numbers[0] to numbers[numbers.size()-1]

void initialize_numbers()
{
    numbers.push_back("zero");
    numbers.push_back("one");
    numbers.push_back("two");
    numbers.push_back("three");
    numbers.push_back("four");
    numbers.push_back("five");
    numbers.push_back("six");
    numbers.push_back("seven");
    numbers.push_back("eight");
    numbers.push_back("nine");
    numbers.push_back("ten");   // why not? :-)
}

int get_number()
/*
    An apology: To use cin again after a failed read, you need to use a function call "cin.clear();" to "clear" it.
That isn't explained in the book until chapter 10. Sorry.

Solutions that do not use this technique can get very complicated.
*/
{
    const int not_a_symbol = numbers.size();    // not_a_symbol is a value that does not  correspond
                                                // to a string in the numbers vector
    int val = not_a_symbol;
    if (cin>>val) return val; // try to read an integer composed of digits

    cin.clear();    // clear string after failed attempt to read an integer
    string s;
    cin>>s;
    for (int i=0; i<numbers.size(); ++i)    // see if the string is in numbers
        if (numbers[i]==s) val = i;
    if (val==not_a_symbol) error("unexpected number string: ",s);
    return val;
}

int main()
try
{
    initialize_numbers();

    cout<< "please enter two floating-point values separated by an operator\n The operator can be + - * / % : ";

    while (true) {  // "forever"; that is until we give an unacceptable input or make a computations error
        int val1 = get_number();

        char op = 0;
        cin>>op; // get the operator

        int val2 = get_number();

        string oper;    // text appropriate for an operator
        double result;

        switch (op) {
        case '+':
            oper = "sum of ";
            result = val1+val2;
            break;
        case '-':
            oper = "difference between ";
            result = val1-val2;
            break;
        case '*':
            oper = "product of ";
            result = val1*val2;
            break;
        case '/':
            oper = "ratio of ";
            if (val2==0) error("trying to divide by zero");
            result = val1/val2;
            break;
        case '%':
            oper = "remainder of ";
            if (val2==0) error("trying to divide by zero (%)");
            result = val1%val2;
            break;
        default:
            error("bad operator");
        }
        cout << oper << val1 << " and " << val2 << " is " << result << '\n';
        cout << "Try again: ";
    }
}
catch (runtime_error e) {   // this code is to produce error messages; it will be described in Chapter 5
    cout << e.what() << '\n';
    keep_window_open("~");  // For some Windows(tm) setups
}
catch (...) {   // this code is to produce error messages; it will be described in     5
    cout << "exiting\n";
    keep_window_open("~");  // For some Windows(tm) setups
}