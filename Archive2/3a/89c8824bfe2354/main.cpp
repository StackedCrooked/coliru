#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <iterator>
#include <fstream>

struct Mydata {
    char myString;
    unsigned value;
};
std::istream& operator>>(std::istream &is, Mydata &d)
{return is >> d.myString >> d.value;}

int main()
{
    std::ifstream in("Data.txt");
    std::string line;
    while(std::getline(in, line)) {
        typedef std::pair<char,char> combo;
        typedef std::istream_iterator<Mydata> MydataIstrIt;
        std::map<combo, unsigned> CharP;
        std::stringstream ss(line);
        std::vector<Mydata> data {MydataIstrIt(ss), MydataIstrIt()};
        for(unsigned i=0; i<data.size()-1; ++i) {
            for(unsigned j=i+1; j<data.size(); ++j) {
                combo char_combo(data[i].myString, data[j].myString);
                CharP[char_combo] += 1;
            }
        }
    }
}