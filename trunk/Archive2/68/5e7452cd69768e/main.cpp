// C++  for calculating Ref_parameters in Adam Schall
// Solving polynomials equations based on pi = 3  
//      ååº«å¨æ¸ 787å(730é ) å¤ä»å¾æ­´è å·69     
// 2013 April 10  Aurthor : Mr Lam/ Yee Din(æè²½å¸)  Email: yeedlam@yahoo.com

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
 
#include <cmath>

//---------------------------------
const double  d = 116.845;  // for pi = 3.126
const double  Ref_dd = 0;  //d*d;
const double  Ref_ddd = 9*d*d*d;

const double  Max_XRef = 23.71; 
const double  pi = 3.1415926;

int main()
{  
  printf("t\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\n");
  printf("------------------------------------------------------------------------\n");
  printf("  d\tRef_dd = d*d\tRef_ddd = d*d*d\n");
  printf("%2.3f\t%2.4f\t%2.6f\n", d, Ref_dd, Ref_ddd);
  printf("\n===========================================================");
  printf("===============================================================\n");
  printf("degree\thalf_a  \tsum_b\t\tRed_XD360\t\tSunRed_Lat360\tTheoYR_Diff\t\tTheoSunRed_Lat\n");
  printf("\t\t\t\t\t(Red_XD360 - degree)\n");
  printf("============================================================");
  printf("==============================================================\n");
 
double  YellowRed_XRef = d/2;
double  YellowRed_YRef = 53.3645;
 
double  degree = -1.0;
double  y;
int m,i;
for (m = 0; m - 1 < 90; m ++)
{
          degree = degree + 1;
  double  half_a = degree * 365.2575/360;
  double  Ref_ad = 6*half_a *d;
  double  PosReal = 9*half_a*half_a * d*d;
 
  double  NetReal[] = {PosReal, 0, 0, 0, 0};
  double  ddd_ad = Ref_ddd;
  double  b[] = {0,0,0,0,0,0};
  double  sum_b = 0;
  for (i = 0; i-1 < 4; i++)
  {
    y = NetReal[i]/ddd_ad;      
    if (y > 1){ b[i] =(int)y/1.0; }
    if (y < 1){ b[i]=(int)(10*y)/10.0; }

    if (y < 0.1)
    { 
       if (y > 0.01){ b[i]= (int)(100*y)/100.0;}
    }
 
    if (y < 0.01)
    {
       if (y > 0.001){ b[i]= (int)(1000*y)/1000.0;}
     }
 
    if (y < 0.001)
    {
        if (y > 0.0001){ b[i]= (int)(10000*y)/10000.0;}
    }
 
    if (y < 0.0001){ b[i]= y;}

  double  Next_b = 2 * sum_b + b[i];
  double  dd = Ref_dd * Next_b;
 
  double  ad = Ref_ad - sum_b*sum_b -(sum_b + b[i])*(sum_b + b[i]);
 
double  ddd_ad = (Ref_ddd - dd)+ ad*Next_b; 

    NetReal[i+1] = NetReal[i] - b[i] * ddd_ad ;
 
    sum_b = sum_b + b[i];
  };
  printf("%3.0f\t%3.6f", degree, half_a);
  printf("\t%3.6f", sum_b);
//------------------------------------------------------ 
  double  YellowRed_X = YellowRed_XRef - sum_b;
  double  YellowRed_XY = YellowRed_X * YellowRed_YRef;
  double  YellowRed_Y = YellowRed_XY/YellowRed_XRef;
 
  double  b_square = sum_b * sum_b;
  double  b_Diff = b_square/d;
 
  //double  half_aX = half_a - b_Diff;  
  double  half_aX = sqrt(sum_b*(d-sum_b));
  double  half_aX2 = half_aX*half_aX;
  double  YellowRed_Y2 = YellowRed_Y * YellowRed_Y; 
  double  Red_X = sqrt(half_aX2 + YellowRed_Y2); 
 
  double  half_XRed = half_aX * YellowRed_XRef/Red_X;
 
  double  Red_S = YellowRed_Y * YellowRed_XRef/Red_X;
 
  double  Red_b = d/2.0 - Red_S;
  double  Red_Diff = Red_b * Red_b/d;
  double  Red_XD = half_XRed + Red_Diff;
  double  Red_XD360 = Red_XD * 360/365.2575;
 
  printf("   \t%2.6f(%2.6f)", Red_XD360, Red_XD360 - degree); 
//--------------------------------------------------------
  double  YellowRed_b = d/2 - Red_X;
  double  YellowRedArc = YellowRed_X * Max_XRef/YellowRed_XRef;
  double  Arc_Diff = YellowRed_b * YellowRed_b/d;
  double  SunRed_Lat = YellowRedArc + Arc_Diff;
  double  SunRed_Lat360 = SunRed_Lat * 360/365.2575;
  printf("\t%2.6f", SunRed_Lat360);  
//-------------------------------------------
  double  Ref_degree = 90 - degree;
  double  TheoYR_Diff = Ref_degree - 180/pi * atan(tan(Ref_degree* pi/180) * cos(23.55647 * pi/180));
  double  TheoSunRed_Lat = 180/pi * asin(sin(Ref_degree * pi/180) * sin(23.55647 * pi/180));
  printf("\t%2.6f[%2.6f]\t%2.6f[%2.6f]\n", 
        TheoYR_Diff, TheoYR_Diff -(Red_XD360 - degree), TheoSunRed_Lat, TheoSunRed_Lat - SunRed_Lat360);
  if (degree/10 == int(degree/10)){printf("\n");}
 }
}

