#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <cmath>



#include <boost/chrono.hpp>
#define STATIC_PROFILER_START(name, label) \
    static Profiler::Data profiler##name = Profiler::Data(label); \
    boost::chrono::steady_clock::time_point start##name = boost::chrono::high_resolution_clock::now();
                
#define STATIC_PROFILER_END(name) \
    boost::chrono::duration<long long,boost::nano> duration##name = boost::chrono::high_resolution_clock::now() - start##name; \
    profiler##name += duration##name; 
                
namespace Profiler{
    struct Data{
        Data(const std::string& name) : time(0), name(name), count(0) {}                                                                     
        Data(const std::string& name, const boost::chrono::nanoseconds& time) : time(time), name(name), count(0) {}                           
        template <typename Duration>                                                                                               
        Data& operator+=(const Duration& amount){                                                                                  
            time += boost::chrono::duration_cast<boost::chrono::nanoseconds>(amount);                                                 
            ++count;                                                                                                               
            return *this;
        }
        ~Data(){
    		std::cout << name << ": " << time.count()/1000000. << " milliseconds (" << count << " calls) average: " << time.count()/1000000./count << " milliseconds" << std::endl;                     
        }
        boost::chrono::nanoseconds time;
        std::string name;                                                                                                          
        size_t count;
    };      
}               



#if 0
float InvSqrt (float x){
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    // x = x*(1.5f - xhalf*x*x);
    return (float)x;
}
#endif

const int N = 100000;
class A{
    int a;
    
};

class A2{
    int a;
    public:
    void* operator new(const std::size_t s){
        static void* ptr = malloc(N * sizeof(A2));
        static int count = 0;
        
        return ptr + sizeof(A2) * (count++);
    }
};

int main(int argc, char* argv[])
{
    STATIC_PROFILER_START(a, "a")
    for (int i = 0; i< N; ++i){
        A* p = new (A);   
    }
    STATIC_PROFILER_END(a)
    
    
    STATIC_PROFILER_START(a2, "a2")
    for (int i = 0; i< N; ++i){
        A2* p = new (A2);   
    }
    STATIC_PROFILER_END(a2)
    return 0;
}


