#include <iostream>
#include <string>

struct _
{
    _(){std::cout<<"Ctor"<<std::endl;}
    ~_(){std::cout<<"Dtor"<<std::endl;}
    _(_ const &) = delete;
    _(_ &&) = delete;
    _ &operator=(_ const &) = delete;
    _ &operator=(_ &&) = delete;
    operator bool()const{return std::cout<<"bool()"<<std::endl;}
    friend _ &operator>>(_ &s, std::string &v)
    {
        std::cout << ">>" << v << std::endl;
        return s;
    }
};

int main()
{
	std::string a {"a"}, b {"b"};
    if(_{} >> a >> b)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}
