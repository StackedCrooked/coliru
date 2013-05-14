#include <iostream>

     using namespace std;




     int main()

     {
 
		int counter, Montreal=0, Barcelona=0;
     // using do-While to make sure the user enters correct scores (not minus values)   
do {
    
    if(Montreal<0 || Barcelona<0)
    cout<< " Please enter correct scores\n";
    
    // entering the scores by the user
    cout<< " Montreal scores:\n";
    cin>> Montreal;

    cout<< " Barcelona scores:\n";
    cin>> Barcelona;
  } while (Montreal<0 || Barcelona<0);
                 

 	if  (Montreal  > Barcelona)  {

		 counter 

= 0;
 
		while ( counter < Montreal )

 		{

			 counter++;
 
			cout << " Montreal\t ";

 	

	}
         cout << "\n";
        
        counter = 0;
 
    	while ( counter < Barcelona )

 		{

			 

counter++;
 
			cout << " oooh-Barcelona\t ";

 		}
         cout << "\n";
         
 	}

else if (Barcelona  > 

Montreal)  {
 

	counter = 0;

		 while ( counter < Barcelona )
 
		{

			 counter++;

			 

cout << " Barcelona * \t ";
 
		}
        cout<< "\n";
        
        counter = 0;
 
        while ( counter < Montreal )

 		{

	

		 counter++;
 
			cout << " oooh-Montreal\t ";

 		}
         cout << "\n";
         
}

 
 else // if none of the teams won, they must be having the same scores

 {cout << "\\------/ "<< "\n";
 cout << " \\ G  / "<< "\n";
cout << "  \\  / "<< 

"\n"; 
cout << "   \\/ "<< "\n";
 
}


return 0;
}
