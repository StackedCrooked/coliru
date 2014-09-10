#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
 
using namespace std;
 
const unsigned col_width=11u;
 
int main(){
  vector<string> col_names{
    "CPU", "user", "nice", "system", "idle", "iowait",
    "irq", "softirq", "stolen", "guest", "guest_nice"
  };
  map<string, vector<unsigned long long>> cpu_data;
  unsigned long long counter;
  string line;
  istringstream line_parser;
  string cpu_name;
 
  ifstream proc_stat("/proc/stat");
  while(getline(proc_stat, line)){
    line_parser.clear();
    line_parser.str(line);
    if((line_parser >> cpu_name) && cpu_name.substr(0, 3)=="cpu"){
      if(cpu_name=="cpu")
        cpu_name="TOTAL";
      while(line_parser >> counter)
        cpu_data[cpu_name].push_back(counter);
    }
  }
  proc_stat.close();
 
  for(auto &col : col_names)
    cout << setw(col_width) << col;
  cout << '\n';
 
  for(auto &cpu_info : cpu_data){
    cout << setw(col_width) << cpu_info.first;
    for(auto &col : cpu_info.second)
      cout << setw(col_width) << col;
    cout << '\n';
  }
}