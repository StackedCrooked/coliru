struct read_interface
{
    virtual void read() = 0;
};
struct write_interface
{
    virtual void write() = 0;
};

struct bob: read_interface, write_interface
{
   void read(){};
   void write(){};
    
};


void f()
{
    bob a;
    a. write();
}
int main()
{
};