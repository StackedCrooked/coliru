#include <type_traits>


enum Flags : unsigned
{
    Read = 1,
    Write = 2,
    Execute = 4
};


struct Reader
{
    void read() {}
};


struct Writer
{
    void write() {}
};


struct Runner
{
    void run() {}
};


template<unsigned>
struct Empty
{
};


template<unsigned N>
struct File : std::conditional<Read    & N, Reader , Empty<0>>::type,
              std::conditional<Write   & N, Writer , Empty<1>>::type,
              std::conditional<Execute & N, Runner , Empty<2>>::type
{
    
};


int main()
{    
    auto r = File<Read>{};
    r.read();
    
    auto w = File<Write>{};
    w.write();
    
    auto rw = File<Read|Write>{};
    rw.read();
    rw.write();
    
    
    auto rwx = File<Read|Write|Execute>{};
    rwx.read();
    rwx.write();
    rwx.run();
    
    // Error
    r.write();
    rw.run();
}