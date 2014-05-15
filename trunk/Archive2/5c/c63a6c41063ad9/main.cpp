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


void nuts()
{
    bob a;
    write_interface &foo = a;
    foo. write();
}
int main()
{
};