#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    vector<string> argList;
    cout << "argc: " << argc << endl;
    for(int i=0; i < argc; ++i)
    {
        argList.push_back(argv[i]);
    }
    cout << "Program name is " << argList[0] << endl;
    if(argc > 1) {
        if(argList.at(1) == "-r") {
            cout << " Good job, you supplied -r\n";
        } else {
            cout << "Unrecognized option " << argList[1]
                << "\nUsage: " << argList[0] << " -r\n";
        }
    }
    return 0;
}