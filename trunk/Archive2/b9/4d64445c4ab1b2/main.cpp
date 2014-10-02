
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <algorithm>
#include "boost/progress.hpp"
using namespace std;

struct SomeLargeData {
    SomeLargeData(int id_)
        : id(id_)
    {}
    int id;
    int arr[100];
};

bool compare_by_value(const SomeLargeData& a, const SomeLargeData& b) {
    return a.id < b.id;
}

bool compare_by_ptr(const SomeLargeData* a, const SomeLargeData* b) {
    return a->id < b->id;
}

bool compare_by_uniqptr(const unique_ptr<SomeLargeData>& a,
                        const unique_ptr<SomeLargeData>& b) {
    return a->id < b->id;
}

int main()
{

    vector<SomeLargeData> vec_byval;
    vector<SomeLargeData*> vec_byptr;
    vector<unique_ptr<SomeLargeData>> vec_byuniqptr;
    static const int n = 10000000;

    for (int i = 0; i < n; ++i) {
        int id = rand() % 500000;
        vec_byval.push_back(SomeLargeData(id));
        vec_byptr.push_back(new SomeLargeData(id));
        vec_byuniqptr.push_back(
                unique_ptr<SomeLargeData>(new SomeLargeData(id)));
    }

    {
        boost::progress_timer t1;
        sort(vec_byval.begin(), vec_byval.end(), compare_by_value);
        double elapsed_time = t1.elapsed();
        cout <<"Sort using objects took" << elapsed_time <<endl; 
    }
    {
        boost::progress_timer t2;
        sort(vec_byptr.begin(), vec_byptr.end(), compare_by_ptr);
        double elapsed_time = t2.elapsed();
        cout <<"Sort using pointers took" << elapsed_time <<endl; 
    }
    {
        boost::progress_timer t3;    
        sort(vec_byuniqptr.begin(), vec_byuniqptr.end(), compare_by_uniqptr);
        double elapsed_time = t3.elapsed();
        cout <<"Sort using unique pointers took" << elapsed_time <<endl; 
    }
    return 0;
}



