#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

int main(){
    //This doesn't work
    std::string json= "{\"config_changed\":\"true\",\"config\":{\"apps\": [\"windows_registry_monitor\"],\"windows_registry_monitor\": {\"path\":\"HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\aaa\"},\"charset\": \"utf-8\",\"parser\": \"LineParser\",\"device_name\": \"test\",\"normalizer\": \"null\",\"repo\": \"default\"}}";
    //std::string json="{\"config_changed\":\"true\"}"; //this works
    boost::property_tree::ptree pt;
            try
            {
                std::stringstream ss(json);
                boost::property_tree::read_json (ss, pt);

            }
            //catch(boost::property_tree::json_parser::json_parser_error &err)
            catch(const std::exception& err)
            {
                std::cerr << err.what() << std::endl;
                //std::cerr << "Error parsing: " << err.filename() << " on line: " << err.line() << std::endl;
                //std::cerr << err.message() << std::endl;
            }
    std::cout<<pt.empty();
    write_json(std::cout,pt);
    return 0;


}