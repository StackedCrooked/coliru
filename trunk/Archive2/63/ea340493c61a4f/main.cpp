#include <string>
#include <set>
#include <iostream>
using std::string;
using std::set;

unsigned long countUWords(const string& s)
{
  set<string> uw;
  string word = "";
  for(size_t i = 0; i < s.size(); i++){
    bool words = (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z');
    if(words){
      word += s[i];
    }
    else if(!words && word != ""){
      uw.insert(word);
      word = "";
    }
  }
  if (word != "")
    uw.insert(word);
  return uw.size();
}

int main(int, char*[]) {
    string x = "Testing this algorithm";
    std::cout << countUWords(x) << "\n";
}