#include <iostream>
#include <string>
#include <vector> 

using namespace std;

struct OracleResultData
{
    int record_count;
    int field_count;
    vector<int> field_type;
    vector<int> field_size;
    vector<vector<int>> data_length;
    vector<vector<char*>> data_buffer;
}
;

int main()
{
    cout<<"done."<<endl;
    return 0;
}
