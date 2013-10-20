#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

struct Set
{
    Set();
    Set(std::string);
    ~Set();

    void readLine(std::string inString);
    int addToSet(int element);

    bool containsElement(int element) const { return end(theSet) != find(begin(theSet), end(theSet), element); }

    std::vector<int> theSet;
};

struct ScanLine
{
    void openString(std::string const& str) 
    { 
        iss.clear(); iss.str(str); 
        input_it = {iss};
    }
    bool hasMoreData() const {
        return !iss.fail();
    }
    int nextInt() {
        return *input_it++;
    }

  private:
    std::istringstream iss;
    std::istream_iterator<int> input_it;
};


using namespace std;

/***************************************************************************************
 * Constructors and Destructors
**/
Set::Set()
{
}
Set::Set(string inputString) {
    readLine(inputString);
}

Set::~Set(){
}

/***************************************************************************************
 * readLine function
 * 
 * This function takes in a string, takes the next int, and stores in in a vector.
 *
 * Parameters: string, the string to be parsed.
 * 
**/
void Set::readLine(string inString){
    if(inString != ""){
        ScanLine scanLine;
        scanLine.openString(inString);
        while(scanLine.hasMoreData()){
            addToSet(scanLine.nextInt());
        }
    }
}

/***************************************************************************************
 * addToSet function
 * 
 * This function takes in a int that is an element and adds it to "this" Set.
 *
 * Parameters: int, the element to be added.
 * Return: int, the value that was added.
 * 
**/
int Set::addToSet(int element){
    int returnValue = -1;
    if(!containsElement(element)){
        this->theSet.push_back(element);
        returnValue = element;
    }
    return returnValue;
}

#include <cassert>

int main()
{
    Set set("1 2 3 47 9");
    assert(set.containsElement(1));
    assert(set.containsElement(2));
    assert(set.containsElement(3));
    assert(set.containsElement(47));
    assert(set.containsElement(9));
    
    assert(!set.containsElement(0));
    assert(!set.containsElement(4));
}
