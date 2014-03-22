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

const double  Y24Ref = 23.71; 
const double  pi = 3.1415926;

int main()
{  
  printf("t\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\n");
  printf("--------------------------------------------------------------------------------------------------------------------------\n");
  printf("  d\tRef_dd = d*d\tRef_ddd = d*d*d\n");
  printf("%2.3f\t%2.4f   \t%2.6f\n", d, Ref_dd, Ref_ddd);
  printf("(d/2) = %2.5f\n",d/2);
  printf("==========================================================================================================================\n");
  printf("deg360\tSun_arc\t   b  \t   S_arc360\t       Sun_Lat360   TheoYR_Diff\t\tTheoSun_Lat\t\tCenter_W  Center_Z\n");
  printf("\t\t\t    (dR=S_arc360-deg360)\t     (TheoYR_Diff-dR)\t(TheoSun_Lat-Sun_Lat360)\n");
  printf("==========================================================================================================================\n");
 
double  Center_XRef = 53.3645;
 
double  deg360 = -1.0;
double  y;
int m,i;
for (m = 0; m - 1 < 90; m ++)
{
          deg360 = deg360 + 1;
  double  Sun_arc = deg360 * 365.2575/360;      // Sun_arc = 黄道半弧背
  double  Ref_ad = 6*Sun_arc*d;                 // Ref_ad = 下廉，用於授時曆時，Ref_ad = 2*Sun_arc*d
  double  PosReal = 9*Sun_arc*Sun_arc * d*d;    // PosReal = 正實，用於授時曆時，PosReal = Sun_arc*Sun_arc*d*d
 
  double  NetReal[] = {PosReal, 0, 0, 0, 0};
  double  div = Ref_ddd;                         // div = 下法
  double  b_[] = {0,0,0,0,0,0};
  double  sum_b = 0;
  for (i = 0; i-1 < 4; i++)
  {
    y = NetReal[i]/div;      
    if (y > 1){ b_[i] =(int)y/1.0; }
    if (y < 1){ b_[i]=(int)(10*y)/10.0; }

    if (y < 0.1)
    { 
       if (y > 0.01){ b_[i]= (int)(100*y)/100.0;}
    }
 
    if (y < 0.01)
    {
       if (y > 0.001){ b_[i]= (int)(1000*y)/1000.0;}
     }
 
    if (y < 0.001)
    {
        if (y > 0.0001){ b_[i]= (int)(10000*y)/10000.0;}
    }
 
    if (y < 0.0001){ b_[i]= y;}

  double  Next_b = 2 * sum_b + b_[i];
  double  dd = Ref_dd * Next_b;
 
  double  ad = Ref_ad - sum_b*sum_b - (sum_b + b_[i])*(sum_b + b_[i]);
 
  double  div = (Ref_ddd - dd)+ ad*Next_b; 

    NetReal[i+1] = NetReal[i] - b_[i] * div ;
 
    sum_b = sum_b + b_[i];
  };
  double b = sum_b;
  printf("%3.0f    %2.5f", deg360, Sun_arc);
  printf("\t  %2.5f", b);
//------------------------------------------------------ 
  double  Center_X = d/2 - b;        // 置周天半徑，內減去黄道矢度，餘為黄赤道小弦
  double  Center_XXRef = Center_X * Center_XRef;
  double  Center_Z = Center_XXRef/(d/2);
 
          double  bb = b * b;                         //  術用割圓法，以半弧背自之為半弧背冪
          double  arc_Diff = bb/d;                    //  original  Shoushi equation for arc_Diff
          double  Sun_X = Sun_arc - arc_Diff;         //  original  Shoushi equation for Sun_X
  
          Sun_X = sqrt(b*(d-b));                      //  Supposed modified by 邢雲路
  double  Sun_XX = Sun_X*Sun_X;
  double  Center_ZZ = Center_Z*Center_Z;
  double  Center_Y = sqrt(Sun_XX + Center_ZZ);
  
  double  Sun_XRef = Sun_X*(d/2.0);
  double  SW = Sun_XRef/Center_Y;
  
  double  Center_ZRef = Center_Z *(d/2.0);
  double  Center_W = Center_ZRef/Center_Y;
 
  double  WH_b = (d/2.0) - Center_W;
  double  S_arcDiff = WH_b * WH_b/d;                       // original Shoushi equation for S_arcDiff
          double  S_arc = SW + S_arcDiff;                  // original Shoushi equation for S_arc
          S_arc = sqrt(d*WH_b) + S_arcDiff/3.0;            // Supposed modified by 邢雲路
  double  S_arc360 = S_arc * 360/365.2575;
 
  printf("    %2.5f(%2.5f)", S_arc360, S_arc360 - deg360); 
//--------------------------------------------------------
  double  SY_b = (d/2.0) - Center_Y;
  double  Sun_Y = Center_X * Y24Ref/(d/2.0);
  double  Sun_S_arcDiff = SY_b * SY_b/d;
  double  Sun_Lat = Sun_Y + Sun_S_arcDiff;
  double  Sun_Lat360 = Sun_Lat * 360/365.2575;
  printf("\t%2.5f", Sun_Lat360);  
//-------------------------------------------
  double  Ref_degree = 90 - deg360;
  double  TheoYR_Diff = Ref_degree - 180/pi * atan(tan(Ref_degree* pi/180) * cos(23.55647 * pi/180));
  double  TheoSun_Lat = 180/pi * asin(sin(Ref_degree * pi/180) * sin(23.55647 * pi/180));
  printf("    %2.5f[%2.5f]\t%2.5f[%2.5f]\t%2.5f  %2.5f\n", 
        TheoYR_Diff, TheoYR_Diff-(S_arc360-deg360), TheoSun_Lat, TheoSun_Lat-Sun_Lat360, Center_W,Center_Z );
  if (deg360/10 == int(deg360/10)){printf("\n");}
 }
}

