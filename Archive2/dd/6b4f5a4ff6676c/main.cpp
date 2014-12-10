#include <iterator>
#include <iostream>
#include <vector>
#include <unordered_map>

class Foo
{
public:
    class Variant
    {
        typedef std::unordered_map<std::string, Variant*> object_container;
        typedef std::vector<Variant*> array_container;
        
        enum type
        {
            vundefined,
            vnull,
            vbool,
            vint,
            vflt,
            vstr,
            varr,
            vobj
        };
        
        union Union
        {
            bool bval;
            long ival;
            double fval;
            std::string sval;
            array_container aval;
            object_container oval;
            
            Union() {}
            ~Union() {}
        };
        
        // ====================================================
        
        Variant()
            : type(vundefined)
        {
        }
        
        Variant(std::string s)
            : type(vstr)
        {
            new (&data.sval) std::string(std::move(s));
        }
        
        Variant(array_container a)
            : type(varr)
        {
            new (&data.aval) array_container(std::move(a));
        }
        
        Variant(object_container o)
            : type(vobj)
        {
            new (&data.oval) object_container(std::move(o));
        }
        
        Variant(bool b)
            : type(vbool)
        {
            data.bval = b;
        }
        
        Variant(std::nullptr_t)
            : type(vnull)
        {
        }
        
        ~Variant()
        {
            switch (type)
            {
            case vstr: destruct(&data.sval); return;
            case varr: destruct(&data.aval); return;
            case vobj: destruct(&data.oval); return;
            default: return;
            }
        }
        
        // ====================================================
        
    private:
        template<typename T>
        void destruct(T* addr)
        {
            addr->~T();
        }
        
        type type;
        Union data;
    };
};

int main()
{
    std::cout << sizeof(Foo::Variant) << std::endl;
}
