#include <iostream>

using namespace std;

// ------------------File.hpp-----------------

#ifndef FILE_HPP
#define FILE_HPP

#include <string>

enum class my_enum{
    GENERIC = 0,
    FIRST   = 1,
    SECOND  = 2
};

enum class me_enum{
    GENERIC = 0,
    SECOND_TO_LAST = 1,
    LAST    = 2,
};

class FileBase{
    public:
        FileBase(std::string);
        void read();

    protected:
        std::string _filename;
};

template<my_enum MY, me_enum ME>
class File: public FileBase{
    public:
        using FileBase::FileBase;

};

// Partial templat specialization
template<me_enum ME>
class File<my_enum::FIRST, ME>: public FileBase{
    public:
        File(std::string);

    private:
        std::string _filename;
};

#endif  // FILE_HPP
// ------------------File.cpp-----------------

#include <iostream>
#include <string>

using namespace std;

FileBase::FileBase(std::string filename): 
    _filename(filename)
{
    cout << "Filename is: " << _filename << std::endl;
}

void FileBase::read(){
    cout << "\tI'm reading from " << _filename << std::endl;
}

template<me_enum ME>
File<my_enum::FIRST, ME>::File(std::string filename):
    _filename(filename)
{
    cout << "Filename in specialized constructor is: "
         << _filename << std::endl;
}

// ------------------special.cpp-----------------
//
// Compile with:
//  clang++ -std=c++11 -stdlib=libc++ special.cpp File.cpp -o special
//

int main(){

    FileBase* FB(new FileBase("baseFilename.txt"));
    FB->read();

    FileBase* F02(new File<my_enum::GENERIC, me_enum::LAST>("filename-02.txt"));
    F02->read();

    // The next two lines don't compile
    // FileBase* F10(new File<me_enum::GENERIC>("filename-10.txt"));
    // F10->read();

    return 0;
}
