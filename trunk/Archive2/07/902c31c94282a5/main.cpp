#include <iostream>
#include <string>
#include <vector>

#include <memory>



template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

class animal {
    public:
    virtual void sound() = 0;
    virtual ~animal() {
        cout << "dtod animal" << endl;
    }
    virtual animal* clone() const = 0;
};

class cat : public animal {
        public:

    virtual void sound() {
        cout << "miau" << endl;
    };
    virtual ~cat() {
        cout << "dtod cat" << endl;
    };
    cat* clone() const {
        return new cat(*this);
    }
};

class dog : public animal {
        public:

    virtual void sound() {
        cout << "woff" << endl;
    };
    virtual ~dog() {
        cout << "dtod dog" << endl;
    };
    dog* clone() const{
        return new dog(*this);
    }
};


class mutant : public animal {
        public:
        
        typedef unique_ptr<animal> ptr;

    virtual void sound() {
                cout << "MUTANT:" << endl;
        for (auto& m : muts){
            cout << "   "; m->sound();
        }
    };
    virtual ~mutant() {
        cout << "dtod mutant" << endl;
    };
    
    void add(animal* a) {
                cout << "adding pointer" << endl;
        muts.push_back(ptr(a->clone()));
    };
    
    void add(animal *&& a) {
                        cout << "adding rvalue" << endl;
        muts.push_back(ptr(a));
    }
    
    
    mutant* clone()  const{
        auto m = new mutant();
        for (auto& c : muts) {
           // m->add(move(c.get()));
        }
        return m;
    }
    
    vector<ptr> muts;
};



/////
class object_t {
public:
    template <typename T>
    object_t(T x) : setlf_(make_shared<model<T>>(move(x))){}
    
    friend void draw(const object_t& x, ostream& out, size_t pos)
    {x.self_->draw(out, pos);}
    
private:
    struct concept_t {
        virtual ~concept_t() = default;
        virtual void draw_(ostream&, size_t) const = 0;
    };
    
    template <typename T>
    struct model : concept_t {
        model(T x) : data_(move(x)) {}
        virtual void draw_(ostream& out, size_t pos) const override
        { draw(data_, out, pos); }
        
        T data_;
    };
    
    shared_ptr<const concept_t> self_;
};


/////

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    mutant m;
    auto cp = new cat();
    cat cc;
    //m.add(cp);
    //m.add(cat());
    m.add(new cat);
    m.add(new dog);
    m.add(new dog);
    m.sound();
    cp->sound();
   /*
   unique_ptr<mutant> mp(new mutant);
    mp->add(mutant::ptr(new cat));
    mutant m;
    unique_ptr<cat> c(new cat);
    m.add(move(c));
    m.add(mutant::ptr(new dog));
    m.add(move(mp));
    m.sound();
    */
}

