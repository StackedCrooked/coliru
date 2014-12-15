#include <iostream>

class Hen {

    public:
        class Nest {

        private: void private_member() const { std::cout << "Hen::Nest::access_private_member()\n" ; }

        public:
            class Egg {

                public: void access_nest( const Nest& n ) { n.private_member() ; };
            };
        };
};

int main()
{
    Hen::Nest nest ;
    Hen::Nest::Egg egg ;
    egg.access_nest(nest) ;
}
