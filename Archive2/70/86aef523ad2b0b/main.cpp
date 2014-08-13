#include <string>
#include <unordered_map>
using namespace std;

class Parameter
{
public:
    enum eVarType { BOOL, NUMBER};

    Parameter() {}
    template<class X> Parameter( string , string , X  , enable_if_t<is_same<decay_t<X>, bool>::value> = 0) { type_ = BOOL;}
    Parameter( string , string , double  ) { type_ = NUMBER;}
private:
    eVarType type_;
};

class ParameterManager
{
public:
    template<typename T> void add( string option_name, string description, T value );
private:
    std::unordered_map< string, Parameter > parameters;
};

template<typename T> void ParameterManager::add( string param, string description, T value )
{
    parameters[param] = Parameter( param, description, value );
}

int main()
{
    ParameterManager mgr;
    int var = 1;
    mgr.add("number","This is an int",var); //Could be double or bool: I want it to be a double
}