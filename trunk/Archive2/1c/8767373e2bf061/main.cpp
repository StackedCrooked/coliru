#include <list>
#include <future>
#include <algorithm>

using namespace std;

template<typename T>
struct sorter
{
    struct chunk_to_sort
    {
        std::list<T> data_m;
        std::promise<std::list<T> > promise_m;
    };
    list<chunk_to_sort> chunks_m;
    void do_sort(std::list<T>& chunk_data)
    {
        std::list<T> result;
        result.splice(result.begin(),chunk_data,chunk_data.begin());
        T const& partition_val=*result.begin();
        typename std::list<T>::iterator divide_point = std::partition(chunk_data.begin(),chunk_data.end(),[&](T const& val){return val<partition_val;});
        chunk_to_sort new_lower_chunk;
        new_lower_chunk.data_m.splice(new_lower_chunk.data_m.end(), chunk_data,chunk_data.begin(),divide_point);
        chunks_m.emplace_back(std::move(new_lower_chunk));
    }
};

int main()
{
    sorter<int> s;
    list<int> l;
    l.push_back(4);
    l.push_back(3);
    s.do_sort(l);
    return 0;
}
