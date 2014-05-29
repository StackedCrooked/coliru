#include <sstream>
#include <utility>
std::stringstream getss(){
   std::stringstream q;
   return std::move(q);
}
