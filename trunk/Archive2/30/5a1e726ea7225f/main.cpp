// C++ for Polynomial equations: derived based on 邢雲路(Xin Yunlu)'s pi = 3.126
//                                           下廉           益從方          正實
//                               (b*b*b*b) - 6*a*d*(b*b) - 9*d*d*d*(b) + 9*a*a*d*d = 0   
//      四庫全書(787册/730頁) 古今律曆考卷六十九     
// 2014 March 20  Aurthor : Mr Lam/ Yee Din(林貽典)  Email: yeedlam@yahoo.com

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
 
#include <cmath>

//---------------------------------
const double  d = 116.845;       // d = 周天徑，授時曆的 pi = 3 時, d = 121.75 用於 pi = 3.126  d = 365.2575/3.126 = 116.845
const double  Ref_dd = 0;        // Ref_dd = 上廉，用於授時曆時，Ref_dd = d*d; 以邢雲路新的多項弍推算, Ref_dd = 0
const double  Ref_ddd = 9*d*d*d; // Ref_ddd = 益從方，用於授時曆時，Ref_ddd = d*d*d；以邢雲路新的多項弍推算, Ref_ddd = 9*d*d*d

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
  printf("Sun_deg\thalf_arc  \tsum_b\t\tRed_XD360\t\tSunRed_Lat360\tTheoYR_Diff\t\tTheoSunRed_Lat\n");
  printf("\t\t\t\t\t(Red_XD360 - Sun_deg)\n");
  printf("============================================================");
  printf("==============================================================\n");
 
double  YellowRed_XRef = d/2;     // (d/2) = 半徑(黄赤道大弦)
double  YellowRed_YRef = 53.3645;
 
double  Sun_deg = -1.0;
double  y;
int m,i;
for (m = 0; m - 1 < 90; m ++)
{
          Sun_deg = Sun_deg + 1;
  double  half_arc = Sun_deg * 365.2575/360;     // half_arc = 黄道半弧背
  double  Ref_ad = 6*half_arc *d;                // Ref_ad = 下廉，用於授時曆時，Ref_ad = 2*half_arc*d
  double  PosReal = 9*half_arc*half_arc * d*d;   // PosReal = 正實，用於授時曆時，PosReal = half_arc*half_arc*d*d
 
  double  NetReal[] = {PosReal, 0, 0, 0, 0};
  double  div = Ref_ddd;                         // div = 下法
  double  b[] = {0,0,0,0,0,0};
  double  sum_b = 0;
  for (i = 0; i-1 < 4; i++)
  {
    y = NetReal[i]/div;      
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
 
  double  ad = Ref_ad - sum_b*sum_b - (sum_b + b[i])*(sum_b + b[i]);
 
  double  div = (Ref_ddd - dd)+ ad*Next_b; 

    NetReal[i+1] = NetReal[i] - b[i] * div ;
 
    sum_b = sum_b + b[i];
  };
  printf("%3.0f\t%3.6f", Sun_deg, half_arc);
  printf("\t%3.6f", sum_b);
//------------------------------------------------------ 
  double  YellowRed_X = YellowRed_XRef - sum_b;
  double  YellowRed_XY = YellowRed_X * YellowRed_YRef;
  double  YellowRed_Y = YellowRed_XY/YellowRed_XRef;
 
  //double  b_square = sum_b * sum_b;
  //double  b_Diff = b_square/d;
  //double  half_aX = half_a - b_Diff;  
  double  half_aX = sqrt(sum_b*(d-sum_b));
  double  half_aX2 = half_aX*half_aX;
  double  YellowRed_Y2 = YellowRed_Y * YellowRed_Y; 
  double  Red_X = sqrt(half_aX2 + YellowRed_Y2);
 
  //double  half_XRed = half_aX * YellowRed_XRef/Red_X;
 
  double  Red_S = YellowRed_Y * YellowRed_XRef/Red_X;
 
  double  Red_b = d/2.0 - Red_S;
  double  Red_Diff = Red_b * Red_b/d;
  //double  Red_XD = half_XRed + Red_Diff;
  double  Red_XD = sqrt(d*Red_b) + Red_Diff/3.0;
  double  Red_XD360 = Red_XD * 360/365.2575;
 
  printf("   \t%2.6f(%2.6f)", Red_XD360, Red_XD360 - Sun_deg); 
//--------------------------------------------------------
  double  YellowRed_b = d/2 - Red_X;
  double  YellowRedArc = YellowRed_X * Max_XRef/YellowRed_XRef;
  double  Arc_Diff = YellowRed_b * YellowRed_b/d;
  double  SunRed_Lat = YellowRedArc + Arc_Diff;
  double  SunRed_Lat360 = SunRed_Lat * 360/365.2575;
  printf("\t%2.6f", SunRed_Lat360);  
//-------------------------------------------
  double  Ref_degree = 90 - Sun_deg;
  double  TheoYR_Diff = Ref_degree - 180/pi * atan(tan(Ref_degree* pi/180) * cos(23.55647 * pi/180));
  double  TheoSunRed_Lat = 180/pi * asin(sin(Ref_degree * pi/180) * sin(23.55647 * pi/180));
  printf("\t%2.6f[%2.6f]\t%2.6f[%2.6f]\n", 
        TheoYR_Diff, TheoYR_Diff -(Red_XD360 - Sun_deg), TheoSunRed_Lat, TheoSunRed_Lat - SunRed_Lat360);
  if (Sun_deg/10 == int(Sun_deg/10)){printf("\n");}
 }
}

