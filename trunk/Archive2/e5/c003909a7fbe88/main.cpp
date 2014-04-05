#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include <sys/time.h>
#include <sys/resource.h>

using std::vector;

void error(const char *msg) {
    fprintf(stderr, "error: %s\n", msg);
    exit(1);
}


int f1(vector<int> &vec) {
    int sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        sum += vec[i];
        if (sum < 0) {
            error("negative");
        }
    }
    return sum;
}

int f2(vector<int> &vec) {
    int sum = 0;
    for (size_t i = 0, iEnd = vec.size(); i < iEnd; ++i) { //this line changed (iEnd)
        sum += vec[i];
        if (sum < 0) {
            error("negative");
        }
    }
    return sum;
}

typedef int (*TFuncPtr)(vector<int> &) ;
TFuncPtr Functions[2] = {f1, f2};

int output;

int main() {
    vector<int> v;
    for (size_t i = 0; i < 10000; ++i) {
        v.push_back(i);
    }

    rusage r1, r2;
    for (size_t iTest = 0; iTest < 20; ++iTest) {
        for (size_t iFunc = 0; iFunc < 2; ++iFunc) {
            getrusage(RUSAGE_SELF, &r1);
            for (size_t k = 0; k < 200000; ++k) {
                output += Functions[iFunc](v);
            }
            getrusage(RUSAGE_SELF, &r2);
            long long user_time = (r2.ru_utime.tv_usec - r1.ru_utime.tv_usec) + 1e6*(r2.ru_utime.tv_sec - r1.ru_utime.tv_sec);
            long long sys_time = (r2.ru_stime.tv_usec - r1.ru_stime.tv_usec) + 1e6*(r2.ru_stime.tv_sec - r1.ru_stime.tv_sec);;
            std::cout << "[" << iFunc << "] user: " << user_time << " ms; system: " << sys_time << " ms; total: " << (user_time + sys_time) << " ms\n";
        }
        std::cout << std::endl;
    }
}
