#include <iostream>
#include <cassert>

bool next_unused(char& dest, char begin, bool* used) {
    used[dest] = false;
    dest = 0;
    if (begin > 'Z') return false;
    while(used[begin]) {
        if (++begin > 'Z')
            return false;
    }
    dest = begin;
    used[begin] = true;
    return true;
}

void reset_range(std::string& word, int begin, bool* used) {
    int count = word.size()-begin;
    for(int i=0; i<count; ++i)
        assert(next_unused(word[i+begin], 'A'+i, used));
}

template<class func_type>
void doit(int n, func_type func) {
    bool used['Z'+1] = {};
    std::string word(n, '\0');
    reset_range(word, 0, used);
    for(;;) {
        func(word);
        //find next word
        int index = word.size()-1;
        while(next_unused(word[index], word[index]+1, used) == false) {
            if (--index < 0)
                return; //no more permutations
        }
        reset_range(word, index+1, used);
   }
}





template<class func_type> 
void generate(std::string& word, int length, const func_type& func) {
    for(char i='a'; i<='z'; ++i) {
        bool used = false;
        for(char c : word) {
            if (c==i) {
                used = true;
                break;
            }
        }
        if (used) continue;
        word.push_back(i);
        if (length==1) func(word);
        else generate(word, length-1, func);
        word.pop_back();
    }
}
template<class func_type> 
void generate(int length, const func_type& func) {
    std::string word;
    generate(word, length, func);
}







#include <ctime>
int main() 
{
    int nocheat=0;
    clock_t begin,end;
    
    begin = clock();
    doit(5, [&](const std::string& a){nocheat+=a.size();});
    end = clock();    
    std::cout << "nocheat " << nocheat << ".  unrolled in " << (end-begin) << " ticks.\n";
    
    begin = clock();
    generate(5, [&](const std::string& a){nocheat+=a.size();});
    end = clock();    
    std::cout << "nocheat " << nocheat << ".  nieve in " << (end-begin) << " ticks.\n";
}