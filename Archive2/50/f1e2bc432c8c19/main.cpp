#include <fstream> //generic class template that implements input/output operations on file streams https://en.wikipedia.org/wiki/Input/output_(C%2B%2B)

using namespace std; //i do not use it https://en.wikipedia.org/wiki/Namespace#In_programming_languages
 
int main() //main function https://en.wikipedia.org/wiki/C%2B%2B
{
    ofstream OurFile; //it interfaces a file-based streambuffer http://en.cppreference.com/w/cpp/io/basic_ofstream
	OurFile.open("hello.txt"); //opens a file and associates it with the stream http://en.cppreference.com/w/cpp/io/basic_ofstream/open
	OurFile << "Hello World!"; //inserts formatted data http://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt
	OurFile.close(); //closes the associated file http://en.cppreference.com/w/cpp/io/basic_ofstream/close

	return 0;
}