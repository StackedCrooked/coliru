#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <map>
#include <string>
#include <sstream>
#include <iostream>


struct AXmlConfigurator : private boost::noncopyable {
protected:
    std::string configuration_file_;
    std::map<std::string, std::string> parameters_;
    ptree ptree_;

    AXmlConfigurator();

public:

    AXmlConfigurator(const std::string &argConfigurationFile) :
        configuration_file_(argConfigurationFile) {
        read_xml(configuration_file_, ptree_);
    }

    ~AXmlConfigurator() {}

    template<typename Type> inline
    Type get(const std::string & argPath, Type argDefault) const {
        Type value = ptree_.get<Type>(argPath, argDefault);
        parameters_.insert(std::pair<std::string,std::string>(argPath, value));
        return value;
    }

    template<class Type , class Translator> inline
    typename boost::enable_if<detail::is_translator<Translator>, Type>::type
    get(const std::string &argPath, const Type &argDefault, Translator tr) const {
        Type value = ptree_.get(argPath, argDefault);
        parameters_.insert(std::pair<std::string,std::string>(argPath, value));
        return value;
    }
    void logConfiguration() {
        for(std::map<std::string, std::string>::const_iterator it = parameters_.begin() ; it != parameters_.end() ; ++it) {
            std::cout << (*it).first << " => " << (*it).second << std::endl;
        }
    }

};
