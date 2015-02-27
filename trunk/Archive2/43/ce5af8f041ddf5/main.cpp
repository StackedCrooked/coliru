#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <list>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template<typename T>
std::ostream & operator<<(std::ostream& os, const std::list<T> & lit)
{
    for (auto &iter : lit)
    {
        os << iter << ' ';
    }
    return os;    
}

void test_reference(int * & val)
{
    int tmp_int(0);
    val = &tmp_int;
}

int main()
{
    int n(0);
    std::istringstream("2a") >> std::hex >> n;
    std::cout << n <<std::endl;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::list<std::string> tmp_list;
    for (auto &iter : words)
    {
        tmp_list.push_back(iter);
    }
    
    int tmp_val(9);
    int *tmp_ptr = &tmp_val;
    std::cout<<tmp_val <<" "<<std::hex<<tmp_ptr<<" "<<std::dec<<tmp_ptr<<std::endl;
    test_reference(tmp_ptr);
    std::cout<<std::hex<<tmp_ptr<<" "<<std::dec<<tmp_ptr<<std::endl;
    
    std::cout << words << std::endl;
    std::cout << tmp_list << std::endl;
    std::stringstream tmp_ss;
    tmp_ss << "11 hello 123";
    std::string tmp_str("");
    int tmp_int(0);
    
    tmp_ss >> tmp_int;
    tmp_ss >> tmp_str;
    tmp_ss >> tmp_int;
    std::cout << "tmp_str=" << tmp_str << "\n" << "tmp_int=" << tmp_int <<std::endl;
    return 0;
}
