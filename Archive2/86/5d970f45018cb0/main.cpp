
// C++ Shoushi Solar equation of center program  Author: Mr Lam Yee Din


#include <iostream>
using namespace std;
#include <cmath>        // or math.h

const double Tropical_year = 365.2425;
const double half_year = Tropical_year/2;
const double Converted_Unit = 365.2425/360;
const double moon_speed_factor = 1;

enum Status{LagStart, LagEnd, LeadStart, LeadEnd}; 
struct Status_type
{
  char *sun;
  char *moon;
};


class Ref_data 
{
        private:
               Status SunStatus, MoonStatus;

        protected:
              int calculated_year;
              int total_months;
              double Required_sun_ref;

              double sun_days;

              double sun_add_minus;
              double sun_sum;
              double sun_difference;

              double solar_days;

        public:
              Ref_data(int m,int n) 
              { 
                calculated_year = m;
                total_months = n;

                      Required_sun_ref = 0;
 
                      sun_days = 0;
                   
                      sun_add_minus = 0;
                      sun_sum = 0;
                      sun_difference = 0;       

                      cout << "Constructing Ref_data\n"; 
               }
  
              ~Ref_data() 
               { 
                      cout << "Destructing Ref_data\n"; 
               }

        void check_SunStatus(double Required_sun_ref, double& sun_days, int& SunStatus)
             {
               SunStatus = LagStart;
               sun_days = 0;
               
              if (Required_sun_ref < half_year)
                 {
                  SunStatus = LagStart;
                  sun_days = Required_sun_ref;
                       if (Required_sun_ref > 93.712025)
                        {
                        sun_days = half_year  - sun_days;                       
                        SunStatus = LagEnd;
                        }
                  }

             if (Required_sun_ref > half_year )
               {
                 SunStatus = LeadStart;
                 sun_days = Required_sun_ref - half_year ; 
                           
                       if (sun_days > 88.909225)
                       {
                       sun_days = half_year - sun_days;
                       SunStatus = LeadEnd;
                       }  
                  }
               }

              void show_SunStatus(int SunStatus)
                  {
                   switch (SunStatus) 
                    {
                           case LagStart:
                                 cout << "SunLagStart";
                              break;

                           case LagEnd:
                                 cout << "SunLagEnd";
                              break;

                           case LeadStart:
                                 cout << "SunLeadStart";
                              break;

                           case LeadEnd:
                                 cout << "SunLeadEnd"; 
                               break;

                           default:
                                  cout << "no SunStatus";
                                break;
                          }
                  }

          void calculate_SunOffset(int SunStatus, double sun_days,
                                   int int_sun_days,
                                   double& sun_add_minus, double& sun_sum,
                                   double& sun_difference)
          {
            sun_add_minus = 0;
            sun_sum = 0;  
            sun_difference = 0;
            if (fmod(SunStatus, 3.0) == 0) // SunStaus = LagStart & LeadEnd
            {
             sun_add_minus = 484.8473 - (4.4362 + (0.0162 * (int_sun_days - 1)/2) * int_sun_days);
             sun_sum = (487.06 - (2.21 + 0.0027 * int_sun_days)* int_sun_days )* int_sun_days;
            }

            if (fmod(SunStatus, 3.0) > 0) // SunStatus = LagEnd & LeadStart
             {
              sun_add_minus = 510.8569 - (4.9386 + (0.0186 * (int_sun_days - 1)/2) * int_sun_days);
              sun_sum = (513.32 - (2.46 + 0.0031 * int_sun_days)* int_sun_days)* int_sun_days;
             }
              sun_difference = ((sun_days - int_sun_days) * sun_add_minus  + sun_sum) / 10000;
           }

};

         

class base2 {
protected:
  int k;
public:
  base2(int x) { 
     k=x; 
     cout << "Constructing base2\n"; 
  }
  ~base2() { 
     cout << "Destructing base2\n"; 
  }
};

class derived: public Ref_data, public base2 {
  int j;
public:
  derived(int m, int n, int x, int z): Ref_data(m,n), base2(x){ 
     j=z; 
     cout << "Constructing derived\n"; 
  }

  ~derived() { 
     cout << "Destructing derived\n"; 
  }
  void show() { 
     cout << calculated_year << " " << k << " " << j << "\n"; 
  }
  
};

int main()
{

  cout << "half_year = " << half_year;
  cout << endl;

       int calculated_year = 0;
       int total_months = 0;
 Ref_data year(calculated_year,total_months);

cout << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" 
<< "\tt" << "\tt" << "\tt" << endl

<< "--------------------------------------------------------------------------------------------------------\n"
<< "degree    Solar     Status      sum         sun_sum    sun           Tycho         Tycho_Converted\n"
<< "          day                   _add_minus            _difference   _Converted      deg min sec\n"
<< "--------------------------------------------------------------------------------------------------------\n";

      int SunStatus, degree;
      double Required_sun_ref, Required_sun_days, sun_days;
      int int_sun_days;
      double sun_add_minus, sun_sum, sun_difference;
      double Tycho_Converted, Tycho_minute, Tycho_second;
for (degree = 0; degree < 361; degree ++)
{
      Required_sun_ref = Converted_Unit * degree;
      Required_sun_days = Required_sun_ref;
      if ( Required_sun_ref > half_year)
      {
      Required_sun_days = Required_sun_ref - half_year;
      };

      cout << degree;
      cout << "\t";
      cout << Required_sun_ref << "\t  ";

      int SunStatus, int_sun_days;
      year.check_SunStatus(Required_sun_ref,sun_days, SunStatus);
 
    int_sun_days = int(sun_days);

    year.show_SunStatus(SunStatus);

    year.calculate_SunOffset(SunStatus, sun_days, int_sun_days,
                                 sun_add_minus, sun_sum, sun_difference);

     cout << "\t" 
          << sun_add_minus  
          << "\t    " 
          << sun_sum;

     if (sun_sum == 0)
     {
         cout << "    ";
     }

     cout << "\t" 
          << sun_difference;

     if (sun_sum == 0)
     {
         cout << "       ";
     }

     cout  << "     ";

     Tycho_Converted = sun_difference * (1/moon_speed_factor)* 0.082 * 24 *(30 + 28/60 + 37/3600)/60;   
     
     if (sun_sum == 0)
     {
         cout << "    ";
     }

     cout << Tycho_Converted << "\t  "
          << int(Tycho_Converted) << "d ";
    
     Tycho_minute = (Tycho_Converted - int(Tycho_Converted))* 60;
     cout << int(Tycho_minute) << "m ";

     Tycho_second = (Tycho_minute - int(Tycho_minute))* 60;
     cout << Tycho_second << "s "
          << endl;
      
}

   derived ob(3, 4, 5, 6);

  ob.show();

  return 0;
}
 



