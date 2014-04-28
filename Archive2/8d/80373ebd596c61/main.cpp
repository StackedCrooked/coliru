//a user defined type
class Widget{};
class Frobnicator{};

/////////////////////////////////////////////////////
// copied and reduced from boost/strong_typedef.hpp
#define CUSTOM_STRONG_TYPEDEF(T, D)                                 \
struct D                                                            \
    /*: boost::totally_ordered1< D           */                     \
    /*, boost::totally_ordered2< D, T        */                     \
    /*> >                                    */                     \
{                                                                   \
    T t;                                                            \
    explicit D(const T t_) : t(t_) {};                              \
    D(){};                                                          \
    D(const D & t_) : t(t_.t){}                                     \
    D & operator=(const D & rhs) { t = rhs.t; return *this;}        \
    D & operator=(const T & rhs) { t = rhs; return *this;}          \
    explicit operator const T & () const {return t; }               \
    explicit operator T & () { return t; }                          \
    /*bool operator==(const D & rhs) const { return t == rhs.t; } */\
    /*bool operator<(const D & rhs) const { return t < rhs.t; }   */\
};

CUSTOM_STRONG_TYPEDEF(Widget, Gadget)
CUSTOM_STRONG_TYPEDEF(Frobnicator, Normalcy)

void acceptWidget(Widget){}
void acceptGadget(Gadget){}
void acceptFrobnicator(Frobnicator){}
void acceptNormalcy(Normalcy){}

int main(){

    //make the two different types
    Widget w;
    Gadget g;

    //call a function that should ONLY accept Widgets
    acceptWidget(w); //works (good)
    acceptGadget(g);

    //acceptWidget(g); // Error
    //acceptGadget(w); // Error
    // but we can enjoy conversions if we summon them
    acceptWidget(static_cast<Widget&>(g));

    //more, unrelated, types with the very same macro
    Frobnicator f;
    Normalcy n;
    acceptFrobnicator(f);
    acceptNormalcy(n);
    
    
    class class_with_other_methods{
        public: void do_stuff(){return;}
    };
    
    CUSTOM_STRONG_TYPEDEF(class_with_other_methods, rename)

    class_with_other_methods a;
    rename b;

    a.do_stuff();
    b.do_stuff();

}
