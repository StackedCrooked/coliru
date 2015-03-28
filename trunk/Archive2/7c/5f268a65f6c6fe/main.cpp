#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

namespace local
{
    class Me;
    void test0(void); template<typename A> void dumpMapReverse(const A &map);
}
int main(void) { local::test0(); }

namespace local
{
    void test0(void)
    {
        string s("Hello" "Guy");
        s += '!';
        
        cout << s << '\t' << s.length() << endl;
    }
    
    void test24(void)
    {
        vector<string> myStrings;
        myStrings.emplace_back("Hello" "Joe");
        
        vector<string> myStrings2{ myStrings.cbegin(), myStrings.cend() - 1 };
        cout << myStrings2.size() << endl;
    }
    
    void test23(void)
    {
        string mine("1020304");
        string::size_type pos(0);
        auto pos2(pos);
        while (string::npos != (pos2 = mine.find("0", pos)))
        {
            cout << "Here: " << mine.substr(pos, pos2 - pos) << endl;
            pos = pos2 + 1;
        }
        
        cout << "Last: " << mine.substr(pos) << endl;
    }
    
    void test22(void)
    {
        string test("test");
        cout << test.substr(1) << endl;
        
        
        int myInt;
        auto myTuple(make_tuple(1330, 2.6, 'a'));
        tie(myInt, ignore, ignore) = myTuple;
        cout << myInt << endl;
        
        auto myTuple2(tie(myTuple));
        /*
        // no idea...
        tie(myInt, ignore, ignore) = myTuple2;
        cout << myInt << endl;
        */
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
    void test21(void)
    {
        {
            unordered_map<string, Me> test;
            cout << "here-1" << endl;
            test["here"];
            cout << "here-2" << endl;
        }
        cout << "here-3" << endl;
    }
    
    void test20(void)
    {
        /** /
        char *s1 = "hi1";           // deprecated conversion from string constant to char*
        const char *s2 = "hi2";
        char const *s3 = "hi3";

        char * const s4 = "hi4";    // deprecated conversion from string constant to char*

        char const * const s5 = "hi5";
        const char * const s6 = "hi6";
        
        printf("%s\n%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5, s6);
        // */
    }
    
    struct MeMine
    {
        string hi_;
        int bye_;
        void Print(const string &descr) const { cout << descr << ": " << hi_ << ": " << bye_ << endl; } 
    };
    void callMe(MeMine aa)
    {
        aa.Print(" In-1");
        aa.bye_ += 10;
        aa.Print(" In-2");
    }
    void test19(void)
    {
        MeMine me;
        me.hi_ = "hi there";
        me.bye_ = 12;
        
        me.Print("Out-1");
        callMe(me);
        me.Print("Out-2");
    }
    
    void test18(void)
    {
        int what(0);
        what += 0x02 + 0x10;
        cout << what << endl;
        what <<= 2;
        cout << what << endl;
        
        cout << boolalpha;
        what = 1;
        for (auto ii(0); 3 > ii; ++ii) { cout << bool(0x04 & (what <<= 1)) << endl; }
    }
    
    void test17(void)
    {
        ostringstream stream1;
        stream1 << "Size: " << 111 << ends;
        cout << stream1.str().size() << "|" << stream1.str() << "|" << endl;
        stream1 << ends;
        cout << stream1.str().size() << "|" << stream1.str() << "|" << endl;
        
        return;
        
        
        ostringstream test;
        test << "hi" << endl;
        test << "bye";
        cout << test.str() << '.' << endl;
    }
    
    void test16(void)
    {
        vector<string> vc(2);
        vc.front() = "hi";
        
        cout << vc.front() << '|' << vc.back() << endl;
    }
    
    void test15(void)
    {
        int i1(1);
        int i2(move(i1));
        string s1("2");
        string s2(move(s1));
        
        printf("...int:\t- %d\t- %d\nstring:\t- %s\t- %s\n", i1, i2, s1.c_str(), s2.c_str());
        cout << "...int:\t- " << i1 << "\t- " << i2 << "\nstring:\t- " << s1 << "\t- " << s2 << endl;
    }
    
    Me retVal(void)
    {
        return Me(1);
    }
    
    void test14(void)
    {
        {
            cout << "before" << endl;
            Me&& haHa(retVal());
            cout << "after" << endl;
            Me haHa2(haHa);
        }
        cout << "no scope" << endl;
    }

    void test13(void)
    {
        {
            unique_ptr<Me[]> p(new Me[2]);
            p[1] = 22;
            cout << endl;
            const auto p2(new Me[2]); // these objects are leaked... memory-leaked! -- 'auto' can also be 'Me*'
            p2[1] = 22;
            
            cout << "\nObjects falling out of scope..." << endl;
        }
        cout << "Done.\n" << endl;
    }
    
    void test12(void)
    {
        {
            shared_ptr<Me> p3;
            {
                auto p1(make_shared<Me>(1)); // count is 1
        		{
        			shared_ptr<Me> p2(p1); // count is 2
        			{
        				p3 = p2; // count is 3
        			} // count goes back down to 2
        		} // count goes back down to 1
            }
            cout << "Gonna delete..." << endl;
        } // // here the count goes to 0 and the object is deleted.
        cout << "Deleted\n" << endl;
        
        {
            unique_ptr<Me> p1(new Me{ 2 }); // count is 1
            p1.reset(new Me{ 4 });
            p1.reset();
            cout << "Gonna delete..." << endl;
        } // // here the count goes to 0 and the object is deleted.
        cout << "Deleted\n" << endl;
    }
    
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
        // I don't get why Me can be declared after this void test9, but others (i.e., void test 12) need Me defined above them?
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
    
    void test8(void)
    {
        cout << 1 << endl;
        Me mine1(retVal());
        cout << 2 << endl;
        auto mine2(retVal());
        cout << 3 << endl;
        Me mine3 = retVal();
        cout << 4 << endl;
        auto mine4 = retVal();
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
