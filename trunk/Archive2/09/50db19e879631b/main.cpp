#include <iostream>
#include <typeinfo>

using namespace std;

class Config  {
public:

  enum { NO_ID = 999 };

  struct aType { bool a; };
  struct bType { size_t b; };
  struct cType { time_t c; };
  struct ValueType {
    aType aField;
    bType bField;
    cType cField;
  };
  Config( bool a, size_t b, time_t c) {
    _a.a = a;
    _b.b = b;
    _c.c = c;
  }
  template <typename T>
  T getField(ValueType val) { throw "Unknown type"; }

  template <typename T>
  T getDefaultField() { throw "Unknown type"; }

  //  template <typename T>
  //void fun1(T val) { cout << "-D- Fun1 type=" << typeid(val).name() << endl; }

  template <typename T>
  T get(int id = NO_ID ) {
    T result = getDefaultField<T>();
    if (id != NO_ID) {
      ValueType val = do_getFromDB(id);
      result = getField<T>(val);
    }
    return result;
  }

  ValueType getFromDB( int /* id */ ) { /* ... */ throw "something" ; }
  
  ValueType do_getFromDB( int id ) 
  {
    try {  /* ... */ return getFromDB(id) ; }
    catch(...) { 
      cout << "-E- Cannot get from DB id=" << id << endl;
      ValueType defaultVal = { _a, _b, _c};
      return defaultVal;
    }
  }

private:
  aType _a;
  bType _b;
  cType _c;
};

// Explicit specialization of getField
template <>
Config::aType Config::getField(ValueType val) { return val.aField; }

template <>
Config::bType Config::getField(ValueType val) { return val.bField; }

template <>
Config::cType Config::getField(ValueType val) { return val.cField; }

// Explicit specialization of getDefaultField
template <>
Config::aType Config::getDefaultField() { return _a; }

template <>
Config::bType Config::getDefaultField() { return _b; }

template <>
Config::cType Config::getDefaultField() { return _c; }

int main() {
   time_t tm(333);
   Config conf(true, 111, tm);
   Config::aType a2 = { false };
   Config::bType b2 = { 222 };
   Config::cType c2 = { tm };

   cout << "-D- Call conf.get<aType>(101)\n";    
   Config::aType aResult = conf.get<Config::aType>(101);  
   cout << "-D- aResult=" << std::boolalpha << aResult.a << endl;

   cout << "-D- Call conf.get<bType>(102)\n";	
   Config::bType bResult = conf.get<Config::bType>(102);  
   cout << "-D- bResult=" << bResult.b << endl;

   cout << "-D- Call conf.get<cType>(101)\n";	
   Config::cType cResult = conf.get<Config::cType>(101);  
   cout << "-D- cResult=" << cResult.c << endl;
}
