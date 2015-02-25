//#include <boost/typeof/typeof.hpp>
//
//#include <boost/lambda/lambda.hpp>
//#include <boost/lambda/bind.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>       // std::vector
//#include <list>
//#include <boost/function.hpp>

using namespace std;

int main()
{
    string str("this is line");
    istringstream sin(str);
    vector<string> c(6);

    vector<string>::iterator cend= copy(istream_iterator<string>(sin), istream_iterator<string>(), c.begin());
    copy(c.begin(), cend, ostream_iterator<string>(cout," "));
    cout<<endl;
    sin.clear();
    sin.seekg(0);    
    vector<string>::iterator cend2= copy(istream_iterator<string>(sin), istream_iterator<string>(), cend);
    //copy(c.begin(), cend2, ostream_iterator<string>(cout," "));
    //cout<<endl;

    //s>>c[0];
    //s>>c[1];
    //s>>c[2];
    //s>>x;

    copy(c.begin(), cend2, ostream_iterator<string>(cout," "));
    //copy(istream_iterator<string>(cin), istream_iterator<string>(), ostream_iterator<string>(cout,"\n"));
    cout<<endl;
    //copy(c.begin(), c.end(), ostream_iterator<string>(cout," "));

    //cout<<x<<endl;
}