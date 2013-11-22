#include <iostream>
#include <regex>
#include <string>
#include <cstring>
#include <iomanip>

#ifdef _DEBUG
const int content_length = 1000;
#else
const int content_length = 100000;
#endif


int manual(int, const char* first, const char* last) {
    int result=0;
    const char* it=first;
    while((it=strstr(it, "CXP-"))!=NULL) {
        if (last-it<8) break;
        int len = 4;
        if (isdigit(it[4])!=0 && isdigit(it[5])!=0 && isdigit(it[6])!=0 && isdigit(it[7])!=0) {
            if (last-it>=9 && isdigit(it[8]))
                len = 9;
            else
                len = 8;
            result += len;
        } 
        it += len;
    }
    return result;
}

int regex1(std::regex_constants::syntax_option_type syntax, const char* first, const char* last) {
    std::regex r("CXP-\\d\\d\\d\\d\\d?", syntax);
    std::regex_iterator<const char*> it(first, last, r, std::regex_constants::match_default), end;
    int result=0;
    for ( ; it!=end; ++it)
        result += it->length(0);
    return result;
}

int regex2(std::regex_constants::syntax_option_type syntax, const char* first, const char* last) {
    std::regex r("CXP-\\d{4,5}", syntax);
    std::regex_iterator<const char*> it(first, last, r, std::regex_constants::match_default), end;
    int result=0;
    for ( ; it!=end; ++it)
        result += it->length(0);
    return result;
}

template<class func_type>
void do_test(func_type&& func, const char* name, std::regex_constants::syntax_option_type syntax, const char* first, const char* last)
{
    std::cout<<std::setw(30)<<std::left<<name<<": "<<std::flush;
    clock_t begin = clock();
    int ret = func(syntax, first, last);
    clock_t end = clock();
    clock_t dur = end-begin;
    std::cout <<"nocheat="<<ret<<" dur:"<<dur<<'\n'<<std::flush;
}

void add_random_string(std::string& str) {
    int count = rand()%100;
    for(int i=0; i<count; ++i)
        str.push_back(rand()%95+32);
}

std::string random_cxp_text() {
    std::cout << "generating random text... ";
    clock_t begin = clock();
    std::string str;
    str.reserve(content_length*100);
    add_random_string(str);
    int value;
    for(int i=0; i<content_length; ++i) {
        value = (rand()%17+1)*1000 + rand()%1000;
        str += "CXP-";
        str += std::to_string(value);
        add_random_string(str);
    }
    clock_t end = clock();
    clock_t dur = end-begin;
    std::cout <<" dur:"<<dur<<'\n'<<std::flush;
    return str;
}


int __cdecl main() {
    try {
        using namespace std::regex_constants;
        std::cout << "test searching for (CXP-\\d{4,5})\n";
        std::string content = random_cxp_text();
        const char* first = &content[0];
        const char* last = first+content.size();
        do_test(manual, "strstr + isdigit", ECMAScript, first, last);
        do_test(regex1, "CXP-\\d\\d\\d\\d\\d?", ECMAScript, first, last);
        do_test(regex2, "CXP-\\d{4,5}", ECMAScript, first, last);
        do_test(regex1, "CXP-\\d\\d\\d\\d\\d? (optimized)", ECMAScript|optimize, first, last);
        do_test(regex2, "CXP-\\d{4,5}(optimized)", ECMAScript|optimize, first, last);
        return 0;
    } catch(const std::exception& exc) {
        std::cerr<<exc.what();
        return 1;
    }
}

/*
test searching for (CXP-\d{4,5})
generating random text...  dur:473
strstr + isdigit              : nocheat=2557551 dur:13
CXP-\d\d\d\d\d?               : nocheat=2557551 dur:7166
CXP-\d{4,5}                   : nocheat=2557551 dur:3516
CXP-\d\d\d\d\d? (optimized)   : nocheat=2557551 dur:7285
CXP-\d{4,5}(optimized)        : nocheat=2557551 dur:3763
*/