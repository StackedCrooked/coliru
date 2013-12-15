#include <string>

namespace PND {
class BMP;

class WRITER
{
    public:
        bool writeData(const BMP& bmp); //outname is from BMP
        bool writeData(unsigned char* data,int length,int width,int height,std::string outname); //outname is user defined
    private:
        //other functions and error handling
};

class BMP
{
    public:
        //constructor, overloaded ops. copy csrt, destructor ect, loader ect...
    private:

        ::std::string m_filename;
        //other private members

        friend bool WRITER::writeData(const BMP& bmp); //only this writedata(...)
        //and more functs...
};
}

bool ::PND::WRITER::writeData(const BMP& bmp)
{
    void(bmp.m_filename);
    return true;
}

int main()
{
}