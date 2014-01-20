#include<iostream>                                                                          
#include<string>                                                                            
#include <algorithm>

using namespace std;                                                                        

int  main ()                                                                                
{                                                                                           
  string string_to_edit;                                                                    
  cout<<"Enter a string to replace all the vowels:"<<endl;                                  
  cin>>string_to_edit;                                                                      
  string output_string=replace(string_to_edit.begin(),string_to_edit.end(),"a","x");               
  cout<<output_string<<endl;                                                                
  return 0;                                                                                 
} 