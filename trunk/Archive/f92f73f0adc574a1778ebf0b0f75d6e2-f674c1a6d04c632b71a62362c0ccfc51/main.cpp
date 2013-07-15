#include <iostream>
#include <functional>


template <typename MyFriend>
struct Benefits {
     friend MyFriend;
     
    private:
     void HotSex () {
         std::cout << "Oh yes~\n";
     }
};

struct ThePhD;

struct Tomalak : public Benefits<ThePhD> {

    
};

struct ThePhD {
    
    void GoForIt ( Tomalak& t ) {
        t.HotSex();
    }
};

int main ( int argc, char* argv[] ) {
    Tomalak tomalak_so_sexy;
    ThePhD thephd_so_horny;
    
    thephd_so_horny.GoForIt( tomalak_so_sexy );
    
}