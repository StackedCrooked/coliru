#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <functional>

using namespace std;

class IL {
  public:
   IL() {}
   ~IL() {}
   
   void Query(const string& q) {}
      
   template <typename... Args>
   bool Fetch(std::function<void(Args...)> callback) {
     
     if (sizeof... (Args) < GETFIELDCOUNT) {
       cout << "Invalid number of arguments. The query contains more fields!" << endl;
       return false;
     } else if (sizeof... (Args) > GETFIELDCOUNT) {
       cout << "Invalid number of arguments. The query contains less fields!" << endl;
       return false;
     } else {
        FetchInternal<Args...>(callback);
        return true;
     }     
   }
   
   template <typename... Args>
   void FetchInternal(std::function<void(Args...)> callback) {
       // This MUST be an initializer list, otherwise the order of GetField evaluations is undefined.
       // We MUST make sure that we evaluate GetField from the first argument to the last, since it's
       // implementation depends on it.
       const auto results = tuple<Args...>{ GetField<Args>()... };
       cout << "Doing the real fetch" << endl;
       //cout << result << endl;
   }  
   
   template <typename T> T GetField() const {
       T t;
       return t;
   }
  
   
  private:
    mutable int get_field_index = 0;
  
   const unsigned int GETFIELDCOUNT = 3;
   vector<string> field_1 = {"value_1", "value_2", "value_3"};
   vector<int> field_2 = {1,2,3};
   vector<double> field_3 = {.1,.2,.3};
};


   
   template <> string IL::GetField<string>()  const {
       cout << "GetField<string>" << endl;
       if (get_field_index++ != 0)
        cout << "INTERNAL ERROR" << endl;
        
       return field_1.at(0);
   }
   
   template <> int IL::GetField<int>() const {
       cout << "GetField<int>" << endl;
       if (get_field_index++ != 1)
        cout << "INTERNAL ERROR" << endl;
        
       return field_2.at(0);
   }
   
   template <> double IL::GetField<double>() const {
       cout << "GetField<double>" << endl;
       if (get_field_index++ != 2)
        cout << "INTERNAL ERROR" << endl;
       return field_3.at(0);
   }

typedef struct Object {
    Object(string f1, int f2, double f3) : f1(f1), f2(f2), f3(f3) {}
    string f1;
    int f2;
    double f3;
    
    friend ostream& operator<<(ostream& os, const Object& o) {
        os << "Object :" << o.f1 << " | " << o.f2 << " | " << o.f3;
        return os;
    }
} Object;


int main()
{
    IL il;    
    il.Query("SELECT bal bla");
     
    #if 0
    // The second approach
    // This is vector<tuple<string,int,long>>
    auto results = il.FetchAll<string,int,double>();
    
    // This is tuple<string,int,long>
    auto result = il.Fetch<string,int,double>();
    #endif
    
    // The third approach
    
//    vector<Object> results;
//    auto callback = [&results](string f1, int f2, double f3) -> void {
//        results.emplace_back(f1,f2,f3);
//    };
    
    //il.FetchAll<string,int,double>(callback);
    vector<Object> results;
    function<void(string,int,double)> callback =  
        [&results](string f1, int f2, double f3) -> void {
            cout << "Callback with " << f1 << " and " << f2 << " and " << f3 << endl;
        results.emplace_back(f1,f2,f3);
    };
    
    if (!il.Fetch<string,int,double>(callback))  {
        cout << "FAIL" << endl;    
    } else {
        cout << "OK" << endl;
        cout << results.at(0);
    }
    
    
    cout << "END" << endl;
    return 0;    
}
