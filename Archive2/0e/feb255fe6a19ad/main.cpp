#include <string>
#include <vector>
#include <tuple>
#include <cassert>

template<class T, int index, class...Us> T& cpp14getindex(T& val, std::tuple<Us...>&) {return val;}
template<class T, int index, class U, class...Us> T& cpp14getindex(U&, std::tuple<Us...>& tup, typename std::enable_if<!std::is_same<T,U>::value,void*>::type=0) {
    return cpp14getindex<T,index+1>(std::get<index+1>(tup), tup);
}
template<class T, class...Us> T& cpp14get(std::tuple<Us...>& tup) {return cpp14getindex<T,0>(std::get<0>(tup), tup);}


template <class T>
class RIVRecord
{

private:
    std::vector<T> values;
public:

    std::string name;

    RIVRecord(std::string _name, std::vector<T> _values) 
        :values(std::move(_values)),
        name(std::move(_name))        
    {};
    ~RIVRecord(void) {  };

    size_t size() const {
        return values.size();
    }

    T& Value(size_t index) {
        assert(index<values.size());
        return values[index];
    }

    const T& Value(size_t index) const {
        assert(index<values.size());
        return values[index];
    }
};

//store a single instance of each of RIVRecord<T>
template<class...Ts>
class RIVDataSet
{
private :
    std::tuple<std::vector<RIVRecord<Ts>>...> records;

public:
    RIVDataSet(void) {}
    ~RIVDataSet(void) {}
    //And this
    template<class U>
    void AddRecord(RIVRecord<U> record) {
        std::vector<RIVRecord<U>>& vec = cpp14get<std::vector<RIVRecord<U>>>(records);
        vec.push_back(std::move(record));
    }
    template<class U>
    RIVRecord<U>& GetRecord(size_t index) {
        std::vector<RIVRecord<U>>& vec = cpp14get<std::vector<RIVRecord<U>>>(records);
        assert(index<vec.size());
        return vec[index];
    }
    template<class U>
    const RIVRecord<U>& GetRecord(size_t index) const {
        std::vector<RIVRecord<U>>& vec = cpp14get<std::vector<RIVRecord<U>>>(records);
        assert(index<vec.size());
        return vec[index];
    }
};

#include <iostream>
int main() {    
    RIVDataSet<int,float> first;
    first.AddRecord(RIVRecord<int>("int",{3, 6}));
    first.AddRecord(RIVRecord<int>("otherint",{-501, 564813866}));
    first.AddRecord(RIVRecord<float>("flt",{3.14, 2e20}));
    std::cout << first.GetRecord<float>(0).Value(1);
}