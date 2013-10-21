#include <sstream>
#include <iostream>

class sink : public std::stringbuf
{
    public:
        sink(std::ostream& os) : stream(os), buf(os.rdbuf()) { os.rdbuf(this);  }
        ~sink() { stream.rdbuf(buf); }
    private:
        std::ostream& stream;
        std::streambuf* buf;
};


void print_to_console() {
    std::cout << "Hello from print_to_console()" << std::endl;
}

void foo(){
  std::cout<<"hello world"<<std::endl; 
  print_to_console(); // this could be printed from anything
}

int main()
{
    std::string s;
    {
        sink start_sink(std::cout);
        
        foo(); //all the std::cout goes to sink
        
        s = start_sink.str(); //get it before it dies
    }
    std::cout << "<redirected-output>\n" << s <<  "</redirected-output>" << std::endl;
}