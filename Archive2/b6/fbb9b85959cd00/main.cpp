#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<string>

bool isGreaterThan3(std::string str)
{
    return (str.size() > 3);
}

bool isLessThan4(std::string str1)
{
    return (str1.size() < 4);
}

int main()
{
    std::vector<std::string> strVector;
	std::string line;
	//1. Get all words in "file.txt" and place it into a container
	std::ifstream objReader("file.txt");
	if (objReader.is_open())
	{
		while (getline(objReader, line))
		{
			strVector.push_back(line);
		}
	objReader.close();
	}
    
    std::cout<<"The contents: ";
    for(std::vector<std::string>::const_iterator it1 = strVector.begin(); it1 != strVector.end(); ++it1)
    {
        std::cout << *it1 << " ";
    }
    std::cout<<std::endl;
    //2. Count all words in the container
    std::cout<< "There are "<<strVector.size()<<" words in the container."<<std::endl;
    //3. Is there a word "STL" in that file?
    int stlWordCount = std::count(strVector.begin(), strVector.end(), "STL");
    if(stlWordCount)
    {
        std::cout<<"There is STL word."<<std::endl;
    }
    else
    {
        std::cout<<"There is no STL word." <<std::endl;
    }
    //4. What is the last word?
    std::cout<<"The last word is "<<strVector.back()<<"."<<std::endl;
    //5. What is the middle word?
    std::cout<<"The middle word is "<<strVector[(strVector.size()/2)] <<"."<<std::endl;
    //6. How many words are there that has length greater than 3?
    int numOfWords = std::count_if(strVector.begin(), strVector.end(), isGreaterThan3);
    std::cout<<"There are "<<numOfWords<<" words that has length greater than 3."<<std::endl;
    //7. Remove all words whose length is less than 4
    std::vector<std::string>::iterator it = std::remove_if(strVector.begin(), strVector.end(), isLessThan4);
    strVector.erase(it, strVector.end());
    //8. Print content of container
    std::cout<<"The final contents: ";
    for(std::vector<std::string>::const_iterator it1 = strVector.begin(); it1 != strVector.end(); ++it1)
    {
        std::cout << *it1 << " ";
    }  
}
