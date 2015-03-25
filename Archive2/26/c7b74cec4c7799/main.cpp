#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
  friend ostream& operator<< (ostream& , const MyString& );    	//check
  friend istream& operator>> (istream& , MyString& );
  friend istream& getline (istream& , MyString& , char delim);

  friend MyString operator+ (const MyString& , const MyString& );

  friend bool operator< (const MyString& , const MyString& );	//check
  friend bool operator> (const MyString& , const MyString& );	//check
  friend bool operator<=(const MyString& , const MyString& );	//check
  friend bool operator>=(const MyString& , const MyString& );	//check
  friend bool operator==(const MyString& , const MyString& );	//check
  friend bool operator!=(const MyString& , const MyString& );	//check

public:
  MyString();				// empty string
  MyString(const char* );		// conversion from c-string
  MyString(int );			// conversion from int
  ~MyString();				// destructor
  MyString(const MyString& );		// copy constructor
  MyString& operator=(const MyString& );   // assignment operator

  MyString& operator+=(const MyString& );  // concatenation/assignment

  // bracket operators to access char positions
  char& operator[] (unsigned int index);
  const char& operator[] (unsigned int index) const;

  // insert s into the string at position "index"
  MyString& insert(unsigned int index, const MyString& s);

  // find index of the first occurrence of s inside the string
  //  return the index, or -1 if not found
  int indexOf(const MyString& s) const;
  
  int getLength() const;		// return string length
  const char* getCString() const;	// return c-string equiv

  MyString substring(unsigned int , unsigned int ) const;
  MyString substring(unsigned int ) const;

private:
  void Grow();
  char* str;
  int currentSize, maxSize;


};

MyString::MyString()
{
	maxSize = 10;
	currentSize = 0;
	str = new char[maxSize];
}

MyString::MyString(const char* a)
	: currentSize(strlen(a)), maxSize(currentSize + 1)
{
	str = new char[maxSize];
	strcpy(str, a);
}

MyString::MyString(int a)
{
	currentSize = 0;
	int count = 0;
	char ch;

	int i_digit = a,
		numOfDigits = 0;

	//counting the spaces
	while (i_digit > 0)
	{
		numOfDigits++;
		i_digit = i_digit / 10;
	}

	currentSize = numOfDigits;
	maxSize = numOfDigits + 1;
	//new dynamic string
	str = new char[maxSize];

	//Putting the ints into a string
	do {
		int digit = a % 10;
		a /= 10;
		ch = digit + '0';

		count++;
		str[numOfDigits - count] = ch;

	} while (a > 0);
	// Here?

}

MyString::MyString(const MyString& m)
{
	maxSize = m.maxSize;
	currentSize = m.currentSize;
	str = new char[m.maxSize + 1];

	strcpy(str, m.str);
}

MyString& MyString::operator=(const MyString& m)
{
	if (this != &m)
	{

		maxSize = m.maxSize;
		currentSize = m.currentSize;
		str = new char[m.maxSize + 1];

		for (int i = 0; i < currentSize; i++)
			str[i] = m.str[i];
	}
	str[currentSize] = '\0';
	return *this;
}

ostream& operator<< (ostream& s, const MyString& m)
{
	for (int i = 0; i < m.currentSize; i++)
		s << m.str[i];
	return s;
}

istream& operator>> (istream& os, MyString& m)
{
	char* buff = 0; // nullptr if C++11
	os >> buff;
	m = MyString(buff);
    return os;
    /*
	os >> m.str;

	for (int i = 0; i < strlen(m.str); i++)
		m.currentSize++;

	if (m.currentSize > m.maxSize)
		m.Grow();
	return os;
	*/

}


istream& getline(istream& is, MyString& m, char delim)
{
	is.getline(m.str, 25, delim);
	m.Grow();
	return is;
}


bool operator< (const MyString& str1, const MyString& str2)
{
	int result = strcmp(str1.str, str2.str);
	if (result == -1 && str1.str != str2.str)	return true;
	else				return false;
}

bool operator> (const MyString& str1, const MyString& str2)
{
	int result = strcmp(str1.str, str2.str);
	if (result == 1 && str1.str != str2.str)
		return true;
	else
		return false;
}

bool operator<= (const MyString& str1, const MyString& str2)
{
	int result = strcmp(str1.str, str2.str);
	if (result == -1 || result == 0)
		return true;
	else
		return false;
}

bool operator>= (const MyString& str1, const MyString& str2)
{
	int result = strcmp(str1.str, str2.str);
	if (result == 1 || result == 0)
		return true;
	else
		return false;
}

bool operator!= (const MyString& str1, const MyString& str2)
{
	int result = strcmp(str1.str, str2.str);
	if (result == 0)	{ return false; }
	else                { return true; }

}

bool operator== (const MyString& str1, const MyString& str2)
{
	int result = strcmp(str1.str, str2.str);
	if (result != 0)	{ return false; }
	else                { return true; }

}

MyString operator+ (const MyString& str2, const MyString& str3)
{
	MyString a;
	a.currentSize = str2.currentSize + str3.currentSize;
	a.maxSize = a.currentSize + 1;
	a = new char[a.maxSize + 1];
	a.str = strcpy(a.str, str2.str);
	strcat(a.str, str3.str);

	return a;

}

MyString& MyString::operator+= (const MyString& appended_str)
{
	currentSize = currentSize + strlen(appended_str.str);
	if (maxSize < currentSize)
		maxSize = currentSize + 1;
	char *oldString = new char[maxSize + 1];
	strcpy(oldString, str);
	delete[] str;
	str = oldString;

	str = strcat(str, appended_str.str);

	return *this;
}

char& MyString::operator[](unsigned int index)
{
	int myIndex = index * 1;
	if (myIndex > currentSize)
	{
		maxSize = myIndex + 1;
		Grow();
		while (currentSize < myIndex)
		{
			str[currentSize] = ' ';
			currentSize++;
		}

		str[myIndex + 1] = '\0';


	}


	return str[index];
}

const char& MyString::operator[] (unsigned int index) const
{
	int myIndex = index * 1;
	if (myIndex > maxSize)
		str[myIndex] = '\0';

	return str[myIndex];
}

int MyString::getLength()const
{
	return currentSize;
}

const char* MyString::getCString() const
{

	return str;
}



void MyString::Grow()
{
	maxSize = currentSize + 10;			// Determine a new size.
	MyString newString = new char[maxSize];		// Allocate a new array.

	newString.currentSize = currentSize;
	for (int i = 0; i < currentSize; i++)	// Copy each entry into
		newString[i] = str[i];		// the new array.

	delete[] str;			// Remove the old array
	str = newString.str;
}




MyString::~MyString(){ delete[] str; }   //adios!


int main()
{
   MyString s1;
   MyString s2("Hello, World");
   MyString s3 = "Welcome to Florida, have a nice day";
   MyString s4 = 12345;

   cout << "s1 = " << s1 << '\n';
   cout << "s2 = " << s2 << '\n';
   cout << "s3 = " << s3 << '\n';
   cout << "s4 = " << s4 << '\n';
   cout << '\n';

   cout << "Making the calls:\n"
        << "\tcin >> s1\n"
        << "\tgetline(cin, s2, ',')\n"
        << "\tgetline(cin, s3)\n";
   cout << "Enter some sentences: ";
  
   cin >> s1;
  /* getline(cin,s2,',');
   getline(cin,s3);

   cout << "\nNew string values:\n";

   cout << "s1 = " << s1 << '\n';
   cout << "s2 = " << s2 << '\n';
   cout << "s3 = " << s3 << '\n';
   cout << "---------------------------\n";*/
 
 //----------------------------------

  /* s1 = "Dog";
   s2 = "Food";
   MyString result = s1 + s2;
   cout << "result = " << result << '\n';

   s1 += s2;
   cout << "s1 = " << s1 << endl;

   const MyString s5 = "The concatenation of the catapult is a catamaran";*/
 //  cout << "s5 = " << s5 << endl;
 //  cout << "s5.indexOf(\"cat\") returns " << s5.indexOf("cat") << '\n';
 //  cout << "s5.indexOf(\"dog\") returns " << s5.indexOf("dog") << '\n';

  /* cout << "s5.getLength() = " << s5.getLength() << '\n';

   cout << "s5[4] = " << s5[4] << '\n';
   cout << "s5[10] = " << s5[10] << '\n';
   cout << "s5[15] = " << s5[15] << '\n';*/
   //cout << "s5[52] = ascii " << static_cast<int>(s5[52]) << '\n';

 //  cout << "s5.substring(10,16) = " << s5.substring(10,16) << '\n';
 //  cout << "s5.substring(23) = " << s5.substring(23) << '\n';

 //  cout << "-----------------------------\n";

 //  MyString words = "Greetings, Earthling";

 //  cout << "words = " << words << '\n';
 //  cout << "words.getLength() = " << words.getLength() << '\n';
 //  words[0] = 'K';
 //  words[4] = 'p';
 //  words[16] = 'z';

 //  cout << "words = " << words << '\n';

 //  words[25] = 'Q';
 //  cout << "words = " << words << '\n';

 //  words.insert(11, "Insane ");
 //  cout << "words = " << words << '\n';

 //  cout << "-----------------------------\n";

 //  MyString x = "apple", y = "apply";
 //  cout << "x = " << x << '\n';
 //  cout << "y = " << y << '\n';

 //  if (x < y)		cout << "x < y is true\n";
 //  if (x > y)		cout << "x > y is true\n";
 //  if (x <= y)		cout << "x <= y is true\n";
 //  if (x >= y)		cout << "x >= y is true\n";
 //  if (x == y)		cout << "x == y is true\n";
 //  if (x != y)		cout << "x != y is true\n";



}
