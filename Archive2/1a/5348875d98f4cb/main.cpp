#include<iostream>
#include<memory>
#include<array>

#include <unistd.h>

struct FileDescriptorDeleter {
    struct Int {
        Int() = default;
        Int( int v ) : value_{v} {}
        
        bool operator== ( std::nullptr_t ) { return value_ == -1; }
        bool operator!= ( std::nullptr_t ) { return value_ != -1; }
        
        Int& operator*() { return *this; }
        Int const& operator*() const { return *this; }
        operator int() const { return value_; }
    private:
        int value_{-1};
    };
    using pointer = Int;
    
    void operator() ( pointer p ) const {
        close( p );
    }
};

using FilePtr = std::unique_ptr<FileDescriptorDeleter::pointer, FileDescriptorDeleter>;
using PipePtr = std::array<FilePtr,2>;

PipePtr OpenPipe() {
    int fd[2];
    if ( pipe(fd) == 0 )
        return { { FilePtr{fd[0]}, FilePtr{fd[1]} } };
    else
        return {};
}

int main() {
    auto p = OpenPipe();
    if ( p[0] && p[1] ) {
        int v = 42;
        write( *p[1], &v, sizeof(v) );
        int vv = 13;
        read( *p[0], &vv, sizeof(vv) ); // p[0].get() possible too
        std::cout << vv;
    }
}