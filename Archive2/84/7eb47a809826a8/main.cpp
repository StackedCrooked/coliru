#include <deque>

int main()
{
    std::deque<double> name{1., 2., 3.};
    double average = ((name.at(1) + name.at(2)) / 2.00) ;
}
