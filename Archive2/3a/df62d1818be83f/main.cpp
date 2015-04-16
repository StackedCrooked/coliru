#include <boost/container/vector.hpp>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

using namespace boost;
using namespace std;

struct Test
{
    bool copied;
    Test()
        : copied(false)
    {
    }
    Test(const Test&)
        : copied(true)
    {
    }
};

template<typename Container>
void check_move_constructor()
{
    Container from(1);
    Container to(boost::move(from));
    cout << "\tmove constructor is" << (to[0].copied ? " not" : "") << " working" << endl;
}

template<typename Container>
void check_move_assignment()
{
    Container from(1);
    Container to;
    to=boost::move(from);
    cout << "\tmove assignment is" << (to[0].copied ? " not" : "") << " working" << endl;
}

template<typename Container>
void check_move(const string &name)
{
    cout << name << " :" << endl;
    check_move_constructor< Container >();
    check_move_assignment< Container >();
    cout << string(16,'_') << endl;
}

int main()
{
    cout << boolalpha;
    check_move< container::vector<Test> >("boost::container::vector");
    check_move< vector<Test> >("std::vector");
   return 0;
}
