#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>

#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>

using namespace std;

typedef boost::iostreams::tee_device<ostream, ofstream> TeeDevice;
typedef boost::iostreams::stream<TeeDevice> TeeStream;

int main()
{
    remove("file.log");
    ofstream logFile;
    logFile.open("file.log");

    ostream tmp(cout.rdbuf()); // <----
    TeeDevice outputDevice(tmp, logFile); // <----
    TeeStream logger(outputDevice);    

    cout.rdbuf(logger.rdbuf());
    cout << "some log info" << endl;

    logger.close();
}