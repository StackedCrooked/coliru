#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

template<typename Key, typename T>
class OrderedMap
{
  using Pair_t = std::pair<Key,T>;
  std::vector<Pair_t> m_array;
  using Iterator_t      = typename std::vector<Pair_t>::iterator;
  using ConstIterator_t = typename std::vector<Pair_t>::const_iterator;

public:
  OrderedMap() {}

  OrderedMap(std::initializer_list<Pair_t> list) :
      m_array(list)
  {}

  ~OrderedMap() {}

  std::pair<Iterator_t, bool> insert(Pair_t & data)
  {
    m_array.push_back(move(data));
    return make_pair(m_array.end() - 1, true);
  }
  
    std::pair<Iterator_t, bool> insert(Pair_t && data)
  {
    m_array.push_back(data);
    return make_pair(m_array.end() - 1, true);
  }
  
    
  T const & at(Key const & key) const
  {
    auto found = find(key);
    if(found != end())
    {
      return found->second;
    }
    std::stringstream ss;
    ss << "Key " << key << " not found";
    throw std::out_of_range(ss.str());
  }

  T & operator[](Key const  & key)
  {
    auto found = find(key);
    if(found != end())
    {
      return found->second;
    }
    else
    {
      T value;
      auto ret = insert(make_pair(key,value));
      return (*ret.first).second;
    }
  }

  size_t  size() const { return m_array.size(); }
  void    clear() { m_array.clear(); }
  auto    find(Key const & key)       -> Iterator_t       { return std::find_if(begin(), end(), [key] (Pair_t const & s) { return s.first == key;});  }
  auto    find(Key const & key) const -> ConstIterator_t  { return std::find_if(begin(), end(), [key] (Pair_t const & s) { return s.first == key;});  }
  auto    begin()  -> Iterator_t  { return m_array.begin(); }
  auto    end()   -> Iterator_t   { return m_array.end();}
  auto    begin() const -> ConstIterator_t  { return m_array.begin(); }
  auto    end()   const -> ConstIterator_t  { return m_array.end();}
  bool    empty() const {return m_array.empty();}

  // more methods should be implemented as needed...
};


enum class BusPropertyAccess
{
  NONE,                     /**< no access */
  READ_ONLY,                /**< read only */
  READ_WRITE,               /**< read and write */
  WRITE_ONLY                /**< write only */
};

struct BusArgument;
struct BusNode;
struct BusMethod;
struct BusSignal;
struct BusProperty;
struct BusNode;
struct BusInterface;

/**
 * Generic Serializable - has to provide a serializer on use, e.g BusNode().WriteObject<SerializerJSON>(std::cout);
 */
template<typename T>
class Serializable
{
public:

  template<typename TSerializer>
  void WriteObject(std::ostream & out) const
  {
      auto a = static_cast< T const &>(*this);
      TSerializer serializer(out);
      serializer.WriteObject(a);
  }
  Serializable(){}
  virtual ~Serializable() {}
};


/**
 * Generic dictionary for bus model objects. Supports all types and using any "map" implementation.
 * Default "map" implementation is std::map
 */
template<typename T, typename Map_t = std::map<std::string, T>>
struct Dictionary: public Serializable<Dictionary<T>>
{
  Map_t  tuples;
};

/**
 * Specialization of Dictionary<T> using std::multimap. Used in BusArgument and BusProperty annotations.
 */
template<typename T> using MultiDictionary = Dictionary<T, typename std::multimap<std::string, T>>;

/**
 * Specialization of Dictionary<T> using OrderedMap. Used for list of BusArgument.
 */
template<typename T> using OrderedDictionary = Dictionary<T, OrderedMap<std::string, T>>;

/**
 * Bus annotation
 */
struct BusAnnotation: public Serializable<BusAnnotation>
{
  std::string   name;
  std::string   value;
};

/**
 * Base type
 */
struct BusType
{
  enum class Type
  {
    INT,
    STRING,
    FLOAT,
    BOOL,
    STRUCT,
    ARRAY,
    DICTELEMENT
  };

  Type  type;
  std::string busType;  // original bus type
  virtual ~BusType() {}
};

struct BusTypeConstraint
{
  std::string constraint;
};

template<typename T>
struct BusTypeConstraintMinMax
{
  T value;
};

template<typename T>
struct BusTypeConstraintEnums
{
  std::vector<T> enums;
};

/**
 * Basic type (string, int, bool)
 */
struct BusTypeBasic: public BusType
{
  Dictionary<BusTypeConstraint> constraints;
};

/**
 * Struct type
 */
struct BusTypeStruct: public BusType
{
  using TypePtr_t = std::unique_ptr<BusType>;
  OrderedDictionary<TypePtr_t>  members;
};

/**
 * Array type
 */
struct BusTypeArray: public BusType
{
  std::unique_ptr<BusType>      element;
};

/**
 * Dictionary element type
 */
struct BusTypeDictionaryElement: public BusType
{
  std::unique_ptr<BusType>             key;
  std::unique_ptr<BusType>             value;
};

/**
 * Bus argument (method, signal ...)
 */
struct BusArgument: public Serializable<BusArgument>
{
  std::string                         name;
  std::unique_ptr<BusType>            type;
  OrderedDictionary<BusAnnotation>    annotations;
};

struct BusProperty: public Serializable<BusProperty>
{
  std::string                         name;
  std::unique_ptr<BusType>            signature;
  BusPropertyAccess                   access;
  OrderedDictionary<BusAnnotation>    annotations;
};


/**
 * Bus signal
 */
struct BusSignal: public Serializable<BusSignal>
{
  std::string                      name;
  OrderedDictionary<BusArgument>   arguments;
  OrderedDictionary<BusAnnotation> annotations;

};


/**
 * Bus method
 */
struct BusMethod: public Serializable<BusMethod>
{
  std::string                     name;
  OrderedDictionary<BusArgument>  in_arguments;
  OrderedDictionary<BusArgument>  out_arguments;
  Dictionary<BusAnnotation>       annotations;

};

/**
 * Bus interface
 */
struct BusInterface: public Serializable<BusInterface>
{
  std::string                  name;
  Dictionary<BusMethod>        methods;
  Dictionary<BusSignal>        signals;
  Dictionary<BusProperty>      properties;
  Dictionary<BusAnnotation>    annotations;

};

/**
 * Bus object node - reflects the <node> element in http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd
 */
struct BusNode: public Serializable<BusNode>
{
  std::string                 path;
  Dictionary<BusInterface>    interfaces;
  Dictionary<BusNode>         nodes;
  Dictionary<BusAnnotation>   annotations;
};

void f(pair<string, unique_ptr<BusType>> & p)
{
    
}

int main()
{
    OrderedDictionary<unique_ptr<BusType>>  members;
    OrderedDictionary<int>  membersI;    
    
    auto b = unique_ptr<BusTypeBasic>(new BusTypeBasic);
    b->type = BusType::Type::INT;
    auto s = unique_ptr<BusTypeStruct>(new BusTypeStruct);

    unique_ptr<BusTypeBasic> bb = move(b);
    pair<string, unique_ptr<BusType>> p = make_pair("0",move(bb));
    pair<string, unique_ptr<BusType>> p1 = move(p);
    
    pair<string,int> ipair = make_pair("0",2);
    membersI.tuples.insert(ipair);
    membersI.tuples.insert(make_pair("1",3));
    
    f(p1);
       
    members.tuples.insert(p1);
 
    auto bbb = unique_ptr<BusTypeBasic>(new BusTypeBasic);
    pair<string, unique_ptr<BusTupe>> pairbbb = make_pair("0", bbb);
    s->members.tuples.insert(pairbbb);
    
}