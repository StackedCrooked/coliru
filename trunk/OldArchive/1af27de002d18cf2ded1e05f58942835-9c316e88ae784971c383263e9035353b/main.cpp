#include <fstream>
#include <sstream>
#include <iostream>

#include <map>
#include <memory>

const std::string Path_Folder = ".";

int main()
{
    std::istream& File     = std::cin; // just for example
    std::ostringstream dummy;
    std::ostream& TextFile = dummy;    // dummy output, to switch

    struct Holder {
        Holder(std::string const& path) 
            : stream(std::make_shared<std::ofstream>(path.c_str(), std::ios::app))
        { }
        std::shared_ptr<std::ofstream> stream;
    };

    std::map<std::string, Holder> buffers;
    int i = 0;

    std::string   Line;
    while(getline(File, Line))
    {
        if (i++<2)
            continue; //Skip Headers

        auto NameText = Line.substr(0, Line.find(','));
        auto Path = Path_Folder + '/' + NameText + ".csv";

        // open, only if not allready opened
        TextFile.rdbuf(buffers.insert({ NameText, Path }).first->second.stream->rdbuf());

        TextFile << Line << std::endl; // notice implicit std::flush in std::endl
    }

    // all files are automatically closed here
}
