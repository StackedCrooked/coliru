#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

std::string const sample = R"(
{
   "background": {
      "scripts": [ "name1.js", "name2.js", "name3.js" ]
   },
      "default_popup": "popup.html",
      "default_title": "__MSG_name__",
   "content_scripts": [ {
      "all_frames": true,
      "js": [ "name4.js", "name5.js", "name6.js" ],
      "match_about_blank": true,
      "matches": [ "http://*/*", "https://*/*" ],
      "run_at": "document_start"
   }, {
      "all_frames": true,
      "js": [ "include.postload.js" ],
      "match_about_blank": true,
      "matches": [ "http://*/*", "https://*/*" ],
      "run_at": "document_end"
   } ]
})";

using boost::property_tree::ptree;
namespace j = boost::property_tree::json_parser;

int main() {
    std::istringstream iss(sample);
    ptree pt;
    j::read_json(iss, pt);

    for(auto& e : pt.get_child("content_scripts"))
        for(auto& r : e.second.get_child("js"))
            std::cout << r.second.get_value<std::string>() << "\n";
}

