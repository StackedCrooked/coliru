#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstddef>


struct FakeOne{
    int field;    
};

struct A{
    void go(){
        auto k = nullptr;
        //auto k = FakeOne();
        
        auto o = [&k]{
                struct m{
                    nullptr_t get( std::true_type, nullptr_t &){
                        return nullptr;
                    }
                    
                    auto get(std::false_type, decltype(k) &k){                                  // swap to "FakeOne" do the trick. Why it even goes here?
                        return k.field;
                    }
                    
                };
                return m().get(
                    std::integral_constant<bool, 
                                           std::is_same<decltype(k), std::nullptr_t>::value
                    >(),
                    k
                );
            }();    
    }
};

int main()
{
    A().go();
}
