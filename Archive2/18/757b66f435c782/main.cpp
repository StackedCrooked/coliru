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
        
        bool openFile(const std::string&) { return true; }
        bool writeHeader(int, int) { return true; }
        bool writeFile(unsigned char*, int) { return true; }
        bool closeStream() { return true; }
};

class BMP
{
        friend bool WRITER::writeData(const BMP& bmp); //only this writedata(...)
        //if I put the other writeData(unsigned char* data,int length,int width,int height,std::string outname); function here as a friend it works.
    public:
        //constructor, overloaded ops. copy csrt, destructor ect, loader ect...
    private:

        ::std::string m_filename;
        //other private members
        
        int m_width;
        int m_height;
        unsigned char* m_data;
        int m_length;

        //and more functs...
};
    
}

// ---

bool ::PND::WRITER::writeData(const BMP& bmp)
{
    if(!openFile(bmp.m_filename)) return false;
    if(!writeHeader(bmp.m_width,bmp.m_height)) return false;
    if(!writeFile(bmp.m_data,bmp.m_length)) return false;
    if(!closeStream()) return false;

    return true;
}

bool ::PND::WRITER::writeData(unsigned char* data,int length,int width,int height,std::string outname)
{
    if(!openFile(outname)) return false;
    if(!writeHeader(width,height)) return false;
    if(!writeFile(data,length)) return false;
    if(!closeStream()) return false;

    return true;
}

// ---

int main()
{
    PND::BMP bmp;
    PND::WRITER w;
    w.writeData(bmp);
    w.writeData(0, 0, 0, 0, "");
}
