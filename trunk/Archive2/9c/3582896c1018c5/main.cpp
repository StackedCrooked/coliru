#include <vector>
#include <string>
#include <iostream>

using namespace std;

class networkbuffer_in
{
protected:
    vector<unsigned char> _buffer;
    int _size;
    void safe_push_back(unsigned char);
public:
    networkbuffer_in(int size) {}
    int getSize() const;
    const unsigned char* getBuffer() const;
    const int getDataLength() const;
    networkbuffer_in& operator<<(bool) { std::cout << "woot!\n"; return *this; }
    networkbuffer_in& operator<<(int);
    networkbuffer_in& operator<<(short);
    networkbuffer_in& operator<<(char);
    networkbuffer_in& operator<<(unsigned int);
    networkbuffer_in& operator<<(unsigned short);
    networkbuffer_in& operator<<(unsigned char);
    networkbuffer_in& operator<<(const string&);
    networkbuffer_in& operator<<(const char*);
    networkbuffer_in& copyto(const unsigned char*, int len);

};

void serialize(networkbuffer_in& data)
{
    bool target = true;
    data << target;
}

int main()
{
    networkbuffer_in x(5);
    serialize(x);
}