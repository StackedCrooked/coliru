#include <array>
#include <atomic>
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

namespace local
{
    class Me;
    void test11(void); void test10(void); void test9(void); void test8(void); void test7(void); void test6(void); void test5(void); void test4(void); void test3(void); void test2(int&); void test1(void); template<typename A> void dumpMapReverse(const A &map);
}

int main(void)
{
    local::test11();
}

namespace local
{
    void test11(void)
    {
        auto t1 = chrono::high_resolution_clock::now();
        this_thread::sleep_for(chrono::milliseconds(87));
        auto t2 = chrono::high_resolution_clock::now();
        
        auto diff = t2 - t1;
        cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
    }
    
    void test10(void)
    {
        enum class MType
        {
            kMe = 0,
            kOther = 1
        };
        
        MType type(MType::kMe);
        
        switch (type)
        {
            case MType::kOther:
                cout << 1 << endl;
                break;
                
            default:
                break;
        }
        
        cout << "Something" << endl;
    }
    
    void test9(void)
    {
        {
//#define OLD_ARRAY
#ifdef OLD_ARRAY
            int vals[] { 1, 2, 3, 4, 5, 6};
            vector<Me> objs2(vals, vals + 7);
            cout << "\nAssigning..." << endl;
            objs2.assign(vals, vals + 5);
#else            
            array<int, 6> vals; /* vals.fill(-11); */
            vector<Me> objs2(vals.data(), vals.data() + 7);
            cout << "\nAssigning..." << endl;
            objs2.assign(vals.data(), vals.data() + 5);
#endif
            cout << "Done assigning.\n" << endl;
            
            // 7 is capacity() 
            objs2.reserve(7);   // [-inf,objs2.capacity()] -- nothing
            objs2.reserve(8);   // (objs2.capacity(),+inf] -- make a new, larger std::vector

            cout << "\nAbout to copy container..." << endl;
            const auto objs(objs2);
            cout << "Done copying container.\n" << endl;
            
            cout << "\nAbout to destruct containers..." << endl;
        }
        cout << "Destructed.\n" << endl;
    }
    
    class Me
    {
    private:
        unsigned long long mine_;
        unsigned long long setMine(void) { static atomic_ullong upper_; return ++upper_; }
    public:
        Me(void)                    : mine_(setMine())  { cout << "constructor()...: " << mine_ << endl; }
        Me(const int)               : mine_(setMine())  { cout << "constructor(int): " << mine_ << endl; }
        Me(initializer_list<int>)   : mine_(setMine())  { cout << "constructor(IL).: " << mine_ << endl; }
        Me(const Me& input)         : mine_(setMine())  { cout << "copy constructor: " << mine_ << "\tfrom: " << input.mine_ << endl; }
        Me(Me&& input)              : mine_(setMine())  { cout << "move constructor: " << mine_ << "\tfrom: " << input.mine_ << endl; }
        Me& operator=(const Me& input)                  { cout << "copy assignment.: " << mine_ << "\tfrom: " << input.mine_ << endl; return *this; }
        Me& operator=(Me&& input)                       { cout << "move assignment.: " << mine_ << "\tfrom: " << input.mine_ << endl; return *this; }
        
        virtual ~Me(void)                               { cout << "destructing.....: " << mine_ << endl; }
    };
    
    Me retValOptimization(void)
    {
        return Me(1);
    }
    void test8(void)
    {
        cout << 1 << endl;
        Me mine1(retValOptimization());
        cout << 2 << endl;
        auto mine2(retValOptimization());
        cout << 3 << endl;
        Me mine3 = retValOptimization();
        cout << 4 << endl;
        auto mine4 = retValOptimization();
    }
    
    void test7(void)
    {
        double mine(123456789.876);
        cout << mine << endl;
        cout << scientific << mine << endl;
    }
    
    void test6(void)
    {
        {
            vector<Me> objs;
            objs.reserve(4);    // important for std::vector, otherwise things keep getting copied around/shifted
            cout << "+ + add -- "; objs.emplace_back(1551);
            cout << "+ + add -- "; objs.emplace_back(22);
            cout << "+ + add -- "; objs.emplace_back(33);
            cout << "+ + add -- "; objs.emplace_back(44);
            cout << "+ + add -- "; objs.emplace_back(55);
            
            cout << "\nAbout to destruct container..." << endl;
        }
        cout << "Destructed.\n" << endl;
        
        return;

        {
            // stinks -- can't tell on failure using emplace_hint()
            map<int, int> objs;
            objs.emplace(1, 11);
            auto it(objs.emplace_hint(objs.begin(), 1, 111));
            cout << it->second << endl;
            return;
        }
    }
    
    void test3(void)
    {
        map<string, string> mapIS;
        
        cout << "Init 3, 4, 5." << mapIS["3"] << mapIS["4"] << mapIS["5"]
             << "\n\tResults:" << endl;
        dumpMapReverse(mapIS);
        
        
        mapIS.erase(begin(mapIS), begin(mapIS));    // does nothing
        
        //cout << "\nErase  \"3\" " << (mapIS.erase("3") ? "found" : "");
        //cout << "\nErase \"44\" " << (mapIS.erase("44") ? "found" : "NOT found") << flush;
        mapIS["4"] = "middle";
        cout << "\nForced 4 set."
             << "\n\tResults:" << endl;
        dumpMapReverse(mapIS);
        
        
        cout << endl;
        
        auto itL(mapIS.lower_bound("4"));
        cout << "std::map::lower_bound(\"4\") := \"4\"\n\t[" << itL->first << "] " << itL->second << endl;
        
        string testS("3");
        testS.append("\377\377\377");   //$c(255,255,255)
        auto itU(mapIS.upper_bound(testS));
        cout << "std::map::upper_bound(\"3\" + $c(255,255,255)) := \"4\"\n\t[" << itU->first << "] " << itU->second << endl;
    }
    
    void test5(void)
    {
        std::map<char,int> mymap;
        
        mymap['x']=1001;
        mymap['z']=2002;
        mymap['y']=3003;
        
        std::cout << "mymap contains:\n";
        
        std::pair<char,int> highest = *mymap.rbegin();          // last element
        
        std::map<char,int>::iterator it = mymap.begin();
        do
        {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }
    
    void test4(void)
    {
        cout << "|" << strncmp("1234", "123", 4) << "|" << endl;
        
        double testD{ -123456789012340000.0 };
        bool isNeg{ 0 > testD };
        long long *llp{ (long long*) &testD };
        long long ll{ *llp };
        
        if (isNeg)
        {
            assert(abs(ll) == -ll);
            ll = -ll;
        }
        
        printf("%c%llX", (isNeg ? 2 : 4), ll);
    }
    
    class A
    {
    public:
        int A_;
        A(void) : A_(0) {}
        A(const int in) : A_{in} {}
    };
    class B : public A
    {
    public:
        int B_;
        B(void) : A(1), B_{1} {}
    };
    
    void test2(int &result)
    {
        A testA;
        B testB;
        
        cout << "before slice" << endl;
        A test2 = testB;
        cout << "after slice" << endl;
        
        
        result = 0;
        result += testA.A_;
        result += testB.B_;
        result += test2.A_;
    }
    
    void test1(void)
    {
        std::map<std::string,int> my_map;
        
        my_map["y"] = 23;
        my_map["z"] = 24;
        my_map["w"] = 12;
        my_map["x"] = 11;
        
        /*
        auto itit(my_map.cbegin());
        advance(itit, 1);
        auto itit2(itit);
        advance(itit2, 2);
        my_map.erase(itit, itit2);
        */
        
        // use for() to limit scope of eraseAt variable
        for (const auto eraseAt(my_map.find("y")); my_map.cend() != eraseAt; )
        {
            my_map.erase(eraseAt);
            break;
        }
        
        dumpMapReverse(my_map);
    }
    
    template<typename A> void dumpMapReverse(const A &map)
    {
        for (auto eachEntry = map.crbegin(); map.crend() != eachEntry; ++eachEntry)
        {
            std::cout << (*eachEntry).first << " - " << (*eachEntry).second << std::endl;
        }
    }
}
