#include "boost/filesystem.hpp"
#include <vector>
#include <iostream>

int main() {
    boost::filesystem::path p("."); // or "C:\\Customer\\AppleFruit\\"

    std::vector<boost::filesystem::path> inVec, outVec;

    std::partition_copy(
            boost::filesystem::directory_iterator(p), {},
            back_inserter(inVec),
            back_inserter(outVec),
            [](boost::filesystem::directory_entry const& de) { 
                return de.path().filename().native().find("In_") == 0;
            ; });

    std::sort(inVec.begin(),  inVec.end());
    std::sort(outVec.begin(), outVec.end());

    for(auto& f : inVec)
    {
        std::cout << f << "\n";
    }
}
