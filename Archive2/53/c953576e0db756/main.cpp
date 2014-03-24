#include <random>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>


int main(){
   ::std::vector<char> letters(10);
   ::std::vector<char> unique;
   ::std::random_device rd;
   ::std::mt19937 mt(rd());
   ::std::uniform_int_distribution<char> dis('a', 'z');
   auto random = ::std::bind(dis, mt);
   for(char & l : letters){
       l = random();
   }
   int max_count = 0;
   char appeared_most = ' ';
    ::std::unique_copy(letters.cbegin(), letters.cend(), ::std::back_inserter(unique));
    for(const char & l : unique){
        int count = ::std::count(letters.cbegin(), letters.cend(), l);
        if(count > max_count){
            max_count = count;
            appeared_most = l;
        }
    }
    ::std::cout << appeared_most << " " << max_count ;
}