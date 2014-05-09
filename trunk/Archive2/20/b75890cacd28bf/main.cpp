//
//  main.cpp
//  Sandbox
//
//  Created by Gerard Simons on 07/05/14.
//  Copyright (c) 2014 Gerard Simons. All rights reserved.
//

#include <iostream>
#include <vector>

template<typename T, typename U, typename... V>
struct index_of : std::integral_constant<size_t, 1 + index_of<T, V...>::value>
{ };

template<typename T, typename... V>
struct index_of<T, T, V...> : std::integral_constant<size_t, 0>
{ };

template<typename T, typename... V>
struct is_different_than_all : std::integral_constant<bool, true>
{ };

template<typename T, typename U, typename... V>
struct is_different_than_all<T, U, V...>
: std::integral_constant<bool, !std::is_same<T, U>::value && is_different_than_all<T, V...>::value>
{ };

template<typename... V>
struct are_all_different : std::integral_constant<bool, true>
{ };

template<typename T, typename... V>
struct are_all_different<T, V...>
: std::integral_constant<bool, is_different_than_all<T, V...>::value && are_all_different<V...>::value>
{ };

template <typename... V>
class many_vectors
{
    //static_assert(are_all_different<V...>::value, "All types must be different!");
    
    std::tuple<std::vector<V>...> _data;
    
public:
    template<typename T>
    std::vector<T>& data()
    { return std::get<index_of<T, V...>::value>(_data); }
    
    template<typename T>
    std::vector<T> const& data() const
    { return std::get<index_of<T, V...>::value>(_data); }
    
    template<typename T>
    void push_back(T&& arg)
    { data<T>().push_back(std::forward<T>(arg)); }
};

template<typename T>
class RIVDataRecord {
public:
    std::string name;
    std::vector<T> values;
    RIVDataRecord(std::string name) {
        this->name = name;
    }

    void AddValue(T value) {
        values.push_back(value);
    }
};

class RIVDataSet {
private:
    many_vectors<RIVDataRecord<float>,RIVDataRecord<int>> records;
};

int main(int argc, const char * argv[])
{
    many_vectors<RIVDataRecord<int>,RIVDataRecord<int>> x;
    
    RIVDataRecord<int> xPixels = RIVDataRecord<int>("xPixels");
    xPixels.AddValue(1);
    
    RIVDataRecord<int> yPixels = RIVDataRecord<int>("yPixels");
    yPixels.AddValue(2);
    
    x.push_back(xPixels);
    x.push_back(yPixels);

    
    return 0;
}

