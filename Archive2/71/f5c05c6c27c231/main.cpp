#include <boost/make_shared.hpp>

#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>

struct FakeAgent {
  explicit FakeAgent() {} // pass in cache    
  template <class TModelIn>     
  void operator()(const TModelIn& in) const {
    std::cout << "Hello World!";   
  }
};
    
template <class TModelIn>
class Agent {
public:

  template <class TAgent>
  Agent(const TAgent& a) : a_(boost::make_shared<Holder<TAgent> >(a)) {}
  
  void operator()(const TModelIn& in) const {
    (*a_)(in);  
  }

private:

  class IAgent {
  public:
    virtual ~IAgent() {}
    virtual void operator()(const TModelIn& in) const = 0;
  };

  template <class U>
  struct Holder : IAgent {

    explicit Holder(const U& a) 
      : a_(a) {}
    
    void operator()(const TModelIn& in) const {
      return a_(in);
    }

    const U a_;
  };

  boost::shared_ptr<const IAgent> a_;

};    
    
    
template <class Key = std::string, 
          class Value = Key>    
struct Model {
  
  void setValue(const Key& key, const Value& value) {
    changes.insert(key);  
    data[key] = value;
  }
  
  void notify() const {
    if (changes.empty()) return; 
    for (AgentIter it = agents.begin();
        it != agents.end(); ++it) {
      (*it)(data);
    }
    changes.clear();
  }
  
  template <class TAgt> 
  void registerAgent(TAgt a) {
    agents.push_back(a);   
  }
  
  private:
  
  typedef std::map<Key, Value> Data;
  typedef std::set<Key> Changes;
  typedef Agent<Data> Agent_t;
  typedef std::vector<Agent_t> Agents;
  typedef typename Agents::const_iterator AgentIter; 
  
  Data data;
  mutable Changes changes;
  Agents agents;
};
    
int main()
{
  
  Model<> model;
  model.registerAgent(FakeAgent());
  model.setValue("Roger", "hatstand");
  model.notify();
  model.notify();
  model.setValue("Roger", "hatstand");
  model.notify();
  model.notify();
  model.notify();
  model.setValue("Roger", "hatstand");
}

