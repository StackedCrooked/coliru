#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

namespace local
{
    void test7(void); void test6(void); void test5(void); void test4(void); void test3(void); void test2(int&); void test1(void); template<typename A> void dumpMapReverse(const A &map);
}

int main(void)
{
    local::test7();
}

namespace local
{
    void test7(void)
    {
        double mine(123456789.876);
        cout << mine << endl;
        cout << scientific << mine << endl;
    }
    
    void test6(void)
    {
        class Me
        {
        private:
            int mine_;
        public:
            Me(void) = delete;
            Me(const int input) : mine_(input) { cout << "constructor-v: " << mine_ << endl; }
            Me(const Me& input) : mine_(input.mine_) { cout << "copy constructor: " << mine_ << endl; }
            Me(Me&& input) : mine_(move(input.mine_)) { cout << "move constructor: " << mine_ << endl; }
            
            // unused
            Me& operator=(const Me& input) { cout << "copy assignment: " << mine_ << endl; }
            Me& operator=(Me&& input) { cout << "move assignment: " << mine_ << endl; }
            
            virtual ~Me(void) { cout << "destructing: " << mine_ << endl; }
        };
        
        {
            vector<Me> objs;
            objs.reserve(3);    // important, otherwise things keep getting copied around/shifted
            objs.emplace_back(1551);
            objs.emplace_back(22);
            objs.emplace_back(33);
            
            cout << "\nAbout to destruct vector..." << endl;
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
        
        /* * /
        cout << "\nErase  \"3\" " << (mapIS.erase("3") ? "found" : "");
        cout << "\nErase \"44\" " << (mapIS.erase("44") ? "found" : "NOT found") << flush;
        /* */
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

namespace local
{
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
