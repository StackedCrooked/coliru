#include <vector>
#include <algorithm>
#include <iostream>

template<class datapoint, class function>
void for_each_unmirrored(const std::vector<datapoint>& data, int num_values, function&& func) {
    std::vector<int> indexes;
    for_each_unmirrored_helper(0, data.size(), num_values, data, func, indexes);
}

template<class datapoint, class function>
void for_each_call_helper(const std::vector<datapoint>& data, function& func, std::vector<int>& indexes) {
    std::sort(indexes.begin(), indexes.end());
    static std::vector<datapoint> call_data;
    call_data.reserve(indexes.size());
    call_data.clear();
    for(int i=0; i<indexes.size(); ++i)
        call_data.push_back(data[i]);
    func(call_data);
}

template<class datapoint, class function>
void for_each_mirrored_helper(int minindex, int maxindex, int num_values, const std::vector<datapoint>& data, function& func, std::vector<int>& indexes) {
    if (minindex >= maxindex)
        return;
    if (num_values == 0) {
        for_each_call_helper(data, func, indexes);
        return;
    }
    indexes.push_back(minindex);
    for( ; indexes.back() < maxindex; ++indexes.back())
        for_each_mirrored_helper(indexes.back()+1, maxindex, num_values-1, data, func, indexes);
    indexes.pop_back();
}

template<class datapoint, class function>
void for_each_unmirrored_helper(int minindex, int maxindex, int num_values, const std::vector<datapoint>& data, function& func, std::vector<int>& indexes) {
    if (minindex >= maxindex)
        return;
    if (num_values == 0) {
        for_each_call_helper(data, func, indexes);
        return;
    }
    indexes.push_back(minindex);
    for_each_mirrored_helper(indexes.back()+1, maxindex-1, num_values-1, data, func, indexes);
    indexes.push_back(maxindex-1);
    for_each_unmirrored_helper(indexes.back()+1, maxindex-1, num_values-1, data, func, indexes);
    indexes.pop_back();
    indexes.pop_back();
}



#include <string>
struct printer {
    void operator()(const std::vector<std::string>& data) {
        for(unsigned i=0; i<data.size(); ++i)
            std::cout << data[i] << ' ';
        std::cout << '\n';
    }
};

int main() {
    std::vector<std::string> data = {"A", "B", "C", "D", "E", "F"};
    for_each_unmirrored(data, 3, printer());
}
    
    