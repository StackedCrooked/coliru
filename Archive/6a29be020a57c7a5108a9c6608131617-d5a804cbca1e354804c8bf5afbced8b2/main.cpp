#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}

/*
int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
*/



void fundoo(bool enc, char* mC){
    std::string mStr(mC);
    std::string::iterator sit = mStr.begin();
    for (;sit!=mStr.end();sit++){
        if(enc) *sit = *sit+1;
        else *sit = *sit+1;
    }
    std::cout << mStr << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
}