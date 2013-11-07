#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include <string>

using namespace std;
class TestItem {
public:
TestItem () { 
    _name = "TestItem" + id();
    cout << "Constructing " << _name << endl;
}
TestItem (const TestItem & other) = delete;
TestItem& operator=(const TestItem& other)
{
    _name=other._name;
    cout << "assigning " << _name << endl;
    return *this;
}

string id() 
{
   return "ID";
}
~TestItem(){
   cout << "Destroying " << _name << endl;
}
void doStuff()
{
   // stub
}

string _name;
};

void run()
{
   cout << "making new obj" << endl;
   TestItem a;
   cout << endl << endl;

   map<string, TestItem> TestItemMap;
   cout << "Makeing new obj as part of a map insert" << endl;
   TestItemMap["foo"].doStuff();
   cout << endl << endl;

   cout << "adding a value to the map" << endl;
   TestItemMap["new mooky key"] = a;
   cout << endl << endl;

   cout << "looking up a value that has already been inserted" << endl;
   TestItem& b = TestItemMap["mooky"];
   (void)b;
   cout << endl << endl;
}

int main(int argc, char** argv)
{
   run();
}
