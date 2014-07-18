#include <boost/python.hpp>
#include <vector>
#include <string>

void get_dir_list( boost::python::list dir_list )
{

    for (int i = 0; i < len(dir_list); ++i)
    {
    
        std::string x = boost::python::extract<std::string>(dir_list[i]);
        std::cout << "This is " << x << std::endl ;
    }
}

BOOST_PYTHON_MODULE(get_dir_list)
{
    def("get_dir_list", get_dir_list);
}
