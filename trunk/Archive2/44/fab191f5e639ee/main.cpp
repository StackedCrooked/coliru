#include <iostream>
#include <string>

template <int N>
void showcolumns_num(std::string (&columns)[N])
{
    int columns_num=std::extent<typename std::remove_reference<decltype(columns)>::type>::value;
    std::cout<<"function array length: "<<columns_num<<std::endl;
}

int main()
{
    std::string column_list[]={"col1","col2","col3","col4","col5"};

    // local calculation of column number
    int columns_num=std::extent<decltype(column_list)>::value;
    std::cout<<"local array length: "<<columns_num<<std::endl;

    // function calculation of column number
    showcolumns_num(column_list);
}
