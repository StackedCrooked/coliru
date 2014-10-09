#include <iostream>

using namespace std;

 #include <boost/uuid/uuid.hpp>            // uuid class
 #include <boost/uuid/uuid_generators.hpp> // generators
 #include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
 
 int main() {
     boost::uuids::uuid uuid = boost::uuids::random_generator()();
     cout << uuid << endl;
 }
