#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <map>
#include <iostream>

struct SoundPack {
    std::string filepath_ = "soundpack.wav";
};
struct MappingScheme {
    std::string getId()    const { return "Id";    }
};
struct SensorConfiguration {
    std::string   getName()        const { return "Name";        }
    std::string   getSensorID()    const { return "SensorID";    }
    std::string   getsignalIndex() const { return "signalIndex"; }
    SoundPack     getSound()       const { return {};            }
    MappingScheme getMScheme()     const { return {};            }
};

void save(std::map<std::string, SensorConfiguration> sensorConfigurations_)
{
    using boost::property_tree::ptree;
    ptree pt;
    for(std::map<std::string, SensorConfiguration>:: iterator it = sensorConfigurations_.begin(); it != sensorConfigurations_.end(); ++it) 
    {
        ptree myTree;

        MappingScheme myScheme = it->second.getMScheme();
        SoundPack mySound = it->second.getSound();

        myTree.put("name",          it->second.getName());
        myTree.put("sensorid",      it->second.getSensorID());
        myTree.put("signalindex",   it->second.getsignalIndex());
        myTree.put("mappingscheme", myScheme.getId());
        myTree.put("soundpack",     mySound.filepath_);

        pt.add_child("root.sensorconfigurations.configuration", myTree);
    }
    boost::property_tree::xml_writer_settings<std::string> settings('\t', 1);
    write_xml(std::cout, pt, settings); 
}

int main() {
    save({
            { "first",  SensorConfiguration {} },
            { "second", SensorConfiguration {} },
            { "third",  SensorConfiguration {} },
            { "fourth", SensorConfiguration {} }
        });
}
