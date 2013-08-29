#include <stdlib.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstring>
#include <string>

class FooCStr {
private:
char str1_[15];
char str2_[16];
char str3_[16];
public:
FooCStr() {
        char str1[] = "903612342354";
        char str2[] = "123456789012345";
        char str3[] = "123456789012345";
        strcpy(str1_,str1);
        strcpy(str2_,str2);
        strcpy(str3_,str3);
}
};

class FooStr {
private:
std::string str1_;
std::string str2_;
std::string str3_;
public:
FooStr() :
        str1_("903612342354"),
        str2_("123456789012345"),
        str3_("123456789012345") {
}
};

int main(int argc, char** argv) {
        if(argc < 2) {
                std::cout << "Usage: "<< argv[0] << " NumObjects\n";
                return  0;
        }

        std::vector<FooCStr*> *foo_vector = new std::vector<FooCStr*>();
        uint32_t cpt = 0, max = atoi(argv[1]);
        timespec tv;
        tv.tv_sec = 0;
        tv.tv_nsec = 0;

        clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tv);

        for(cpt = 0; cpt<max; ++cpt) {
                foo_vector->push_back(new FooCStr());
                if(cpt > 0 && cpt%10000000 == 0) {
                        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tv);
                        std::cout << "Object created: " << cpt << " Elapsed time "<< tv.tv_sec << "." << tv.tv_nsec << std::endl;
                }
        }

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tv);
        std::cout << "Time to create " << max <<" foo " << tv.tv_sec << "." << tv.tv_nsec << std::endl;
    	
        return 0;
}
