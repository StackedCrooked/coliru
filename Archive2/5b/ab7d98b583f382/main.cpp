struct fcfs_type_index
{
  template<typename T>
  static int get()
  {
     static int index=counter++;
     return index;
  }
  
  static int counter;
};
int fcfs_type_index::counter=0;

#include <iostream>

int main()
{
  std::cout<<fcfs_type_index::get<int>()<<"\n";
  std::cout<<fcfs_type_index::get<char>()<<"\n";
  std::cout<<fcfs_type_index::get<double>()<<"\n";
  std::cout<<fcfs_type_index::get<char>()<<"\n";
  std::cout<<fcfs_type_index::get<int>()<<"\n";
}
