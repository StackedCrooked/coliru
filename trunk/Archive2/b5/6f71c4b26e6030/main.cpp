struct tittays {
   int tits;

   void dostuff () {
      [ &tits ] () { }; // legal?
   };
};

int main () {
    tittays t;
    t.dostuff();
}