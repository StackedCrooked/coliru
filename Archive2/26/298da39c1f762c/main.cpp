
#include <iostream>

class MyEnum {
    struct Alfa { constexpr operator int() const { return 0; } };
    struct Beta { constexpr operator int() const { return 1; } };
    int v;
public:
    constexpr static Alfa ALFA {};
    constexpr static Beta BETA {};
    MyEnum(const MyEnum&) = default;
    constexpr MyEnum(Alfa vv): v(vv) {}
    constexpr MyEnum(Beta vv): v(vv) {}
    constexpr MyEnum() : MyEnum(ALFA) {}
    operator int () const { return v; }
};

const char* normalize(std::string path) 
{
    std::cout << "executed   " << path << std::endl;
    //"foo//\\\bar////bar2///../.\bar2" -- foo/bar/bar2
    std::size_t found;
    std::size_t found2;
    std::size_t curchar = 0;
    std::string final;
    std::string buffer;
    bool notdone = true;

    while (notdone) {
        //std::cout << "loop" << std::endl;
        //find the current element
        // can be / or \ --
        found = path.find("/", curchar);
        found2 = path.find("\\",curchar);
        std::cout << "found " << found << std::endl;
        std::cout << "found2 " << found2 << std::endl;
    
        if (found != std::string::npos && found2 != std::string::npos) {
            if (found < found2){
                //read from the curchar to the slash
                if (curchar-found > 1){
                    buffer = path.substr(curchar,found-curchar-1);
                    //add to path
                    final = final + "/" + buffer;
                }
                curchar = found+1;
                //buffer will be the file/component
            }else{
                if (curchar-found2 > 1){
                    buffer = path.substr(curchar,found2-curchar-1);
                    //add to path
                    final = final + "/" + buffer;
                }
                curchar = found2+1;
            }
        }else if(found != std::string::npos){
            //std::cout << "loop2" << found == std::string::npos << std::endl;
            //std::cout << "loop2   " << path.substr(curchar, 1) << std::endl;
            if (curchar-found > 1){//
                buffer = path.substr(curchar,found-curchar-1);
                //add to path
                final = final + "/" + buffer;
            }
            curchar = found+1;
        }else if(found2 != std::string::npos){
            std::cout << "loop3" << std::endl;
            if (curchar-found2 > 1){
                buffer = path.substr(curchar,found2-curchar-1);
                //add to path
                final = final + "/" + buffer;
            }
            curchar = found2+1;
        }else{
            std::cout << "finishing" << std::endl;
            final = final + "/" + path.substr(curchar,path.size()-curchar);
            notdone = false;
        }
    }

    return final.c_str();
}




int main() {
  std::cout << normalize("test/") << std::endl;
}
