class Alien { public: void poison() ; } ; 

class Monster
{
      class Alien; // this declares the nested class Monster::Alien 
      
      friend  void Alien::poison(); // *** error: incomplete type 'Monster::Alien' (declared, but not defined)
      
      friend  void ::Alien::poison(); // fine: the class '::Alien' has been defined
      
      class Alien { public: void poison() ; } ; // defines the nested class Monster::Alien
      
      friend void Alien::poison(); // fine: the class 'Monster::Alien' has been defined
      friend void Monster::Alien::poison(); // fine: same as above
};

class A
{
    friend class B ; // this is a friend declaration; it is not a declaration of class B
    B* pointer = nullptr ; // *** error: unknown type name 'B'. 'B' does not name a type
};

int main()
{
}