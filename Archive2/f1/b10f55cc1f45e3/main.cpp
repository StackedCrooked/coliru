#include<string>
#include<fstream>
#include<iostream>
#include<algorithm>
#include <cstdlib>
#include <ctime>
using namespace std ;
int main (){

    srand(time(0));
	ofstream out;
	out.open("questions.txt");

	string fname, lname, name;

	cout << "Please enter your first name and last name separated by a space." << endl;
	cin >> fname >> lname;


	out << "Answer each of the following questions. Each question is worth\n" <<
		 "0.25 marks.\n\n" <<
		 "a) Create a frequency table for the text shown below.\n\n" <<
		 "b) Create a fixed length code for this text using the minimum number\n" <<
		 "   of bits possible.\n\n" <<
		 "c) Use Huffman's algorithm to create a variable length code.\n\n" <<
		 "d) How would the last line in the text be represented using the\n" <<
		 "   Huffman code created in the previous step?\n\n" <<
		 "e) Assume that the text was originally encoded using the fixed length\n" <<
		 "   code created in part b and then compressed using the variable\n" <<
		 "   length code created in part c. Compute the compression ratio.\n\n" <<
		 "f) Assume that the text is compressed using Run Length Encoding,\n" <<
		 "   would the compression ratio be more or less than 1?\n\n" <<
		 "g) Sometimes it is better to use words with RLE instead of\n" <<
		 "   individual characters? Which word length is suitable for\n" <<
		 "   compressing this text?\n\n" <<
		 "h) Compute the compression ratio for the word-based RLE\n\n";

		 out << endl << endl;

	int i=0;
	name = fname;
	while (name.length() < 16) {
			name += lname[i%lname.length()];
			i++;
	}

	transform(name.begin(), name.end(), name.begin(), ::tolower);

	int c=0;
	int lines = 3 + rand()%4;
	for (int i = name.length(); i > 0; i /= 2) {
		for (int k = 0; k < lines; k++) {
			for (int j = 0; j < 80; j += name.length()) {
				out << name;
			}
			c++;
			out << endl;
		}
		name = name.substr(0, name.length()/2);
		out << endl;
	}

	out << "\nThere are " << c << " lines in this text and 80 characters per line";
	cout << "Your HW has been generated. Check the file \"questions.txt\"" << endl;
	cout << "Consider this HW as a puzzel and you will enjoy it :)";
	return 0;
}
