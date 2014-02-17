#include <iostream>
#include <string>

using namespace std;

int main()
{
   string myString[20] = {"A brief, often humerous narrative told to illustrate a moral","A brief, usually allegorical narrative that teaches a moral","A short narrative without a complex plot","A humerous short narrative that provides a wildly exaggerated version of events.","A traditional form of short narrative folklore, orignally transmitted orally, which features supernatural characters","A prose narrative too brief to be published in a separate volume-as novellas and novels frequently are","a narrative in which the main character, usually a child, undergoes an important experience that prepares him for adulthood","The main or central character in a narrative","The most significant character or force that opposes the protagonist in a narrative","The opening portion of a narrative.","The central struggle between two or more forces in a story","The introduction of a significant development in the central conflict between characters","The point in a narrative when the crucial action, decision or realization must take place","the moment of greatest intensity in a story, which almost inevitably occurs towards the end of the work","in plotting, the locial end or outcome of a unified plot, shortly following climax","an indication of events to come in a narrative","a scene relived in a character's memory","a moment of profound insight or revelation by which a character's life is greatly altered","A latin phrase meaning in the midst of things"};          
   
   string myAnswers[20] = {"fable","parable","tale","tall tale","fairy tale","short story","initiation story","protagonist","antagonist","exposition","conflict","complication","crisis","climax","conclusion","foreshadowing","flashback","epiphany","in mediax res"};
   
   string sInput;
   
   for(int i = 0; i < 19; i++)
   {
        cout << myString[i] << endl;
        cout << "Enter answer: ";
        cin >> sInput;
        
        if(sInput == myAnswers[i])
        {
            cout << "\nCorrect!" << endl;
        }
        else
        {
            cout << "\nURRRR Wrong! Answer is " << myAnswers[i] << endl;
        }
   }
   
   cout << myString[0];
   
   return 0;
}
