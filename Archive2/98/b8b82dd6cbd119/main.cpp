#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include <chrono>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
typedef std::chrono::high_resolution_clock clockh;
typedef std::chrono::duration<unsigned long long, std::nano> ms;

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

string build_string_1(const string &a, const string &b, const string &c)
{
    string out = a + b + c;
    return out;
}

string build_string_1a(const string &a, const string &b, const string &c)
{
    string out;
    out.resize(a.length()*3);
    out = a + b + c;
    return out;
}

string build_string_1b(const string &a, const string &b, const string &c)
{
    return a + b + c;
}

string build_string_2(const string &a, const string &b, const string &c)
{
    string out = a;
    out += b;
    out += c;
    return out;
}

string build_string_2a(const string &a, const string &b, const string &c)
{
    string out;
    out.reserve(a.length() * 3);
    out += a;
    out += b;
    out += c;
    return out;
}

string build_string_3(const string &a, const string &b, const string &c)
{
    string out;
    out = a;
    out.append(b);
    out.append(c);
    return out;
}

string build_string_3a(const string &a, const string &b, const string &c)
{
    string out;
    out.reserve(a.length() * 3);
    out.append(a);
    out.append(b);
    out.append(c);
    return out;
}


string build_string_4(const string &a, const string &b, const string &c)
{
    stringstream ss;

    ss << a << b << c;
    return ss.str();
}


char *build_string_5(const char *a, const char *b, const char *c)
{
    char* out = new char[strlen(a) * 3+1];
    strcpy(out, a);
    strcat(out, b);
    strcat(out, c);
    return out;
}



template<typename T>
size_t len(T s)
{
    return s.length();
}

template<>
size_t len(char *s)
{
    return strlen(s);
}

template<>
size_t len(const char *s)
{
    return strlen(s);
}



void result(const char *name, unsigned long long t, const string& out)
{
    cout << left << setw(22) << name << " time:" << right << setw(10) <<  t;
    cout << " nanosec   (per character: " 
         << fixed << right << setw(8) << setprecision(2) << (double)t / len(out) << ")" << endl;
}

template<typename T>
void benchmark(const char name[], T (Func)(const T& a, const T& b, const T& c), const char *strings[])
{
    //unsigned long long t;
    std::chrono::time_point<std::chrono::high_resolution_clock> t;

    const T s1 = strings[0];
    const T s2 = strings[1];
    const T s3 = strings[2];
    t = clockh::now();
    //t = rdtsc();
    T out = Func(s1, s2, s3);
    //t = rdtsc() - t; 
    auto t1 = clockh::now();

    if (len(out) != len(s1) + len(s2) + len(s3))
    {
        cout << "Error: out is different length from inputs" << endl;
        cout << "Got `" << out << "` from `" << s1 << "` + `" << s2 << "` + `" << s3 << "`";
    }
    unsigned long long asd = ms(t1-t).count();
    result(name, asd, out);
    //result(name, t, out);
}


void benchmark(const char name[], char* (Func)(const char* a, const char* b, const char* c), 
               const char *strings[])
{
    unsigned long long t;

    const char* s1 = strings[0];
    const char* s2 = strings[1];
    const char* s3 = strings[2];
    t = rdtsc();
    char *out = Func(s1, s2, s3);
    t = rdtsc() - t; 

    if (len(out) != len(s1) + len(s2) + len(s3))
    {
        cout << "Error: out is different length from inputs" << endl;
        cout << "Got `" << out << "` from `" << s1 << "` + `" << s2 << "` + `" << s3 << "`";
    }
    result(name, t, out);
    delete [] out;
}


#define BM(func, size) benchmark(#func " " #size, func, strings ## _ ## size)


#define BM_LOT(size) BM(build_string_1, size); \
    BM(build_string_1a, size); \
    BM(build_string_1b, size); \
    BM(build_string_2, size); \
    BM(build_string_2a, size); \
    BM(build_string_3, size); \
    BM(build_string_3a, size); \
    BM(build_string_4, size); \
    BM(build_string_5, size);

int main()
{
    //cout << "Hello World" << endl; 
    //cout << sizeof(boost::gregorian::date) << endl;
    //cout << sizeof(int) << endl;
   
    //return 0;

    const char *strings_small[]  = { "Abc", "Def", "Ghi" };
    const char *strings_medium[] = { "abcdefghijklmnopqrstuvwxyz", 
                                     "defghijklmnopqrstuvwxyzabc", 
                                     "ghijklmnopqrstuvwxyzabcdef" };
    const char *strings_large[]   = 
        { "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 

          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc"

          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc" 
          "defghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc", 

          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
        };

    for(int i = 0; i < 5; i++)
    {
        BM_LOT(small); 
        BM_LOT(medium);
        BM_LOT(large);
        cout << "---------------------------------------------" << endl;
    }
}