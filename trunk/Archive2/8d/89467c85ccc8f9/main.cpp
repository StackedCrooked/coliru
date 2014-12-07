#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <unordered_map>
#include <stdexcept>
#include <boost/any.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/optional.hpp>

using namespace std;

//Without localization and inversion of control.
using namespace boost;
enum class ParamType{
  BOOL,
  INT,
  FLOAT,
  STRING
};

enum class ParamEssentiality{
  NOT_ESSENTIAL,
  REQUIRED
};

struct Param{
  string name;
  ParamEssentiality required;
  ParamType type;
  string description;
};

class OptoParser{
public:
  class ArgumentParseError : public std::runtime_error{
  public:
    explicit ArgumentParseError(const std::string& s) : std::runtime_error(s) {}
  };
private:
  OptoParser() = delete;
  OptoParser(const OptoParser&) = delete;
  OptoParser(OptoParser&&) = delete;
  OptoParser operator =(const OptoParser&) = delete;
  OptoParser operator =(OptoParser&&) = delete;
  vector<Param> params;
  vector<string> args;
  unordered_map<string, std::reference_wrapper<const Param> > paramToDescriptor;
  unordered_map<string, any> paramToValue;
  static const string HELP_ARG;

  template<class T>
  T getValue(string name) const{//throw exceptions when wrong type or name. It's sign of method wrong using.
    return any_cast<T>(paramToValue.at(name));
  }
  any valueParse(string value, string paramName) const {
    const auto paramDescIt = paramToDescriptor.find(paramName);
    assert(paramDescIt != paramToDescriptor.cend());
    try{
      switch (paramDescIt->second.get().type)
      {
      case ParamType::INT:
          return lexical_cast<int>(value);
      case ParamType::STRING:
          return value;
      case ParamType::FLOAT:
          return lexical_cast<float>(value);
      default:
        assert(false);
        return none;
      }
    }
    catch (bad_lexical_cast&){
      throw ArgumentParseError((format("Wrong type for parameter: \"%1%\" with value \"%2%\"") % paramName % value).str());
    }
  }
  const Param& getParameterDescriptor(const string & paramName) const {
    const auto paramDescIt = paramToDescriptor.find(paramName);
    if (paramDescIt == paramToDescriptor.cend())
      throw ArgumentParseError((format("Unknown parameter: \"%1%\"") % paramName).str());
    return paramDescIt->second.get();
  }
  optional<string> unvaluedParameterParse(const string & paramName) {
    const auto& paramDesc = getParameterDescriptor(paramName);
    if (paramDesc.type == ParamType::BOOL){
      paramToValue[paramName] = true;
      return none;
    }
    return paramName;
  }
  void valuedParameterParse(const string & paramName, const string & value) {
    (void)getParameterDescriptor(paramName);
    paramToValue[paramName] = valueParse(value, paramName);
  }
  optional<string> paramParse(const string & arg) {
    const auto
      notFound = arg.cend(),
      eqSymPos = find(arg.cbegin(), notFound, '=');
    if (eqSymPos == notFound)
      return unvaluedParameterParse(arg);
    else{
      valuedParameterParse(string(arg.cbegin(), eqSymPos), &*(eqSymPos+1));
      return none;
    }
  }
  void makeParamToValue() {
    /*
    for (const auto& a : args)
      cout << a << "|";
    cout << endl;
    */
    optional<string> lastParamWaitedValue = none;
    for (const auto& arg : args){
      if (lastParamWaitedValue){
        paramToValue[*lastParamWaitedValue] = valueParse(arg, *lastParamWaitedValue);
        lastParamWaitedValue = none;
      }
      else if (algorithm::starts_with(arg, "--"))
        lastParamWaitedValue = paramParse(arg.c_str()+2);
      else
        throw ArgumentParseError((format("Wrong command-line token: \"%1%\"") % arg).str());
    }
  }
public:
  void outputHelp() const {
    cout << endl;
    for (const auto & param : params){
      if (param.required == ParamEssentiality::REQUIRED)
        cout << "[";
      cout << "--" << param.name;
      if (param.type != ParamType::BOOL)
        cout << "=value";
      if (param.required == ParamEssentiality::REQUIRED)
        cout << "]";
      cout << " - " << param.description;
      cout << endl;
    }
    cout << endl;
  }
  OptoParser(const vector<Param>& params) :
    params(params)
  {
    Param helpDesc{
      HELP_ARG,
      ParamEssentiality::NOT_ESSENTIAL,
      ParamType::BOOL,
      "help description"
    };
    this->params.push_back(helpDesc);
    for (const auto & param : this->params)
      paramToDescriptor.emplace(param.name, param);
  }
  void parse(int argc, char *argv[]){
    assert(!args.size());
    args.clear();
    args.reserve(argc);
    for (int i = 1; i < argc; ++i)
      args.push_back(argv[i]);
    makeParamToValue();
    for (const auto& p : params){
      if (p.required == ParamEssentiality::REQUIRED){
        if (p.type == ParamType::BOOL)
          if (paramToValue.cend() == paramToValue.find(p.name))
            paramToValue.emplace(p.name, false);
        if (paramToValue.find(p.name) == paramToValue.cend())
          throw ArgumentParseError((format("Required parameter: \"%1%\"") % p.name).str());
      }
    }
    if (paramToValue.find(HELP_ARG) != paramToValue.cend())
      outputHelp();
  }
  
  string getStringValue(string name) const{
    return getValue<string>(name);
  }

  bool getBoolValue(string name) const{
    return getValue<bool>(name);
  }

  int getIntValue(string name) const{
    return getValue<int>(name);
  }

  float getFloatValue(string name) const{
    return getValue<float>(name);
  }

  bool isParameterValueExist(string name) const{
    return paramToValue.find(name) != paramToValue.cend();
  }
};

const string OptoParser::HELP_ARG = "help";


int main(int argc, char *argv[]) {
    OptoParser o({
      {
        "my-bool",
        ParamEssentiality::REQUIRED,
        ParamType::BOOL,
        "description 1"
      },
      {
        "my-int",
        ParamEssentiality::REQUIRED,
        ParamType::INT,
        "description 2"
      },
      {
        "my-string",
        ParamEssentiality::REQUIRED,
        ParamType::STRING,
        "description 3"
      },
      {
        "my-float",
        ParamEssentiality::REQUIRED,
        ParamType::FLOAT,
        "description 4"
      },
      {
        "my-not-required-opt",
        ParamEssentiality::NOT_ESSENTIAL,
        ParamType::INT,
        "description 5"
      }
  });
  cout << endl;
  try {
    o.parse(argc, argv);
    cout << boolalpha << endl;
    cout << "my-bool=" << o.getBoolValue("my-bool") << endl;
    cout << "my-int=" << o.getIntValue("my-int") << endl;
    cout << "my-float=" << o.getFloatValue("my-float") << endl;
    cout << "my-string=" << o.getStringValue("my-string") << endl;
    if (o.isParameterValueExist("my-not-required-opt"))
      cout << "my-not-required-opt=" << o.getIntValue("my-not-required-opt") << endl;
    else
      cout << "my-not-required-opt is not set";
  } catch (OptoParser::ArgumentParseError& e) {
    cout << e.what() << endl;
    o.outputHelp();
  }
  return 0;
}
