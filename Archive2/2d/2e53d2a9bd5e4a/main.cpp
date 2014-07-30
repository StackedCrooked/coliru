#include <memory>
#include <vector>
#include <iostream>
#include <array>
#include <string>
#include <algorithm>

void RC4(std::string const&  password, std::vector<char>& content)
{
    std::array<unsigned char, 256> S;
    std::iota(std::begin(S), std::end(S), 0);
     
    for(unsigned i{}, j{}; i < S.size(); i++)
    {
        j = (j + S[i] + password[i % password.size()])%256;
        std::swap(S[i], S[j]);
    }
    
    std::vector<char> output(content.size());
    for(unsigned k{}, i{}, j{}; k < content.size(); k++)
    {
        i = (i+1)%S.size();
        j = (j + S[i]) % S.size();
 
        std::swap(S[i], S[j]);
 
        output[k] = ((S[(S[i] + S[j])%S.size()]) ^ content[k]);
    } 
    content.swap(output);
}

int main(){
  std::vector<std::string[2]> v;
  return 0;
}