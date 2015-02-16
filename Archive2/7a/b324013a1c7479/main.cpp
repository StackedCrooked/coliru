#include <iostream>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;
using namespace std;


void add_to_data(ptree& pt, const ptree& record)
{   
    if(!pt.get_child_optional("data")) {
        ptree arrayPt;
        arrayPt.push_back(make_pair("", record));
        pt.push_back(make_pair("data", arrayPt));
    } else {
       auto& dataPt = pt.get_child("data");
       dataPt.push_back(make_pair("", record));
    }   
}


int main()
{
    ptree pt;
    
    ptree record;
    auto v = vector<int>{0, 1, 2, 3, 4};
    for(int i : v)
        record.add(to_string(i), to_string(i));
    
    add_to_data(pt, record);
    add_to_data(pt, record);
    
    ostringstream out;
    write_json(out, pt);
    
    cout << out.str().c_str() << endl;
}
