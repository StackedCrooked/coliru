#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct Person
{
public:
    friend std::istream& operator>>(std::istream& is, Person& p); // for input
	friend std::ostream& operator<<(std::ostream& os, const Person& p); // for output
private:
	std::string first, last;
	int a, b, c;
};

std::istream& operator>>(std::istream& is, Person& p) //Extractor
{
	char comma;
	is >> p.first >> comma >> p.last >> comma;
	is >> p.a >> comma >> p.b >> comma >> p.c;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	int pPower = p.a + p.b + 2 * p.c;
	return os << p.first << "," << p.last << " ----- " << pPower << endl;
}

int main()
{
	//Variables
	int pPower; //Holds Player Power
	string fName, lName;

	//File Variables
	ifstream inFile;
	ofstream outFile;

	//Open Files
	outFile.open("C:\\quiz1output.txt");
	inFile.open("C:\\quiz1input.txt");

	if (!inFile.fail()) //Checks To Make Sure File Loads
	{
		std::vector<Person> v;


		for (int i = 0; i < 1000; i++)
		{
			Person p;
			if (inFile >> p)
			{
				v.push_back(p);
			}
		}

		for (int i = 0; i < 1000; ++i)
		{
			outFile << v[i];
		}

		inFile.close();
		outFile.close();
	}
	else //Throws Error If File Isn't Present
	{
		cout << "ERROR READING FILE!" << endl;
		system("pause");
		return 0;
	}

	system("pause");
	return 0;
}