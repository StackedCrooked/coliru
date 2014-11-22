#include <iostream>
#include <string>
#include <map>

#include <boost/foreach.hpp>
#include <boost/strong_typedef.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>

struct SensorConfiguration {
    void setName(std::string const& v) { _name = v; }
    std::string getName() const { return _name; }
    void setMappingScheme(std::string) {}
    void setSoundPack(std::string) {}
    void setSensorID(int) {}
    void setSignalIndex(int) {}

    std::string _name;
};

struct MyDemo {

    MyDemo() {
        std::string m_level;
        using boost::property_tree::ptree;
        ptree pt;
        read_xml("SensorConfigurationBank.xml", pt);
        BOOST_FOREACH(ptree::value_type & v, pt.get_child("root.sensorconfigurations")) {

            if (v.first == "configuration")
            {
                SensorConfiguration newSensorConf;

                BOOST_FOREACH(ptree::value_type & w, v.second) {
                    if (w.first == "name") {
                        newSensorConf.setName(w.second.data());
                    }
                    if (w.first == "sensorid") {
                        std::string stringToInt = w.second.data();
                        std::istringstream iss(stringToInt);
                        int value;
                        iss >> value;
                        newSensorConf.setSensorID(value);
                    }
                    if (w.first == "signalindex") {
                        std::string stringToInt = w.second.data();
                        std::istringstream iss(stringToInt);
                        int value;
                        iss >> value;
                        newSensorConf.setSignalIndex(value);
                    }
                    if (w.first == "mappingscheme") {
                        newSensorConf.setMappingScheme(getMappingScheme(w.second.data()));
                    }
                    if (w.first == "soundpack") {
                        newSensorConf.setSoundPack(w.second.data());
                    }
                }
                sensorConfigurations_.insert(make_pair(newSensorConf.getName(), newSensorConf));
            }
        }
        // save();
        
    }

    std::map<std::string, SensorConfiguration> sensorConfigurations_;

    template <typename T>
        std::string getMappingScheme(T const& v) {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            return boost::lexical_cast<std::string>(v);
        }

};

int main() { 
    MyDemo demo;

    for(auto & e : demo.sensorConfigurations_)
        std::cout << e.first << "\n";
}
