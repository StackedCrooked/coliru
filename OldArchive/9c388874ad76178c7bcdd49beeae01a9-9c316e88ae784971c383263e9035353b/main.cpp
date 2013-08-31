#include <fstream>
#include <sstream>
#include <iostream>

#include <map>
#include <memory>

const std::string Path_Folder = ".";

int main()
{
    std::istream& File     = std::cin; // just for example
    std::filebuf  dummy;
    std::ostream  TextFile(&dummy);

    struct Holder {
        Holder(std::string const& path) 
            : buf(std::make_shared<std::filebuf>())
        { 
            buf->open(path.c_str(), std::ios::out | std::ios::app);
        }
        std::shared_ptr<std::filebuf> buf;
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
        auto found = buffers.find(NameText);
        if (end(buffers) == found)
            found = buffers.insert({ NameText, Path }).first;
        
        TextFile.rdbuf(found->second.buf.get());

        TextFile << Line << std::endl; // notice implicit std::flush in std::endl
    }

    // all files are automatically closed here
}