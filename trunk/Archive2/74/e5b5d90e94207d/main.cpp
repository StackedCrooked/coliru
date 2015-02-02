#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> readCsvFileContent()
{
vector<string> buffer;
try{
    ifstream inputFile;
    string line;  
    inputFile.open("Input.csv", static_cast<std::ios::openmode>(std::ios::in) );              
    while (getline(inputFile,line)){
        buffer.push_back(line);}
        inputFile.close();}
    catch (ifstream::failure e){ 
    cout<<"No file read"<<endl;           
    throw e;}
return buffer;
}

int main() {
    auto vec = readCsvFileContent();
    for(const auto& str : vec)
        cout << str << endl;
}