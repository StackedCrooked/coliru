#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<string>

bool isGreaterThan3(std::string word)    { return (word.length()>3); }
bool isLessThan4(std::string word)    { return (word.length()<4); }

int main()
{
    //1. Get all words in "file.txt" and place it into a container
    std::ifstream file;
    file.open ("file.txt");

    std::vector<std::string> words;

    std::string word;
    char x ;
    word.clear();

    while (!file.eof())
    {
        x = file.get();

        while (x!=' ' && x!='\n' &&  !file.eof())
        {
            word = word + x;
            x = file.get();
        }

        words.push_back(word);
        word.clear();

    }

    //2. Count all words in the container
    int wordCount = words.size();
    std::cout<<wordCount<<std::endl;

    //3. Is there a word "STL" in that file?

    if (std::find(words.begin(), words.end(), "STL") != words.end())
    std::cout<<"Yes"<<std::endl;
    else    std::cout<<"No"<<std::endl;

    //4. What is the last word?

    std::cout<<words.back()<<std::endl;

    //5. What is the middle word?

    if(wordCount%2)   std::cout<<words.at(wordCount/2)<<std::endl;
    else std::cout<<words.at((wordCount/2)-1)<<" & "<<words.at((wordCount/2))<<std::endl;

    //6. How many words are there that has length greater than 3?

    int greaterThan3 = std::count_if(words.begin(), words.end(), isGreaterThan3);
    std::cout<<greaterThan3<<std::endl;

    //7. Remove all words whose length is less than 4

    int lessThan4 = std::count_if(words.begin(), words.end(), isLessThan4);
    std::cout<<lessThan4<<std::endl<<std::endl;

    //8. Print content of container

    std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

    file.close();
}