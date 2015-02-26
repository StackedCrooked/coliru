#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>


template<typename T>
std::string serialize(const T&);


template<typename T>
T deserialize(const std::string &);


template<typename T>
std::string GetTypeName(); // uses a demangler


// 
using NameAndBody = std::tuple<std::string, std::string>;


// bool indicates success or failure.
// std::string element is serialized response or exception message
using Maybe = std::tuple<bool, std::string>; 


struct Client
{
    template<typename Command>
    typename Command::result_type send(typename Command::argument_type arg)
    {
        typename Command::result_type result;
        NameAndBody nameAndBody(GetTypeName<Command>(), serialize(arg));
        Maybe maybe = deserialize<Maybe>(send(serialize(nameAndBody)));
        if (std::get<0>(maybe))
        {
            return deserialize<typename Command::result_type>(std::get<1>(maybe));
        }
        else
        {
            throw std::runtime_error(std::get<1>(maybe));
        }
    }
    
    std::string send(const std::string&); // send to network and receive result
};


struct Server
{
    template<typename Command>
    void registerCommand(const std::function<typename Command::result_type(typename Command::argument_type)> func)
    {
        commands_.insert(std::make_pair(GetTypeName<Command>(), [func](const std::string & arg){
            return serialize(func(deserialize<typename Command::argument_type>(arg)));
        }));
    }
    
    // accept network request
    std::string accept(const std::string & request)
    {
        NameAndBody nameAndBody = deserialize<NameAndBody>(request);
        auto it = commands_.find(std::get<0>(nameAndBody));
        if (it != commands_.end())
        {
            auto & func = it->second;
            std::string result = func(std::get<1>(nameAndBody));
            return serialize(Maybe(true, result));
        }
        return serialize(Maybe(false, "Not found"));
    }
    
    
    using Executor = std::function<std::string(const std::string&)>;
    std::map<std::string, Executor> commands_;
};


struct Increment
{
    using argument_type = int;
    using result_type = int;
};


struct Sum
{
    using argument_type = std::tuple<int, int>;
    using result_type = int;
};


int main()
{
    Client client;
    assert(4 == client.send<Increment>(3));
    assert(7 == client.send<Sum>(std::make_tuple(3, 4)));
}