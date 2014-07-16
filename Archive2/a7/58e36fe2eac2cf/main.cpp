#include <iostream> 
#include <cstring> 
#include <type_traits> 
 
 
#define LOG(msg) { if (__builtin_constant_p(msg)) logConst(msg); else logCopy(msg); } 
   
 
 
void logConst(const char* msg) { 
  std::cout << "logConst: " << msg << std::endl; 
} 
 
 
void logCopy(const char* msg) { 
  char str[256]; 
  strcpy(str, msg); 
  std::cout << "logCopy:  " << str << std::endl; 
} 
 
 
template<typename T>  
constexpr auto makeprval(T&& t) -> typename std::remove_reference<T>::type { return t; } 
template<typename T> 
constexpr auto makeprval(T t[]) -> typename std::decay<T>::type { return t[0]; } 
#define isprvalconstexpr(e) noexcept(makeprval(e)) 
 
#define LOG2(msg) { if (isprvalconstexpr(msg)) logConst(msg); else logCopy(msg); } 
 
 
 
/*
namespace detail { 
template<int> struct sfinae_true : std::true_type{}; 
template<class T> 
sfinae_true<(T::f(), 0)> check(int); 
template<class> 
std::false_type check(...); 
} // detail:: 
 
template<class T> 
struct has_constexpr_f : decltype(detail::check<T>(0)){}; 
*/

 
int main() { 
  std::cout << "__builtin_constant_p" << std::endl; 
   
  LOG("string 1"); 
   
  char str2[] = "string 2"; 
  LOG(str2); 
   
  const char str3[] = "string 3"; 
  LOG(str3); 
 
  const char* str4 = "string 4"; 
  LOG(str4); 
   
  constexpr const char* str5 = "string 5"; 
  LOG(str5); 
   
  std::string str6("string 6"); 
  LOG(str6.c_str()); 
   
  std::cout << "constexpr" << std::endl; 
 
  LOG2("string 1"); 
  LOG2(str2); 
  LOG2(str3); 
  LOG2(str4); 
  LOG2(str5); 
  LOG2(str6.c_str()); 
} 
 