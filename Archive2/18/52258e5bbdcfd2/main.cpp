// Flushing files
#include <fstream>      // std::ofstream
#include <iterator>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
int main () {

    string dt = "2013-02-12T12:33:44";
    auto t = boost::posix_time::time_from_string(dt);
    cout << boost::posix_time::to_iso_string(t) << endl;
  return 0;
}