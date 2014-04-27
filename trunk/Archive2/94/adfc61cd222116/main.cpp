#include <iostream>
#include <string>

template <typename T>
class singleton
{
    public:
    virtual ~singleton(){}
    static T & get_instance()
    {
        return _instance;
    }
    private:
    static T  _instance;
};

class print_stderr : public singleton<print_stderr>
{
    friend singleton<print_stderr>;
    public:
    void salut(){std::cout << "salut" << std::endl;}
    private:
    print_stderr(){}
    ~print_stderr(){}
};

int main()
{
   // print_stderr c; //error
   print_stderr::get_instance().salut();
}