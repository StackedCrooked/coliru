#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
 
int main() {
int z = 0;
std::vector<std::string> names = {"john", "bobby", "dear", "test1", "catherine", "nomi", "shinta", "martin", "abe", "may", "zeno", "zack", "angeal", "gabby", "george"};
 
sort(names.begin(), names.end() );

ofstream myfile;
myfile.open ("names.txt");
for(auto name : names){
    myfile << name << endl;
}

myfile.close();
        return 0;
 
}