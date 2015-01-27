#include <iostream>
#include <vector>
#include <string>
#include <regex>


std::vector<int> x={3};
std::vector<int> y(3);
std::vector<int> z({3});

template<typename T>
void print_vector(std::vector<T> v)
{
  for(auto e : v)
       std::cout << e << std::endl;  
}

void foo1(int i)
{
    i++;
}

void foo2(int const i)
{
    //i++;
}

void foo3(const int& i)
{
    //i+=9;
}

void s_test()
{
    std::wstring s=std::to_wstring(56);
    
   // int i=std::stoi(s);
    
    std::wcout << s;
}

void reg_test()
{
  //std::regex rx("(\\d+)([.]\\d+){3}");  
  std::regex rx("(\\d+)[.](\\d+)[.](\\d+)[.](\\d+)");  
  
  std::string s("192.168.1.1");
  
  std::smatch select;
  
  if(std::regex_match(s,select,rx))
  {
      int size=select.size();
      std::cout << "Size: " << size;
      
      for(int i=0; i<size;i++)
        std::cout << std::endl << i << ": " << select[i];
  }
  
  std::cout << s;
}

void aufsummier()
{
   const std::string test_in("Auto: 12,50\nPorto: 0,62\nAuto: 60,20"); 
   
   //In entry tokens zerlegen
   {
       std::regex rx_Entry("[^\n]+");
       
        auto entry_begin = std::sregex_iterator(test_in.begin(), test_in.end(), rx_Entry);
        auto entry_end = std::sregex_iterator();
 
        std::cout << "Found " 
              << std::distance(entry_begin, entry_end) 
              << " words:\n";
 
        for (std::sregex_iterator i = entry_begin; i != entry_end; ++i) 
        {
           std::smatch match = *i;                                                 
           std::string match_str = match.str(); 
           std::cout << match_str << '\n';
           
            //Entry prozessieren
            {
                 std::regex rx_Values("(\\w*):\\s*(\\d{2},\\d{2})");
                 //std::regex rx_Values("(\\w):\\s*");
                 
                 std::smatch select;
      
                  if(std::regex_match(i->str(),select,rx_Values))
                  {
                      int size=select.size();
                      std::cout << "Size: " << size;
                      
                      for(int j=0; j<size;j++)
                        std::cout << std::endl << j << ": " << select[j];
                  }
            }
        }
    }
}

void time_test()
{
    time_t current_time;
    char* c_time_string;
 
    /* Obtain current time as seconds elapsed since the Epoch. */
    current_time = time(NULL);
 
    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to compute the current time.");
        return EXIT_FAILURE;
    }
 
    /* Convert to local time format. */
    c_time_string = ctime(&current_time);
 
    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.");
        return EXIT_FAILURE;
    }
 
    /* Print to stdout. */
    (void) printf("Current time is %s", c_time_string);
    return EXIT_SUCCESS;
}

int main()
{
    /*print_vector(x);
    print_vector(y);
    print_vector(z);
    
    int i=9;
    
    foo1(i);
    foo2(i);
    foo3(i);
    s_test();*/
    //reg_test();  
    //aufsummier();
    time_test();
}

