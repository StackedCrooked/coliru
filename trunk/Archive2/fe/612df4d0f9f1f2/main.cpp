    #include <iostream>
    #include <cmath>
    #include <string>
    
    using namespace std;
    
    struct Cross
    {
        double xvalue[12], yvalue[12];
    
        void setCrossCord()
        {
            for (int i=0; i<12; i++)
            {
                cout << "Please enter x-ordinate of pt " << i << ": "; 
                double xVal, yVal;
                cin >> xVal;
                xvalue[i] = xVal;
                cout << endl;
                cout << "Please enter y-ordinate of pt " << i << ": ";
                cin >> yVal;
                yvalue[i] = yVal;
                cout << endl;
            }
        }
    
        double computeArea()
        {
            int points = 12;
            int running_total = 0;
    
            for (int i=0; i<12-1; i++)
            {
              running_total = (xvalue[i]*yvalue[i+1]) - (xvalue[i+1]*yvalue[i]);  //cross calculation of coord in a cross 
            }                                                                     //(x1*y2)-(y1*x1)
    
            running_total = (xvalue[points-1]*yvalue[0]) - (xvalue[0]*yvalue[points-1]);   // traverse back to the origin point
                                                                                           // (xn*y1)-(yn*x1)
    
            double area = abs(running_total / 2); //purpose of absolute is to make sure result is positive. 
                                          //polygon are specified in counter-clockwise order (i.e. by the right-hand rule), then the area will be positive.
    
            return (area);
        }
    
    };
    int main()
    {
        Cross cross;
        string shapetype;
    
        cout << "enter shape type: " << endl;
        cin >> shapetype;
    
        if(shapetype == "cross")
        {
            cross.setCrossCord();
        }else
        {
            cout << "error" << endl;
        };
    
        cout << "area of cross is: " << cross.computeArea() << endl;
    }
    
