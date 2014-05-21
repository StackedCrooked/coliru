#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <iostream>
#include <functional>

struct _Config
{
    std::string info[2];
    boost::property_tree::ptree pt;

    _Config()
    {
        info[0] = "If updating this file make sure to update all settings accordingly.";
        info[1] = "This program has been created by Name 'Nickname' Lastname";
    }

    void Save()
    {
        boost::property_tree::info_parser::write_info("./config.cfg.ex", pt);
    }

    void Load()
    {
        boost::property_tree::info_parser::read_info("./config.cfg", pt);
        {
            //check if variable already exists in config file, if yes load it to
            {
                //try to load entry
                boost::optional<std::string> v = pt.get_optional<std::string>("Info.a");
                if (v.is_initialized())
                    //overwrite default value
                    info[0] = v.get();
            }
            //if entry does not exist it will be created now, else the loaded value will be saved
            pt.put<std::string>("Info.a", info[0]);
        }

        //again for next variable
        {
            {
                boost::optional<std::string> v = pt.get_optional<std::string>("Info.b");
                if (v.is_initialized())
                    info[1] = v.get();
            }
            pt.put<std::string>("Info.b", info[1]);
        }
        Save();
    }

    ~_Config()
    {
        Save();
        pt.clear();
    }
};

int main()
{
    _Config Config;
    Config.Load();
}

