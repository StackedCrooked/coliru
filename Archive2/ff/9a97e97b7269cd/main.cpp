#include <string>
#include <iostream>

using namespace std;

class File
{
    public:
        //Ctor
        File();
        //Dtor
        ~File(void);

        //Opens up the file for streaming data I/O
        //virtual bool open();

    protected:      
        string _file_name;

};

#include <string.h>
    File::File() {}
    File::~File(void) {}

#include <fstream>
#include <utility>

//Handles the input of our file
class FileReader : public File
{
    public:
        FileReader(string file_name_to_open);
        
//        FileReader(FileReader&& other)
//        : _in_stream(std::move(other._in_stream))
//        {}
//        
//        FileReader& operator=(FileReader&& other)
//        {
//            _in_stream = std::move(other._in_stream);
//            return *this;
//        }

        bool isFileOpen();
        bool open();
        ifstream _in_stream;
};

FileReader::FileReader(string file_name_to_open) { 
    _file_name = file_name_to_open;
    open();
}

bool FileReader::isFileOpen() {
    return _in_stream.is_open();
}

bool FileReader::open() {
    if(isFileOpen()) {
        try{
            _in_stream.open(_file_name , ios::in);
        } catch(exception exce) {
            return false;
        }
        return true;
    } else {
        return false;
    }

}

int main()
{
    FileReader my_file_reader = FileReader("hello.txt");
}
