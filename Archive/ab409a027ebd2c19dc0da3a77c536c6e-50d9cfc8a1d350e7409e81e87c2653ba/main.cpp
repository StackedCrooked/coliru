#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class nation
{
    public:
    void init();
    string genName();
    string getName();

    private:
    string myName;
    int* myBorderPoints;
};

string nation::getName()
{
    return myName;
}

string nation::genName()
{
    int listLength = 0, listPos = 0, listRand = 0;
    string nameToGen = "";
    string* namePartList;
    ifstream fileName;
    fileName.open("NamePart1.txt");
    listLength = fileName.tellg();
    namePartList = new string[listLength]; // Seg fault here
    while (fileName.good())
    {
        while (!fileName.eof())
        {
            getline(fileName,namePartList[listPos]);
            listPos += 1;
        }
    }
    listRand = rand() % listLength;
    nameToGen += namePartList[listRand];
    fileName.close();
    listLength = 0;
    listPos = 0;
    listRand = 0;
    nameToGen = "";
    fileName.open("NamePart2.txt");
    listLength = fileName.tellg();
    namePartList = new string[listLength];
    while (fileName.good())
    {
        while (!fileName.eof())
        {
            getline(fileName,namePartList[listPos]);
            listPos += 1;
        }
    }
    listRand = rand() % listLength;
    nameToGen += namePartList[listRand];
    fileName.close();
    return nameToGen;
}

void nation::init()
{
    srand(time(NULL));
    myName = genName();
}

int main()
{
    nation testNation;
    testNation.init();
    cout << testNation.getName();
    return 0;
}