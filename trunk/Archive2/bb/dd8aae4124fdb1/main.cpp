#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

struct LifeCreator
{
   void Vivid()
   {
      cout << "Hello there!" << endl;
   }

   LifeCreator GiveMeR()
   {
      return LifeCreator();
   }

   void Yell()
   {
      cout << "This Is Fun!" << endl;
   }
};


template<typename T>
struct Talk
{
   void operator = (T words)
   {
      cout << words << endl;
   }
};

template<typename T>
T MeaningOfLife = &LifeCreator::Vivid;

template<typename T>
T&& RValueWorld = T().GiveMeR();

template<typename T>
T Translator = T();

int main()
{
   (static_cast<LifeCreator*>(0)->*MeaningOfLife<void (LifeCreator::*)()>)();
   RValueWorld<LifeCreator>.Yell();
   Translator<Talk<string>> = "This", Translator<Talk<string>> = "is" ,
   Translator<Talk<string>> = "so", Translator<Talk<string>> = "Auh~~";
}
