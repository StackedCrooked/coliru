#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <fstream>
#include <iterator>

template<typename T>
void printValues(T aContainer)
{
    std::copy(aContainer.begin(), aContainer.end(), std::ostream_iterator<decltype(*aContainer.begin())>(std::cout, " "));
	std::cout << std::endl << std::endl;
}

//This is for Exercise 3
struct IsEvenNumber
{
	bool operator()(int num) const
	{
		bool ret = false;
		if (num % 2 == 0)
			ret = true;

		return ret;
	}

	typedef int argument_type;
};

//This is for Exercise 8
class CFileParser
{
private:
	std::vector<std::string> _wordsInFile;

	bool stlWordExist();
	int countWordsWithMoreThan3Chars();
	std::vector<std::string> getStringsWithLessThanFourChars();

public:
	CFileParser() {}
	CFileParser(std::string filename) { parseFile(filename); }
	void parseFile(std::string filename);
	void printAll();
};

//Exercise 8
bool CFileParser::stlWordExist()
{
	bool result = false;

	std::vector<std::string>::iterator it = std::find(_wordsInFile.begin(), _wordsInFile.end(), "STL");
	if (it != _wordsInFile.end())
		result = true;

	return result;
}

//Exercise 8
int CFileParser::countWordsWithMoreThan3Chars()
{
	return std::count_if(_wordsInFile.begin(), _wordsInFile.end(), [](std::string str)->bool{ return str.size() > 3; });
}

//Exercise 8
std::vector<std::string> CFileParser::getStringsWithLessThanFourChars()
{
	std::vector<std::string> stringsLessThanFourChars = _wordsInFile;
	std::vector<std::string>::iterator it = std::remove_if(stringsLessThanFourChars.begin(), stringsLessThanFourChars.end(), [](std::string str)->bool{return str.size() > 3; });
	stringsLessThanFourChars.erase(it, stringsLessThanFourChars.end());
	return stringsLessThanFourChars;
}

//Exercise 8
void CFileParser::parseFile(std::string filename)
{
	std::fstream file;
	std::string word;

	file.open(filename, std::ifstream::in);
	if (!file.is_open()) return;

	while (file >> word)
		_wordsInFile.push_back(word);
        
    file.close();
}

//Exercise 8
void CFileParser::printAll()
{
	std::cout << "Exercise 8" << std::endl;
	std::cout << "Number of Words: " << _wordsInFile.size() << std::endl;
	std::cout << "Is there an STL word?: " << stlWordExist() << std::endl;
	std::cout << "Last word is: " << _wordsInFile.back() << std::endl;
	std::cout << "Middle word is: " << _wordsInFile.at(((int)_wordsInFile.size() / 2)) << std::endl;
	std::cout << "Number of words with more than 3 characters: " << countWordsWithMoreThan3Chars() << std::endl;
	std::cout << "List of words with less than 4 characters: " << std::endl;
	printValues(getStringsWithLessThanFourChars());
    printValues(_wordsInFile);
}

//Common function
std::vector<int> populateVector()
{
	std::vector<int> exercise;

	exercise.push_back(1);
	exercise.push_back(2);
	exercise.push_back(3);
	exercise.push_back(2);
	exercise.push_back(1);
	exercise.push_back(4);
	exercise.push_back(5);

	return exercise;
}

//Exercise 1
void transformIntToStringVector()
{
	std::cout << "Exercise 1" << std::endl;
	std::vector<int> vectInt = populateVector();

	//std::vector<std::string> stringVector(vectInt.size());
	//std::transform(vectInt.begin(), vectInt.end(), stringVector.begin(), static_cast<std::string(*)(int)>(std::to_string));

	std::vector<std::string> stringVector2;
	std::transform(vectInt.begin(), vectInt.end(), std::back_inserter(stringVector2), static_cast<std::string(*)(int)>(std::to_string));
	printValues(vectInt);
}

//Exercise 2
void printStrUpper(std::string str)
{
	std::cout << "Exercise 2" << std::endl;

	std::for_each(str.begin(), str.end(), [](char& value) { value = toupper(value); });
	std::cout << str << std::endl << std::endl;
}

//Exercise 3
void printEvenValuesOfVectorInt(std::vector<int> vectInt)
{
	std::cout << "Exercise 3" << std::endl;
	std::cout << std::count_if(vectInt.begin(), vectInt.end(), IsEvenNumber());
	std::cout << std::endl << std::endl;
}

//Exercise 4
void printMinMax(std::vector<int> vectInt)
{
	std::cout << "Exercise 4" << std::endl;
	std::cout << "Minimum Value is: " << *std::min_element(vectInt.begin(), vectInt.end());
	std::cout << std::endl << std::endl;

	std::cout << "Exercise 4" << std::endl;
	std::cout << "Maximum Value is: " << *std::max_element(vectInt.begin(), vectInt.end());
	std::cout << std::endl << std::endl;
}

//Exercise 5
void printOddValues(std::vector<int> vectInt)
{
	std::cout << "Exercise 5" << std::endl;

	vectInt.erase(std::remove_if(vectInt.begin(), vectInt.end(), std::not1(IsEvenNumber())), vectInt.end());
	printValues(vectInt);
}

//Exercise 7
void printUniqueValues(std::vector<int> vectInt)
{
	std::cout << "Exercise 6/7: " << std::endl;

	std::set<int> setInt(vectInt.begin(), vectInt.end());
	printValues(setInt);
}

int main()
{
	//Exercise 1
	transformIntToStringVector();

	//Exercise 2
	printStrUpper("exercise");

	//Exercise 3
	printEvenValuesOfVectorInt(populateVector());

	//Exercise 4
	printMinMax(populateVector());

	//Exercise 5
	printOddValues(populateVector());

	//Exercise 6/7
	printUniqueValues(populateVector());

	//Exercise 8
	CFileParser parser("file.txt");
	parser.printAll();

	return 0;
}

