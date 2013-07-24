#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <set>
#include <unordered_map>
#include <utility>
#include <list>

using namespace std;

namespace variables
{    
    time_t timer;
    struct tm t1; 
    struct tm t2;
    struct tm t3;
    
    //add to 24hr time
    struct tm t1_add; 
    struct tm t2_add;
    struct tm t3_add;
    
    double minutes;
    list<tm> times;
    pair<int,int> actualTime;
    unordered_map <int, pair<int,int>> map;
    int counter_actualTimes = 0;
    bool foundActualTime = false;
    bool foundMultipleActualTimes = false;
    
}


using namespace variables;

void initialise()
{
    
    int reading1_hr = 5;
    int reading1_min = 0;
    int reading2_hr = 12;
    int reading2_min = 0;
    int reading3_hr = 10;
    int reading3_min = 0;
          
    t1.tm_hour = reading1_hr;   t1.tm_min = reading1_min;  t1.tm_sec = 0; t1.tm_year=0; t1.tm_mon=0; t1.tm_mday=0;
    times.push_back(t1);
    t2.tm_hour = reading2_hr;   t2.tm_min = reading2_min; t2.tm_sec = 0; t2.tm_year=0; t2.tm_mon=0; t2.tm_mday=0;
    times.push_back(t2);
    t3.tm_hour = reading3_hr;   t3.tm_min = reading3_min; t3.tm_sec = 0; t3.tm_year=0; t3.tm_mon=0; t3.tm_mday=0;
    times.push_back(t3);
    
    t1_add.tm_hour = (reading1_hr + 12 );   t1_add.tm_min = reading1_min;  t1.tm_sec = 0; t1.tm_year=0; t1.tm_mon=0; t1.tm_mday=0;
    times.push_back(t1_add);
    t2_add.tm_hour = (reading2_hr + 12 );   t2_add.tm_min = reading2_min; t2.tm_sec = 0; t2.tm_year=0; t2.tm_mon=0; t2.tm_mday=0;
    times.push_back(t2_add);
    t3_add.tm_hour = (reading3_hr + 12 );   t3_add.tm_min = reading3_min; t3.tm_sec = 0; t3.tm_year=0; t3.tm_mon=0; t3.tm_mday=0;
    times.push_back(t3_add);
    
    
    
}


double isNegative(double s)
{
    return s<0 ? -s : s;
}

void addActualTime(tm currTime)
{
    if(actualTime.first == currTime.tm_hour && actualTime.second == currTime.tm_min){
        cout << "duplicate" << endl;
    }
    else if(foundActualTime){
        foundMultipleActualTimes = true;    
    }
    else{
        actualTime.first = currTime.tm_hour; actualTime.second = currTime.tm_min;
        foundActualTime = true;
    }
}

void validateActualTime(int index)
{
    list<tm>::iterator itlist;
    
    itlist = times.begin();
    advance(itlist, index); 
    tm currTime = *itlist;
    
    if(index < times.size()){
        for(int i = 0; i < times.size(); i++)
        {
            itlist = times.begin();
            advance(itlist, index); 
            tm currTime = *itlist;
            
            itlist = times.begin();
            advance(itlist, i);
            tm vectorTime = *itlist;
            if(currTime.tm_hour - vectorTime.tm_hour != 12
            && currTime.tm_hour > vectorTime.tm_hour)
            {
                minutes = isNegative(difftime(mktime(&currTime), mktime(&(vectorTime))))/60;
                unordered_map<int,pair<int,int>>::const_iterator itermap = map.find(minutes);
                if(itermap != map.end())
                {                  
                    if((map[minutes]).first == currTime.tm_hour 
                    && (map[minutes]).second == currTime.tm_min){
                        addActualTime(currTime);                  
                    }
                    
                    if((map[minutes]).first == vectorTime.tm_hour 
                    && (map[minutes]).second == vectorTime.tm_min){
                        addActualTime(vectorTime);                  
                    }
                }

                pair<int, int> timepair = make_pair(vectorTime.tm_hour, vectorTime.tm_min);
                pair<int, int> timepair2 = make_pair(currTime.tm_hour, currTime.tm_min);
                map[minutes] = timepair;
                map[minutes] = timepair2;
            }
        }

        index++;
        validateActualTime(index);
    }
}


int main()
{

    initialise();
    validateActualTime(0);
    if(foundMultipleActualTimes) {cout << "Look at the sun" << endl;}
    else{ cout << "The correct time is " << actualTime.first << ":" << actualTime.second << endl;}

} 


