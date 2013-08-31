#include <cstdio>


class File
{
public:
    File(FILE* file) : file(file)
    {
    }
    
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    
    File(File&& rhs) : file(rhs.file)
    {
        this->file = nullptr; // important!
    }
    
    File& operator=(File&& rhs)
    {
        this->file = rhs.file;
        rhs.file = nullptr; // important!
        return *this;
    }
    
    ~File()
    {
        if (file)
        {
            fclose(file);
        }
    }
    
    
private:
    FILE* file;
};
