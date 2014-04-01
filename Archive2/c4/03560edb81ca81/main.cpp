// C++ for Polynomial equations: derived based on  pi = 3
//                                           下廉           益從方          正實
//                               (b*b*b*b) + (d*d - 2*a*d*(b*b) - d*d*d*(b) + a*a*d*d = 0   
//      四庫全書(787册/730頁) 古今律曆考卷六十九     
// 2014 March 22  Aurthor : Mr Lam/ Yee Din(林貽典)  Email: yeedlam@yahoo.com

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include <cmath>
//---------------------------------
const double  d = 121.75;       // d = 周天徑，授時曆的 pi = 3 時, d = 121.75 用於 pi = 3.126  d = 365.2575/3.126 = 116.845
const double  Ref_dd = d*d;     // Ref_dd = 上廉，用於授時曆時，Ref_dd = d*d; 以邢雲路新的多項弍推算, Ref_dd = 0
const double  Ref_ddd = d*d*d;  // Ref_ddd = 益從方，用於授時曆時，Ref_ddd = d*d*d；以邢雲路新的多項弍推算, Ref_ddd = 9*d*d*d

const double  SkyCircumference = 365.25;
const double  Sun_Y24Ref = 23.8070; //23.80691;   23.7785 from page(787-729);  23.8070 from page(787-717) 
const double  Center_Z24Ref = 56.0268;
const double  pi = 3.1415926;

int main()
{  
  printf("t\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\n");
  printf("-------------------------------------------------------------------------------------------------------------------------------\n");
  printf("  d\tRef_dd = d*d\tRef_ddd = d*d*d\n");
  printf("%2.3f\t%2.4f   \t%2.6f\t\tpi = %2.7f\t\tCenter_Z24Ref = %2.5f\n", d, Ref_dd, Ref_ddd, pi, Center_Z24Ref);
  printf("\t\t\t\t\t(d/2) = %2.5f\tSkyCircumference = %2.5f\tSun_Y24Ref = %2.5f\n",d/2,SkyCircumference,Sun_Y24Ref);
  printf("===============================================================================================================================\n");
  printf("黄道度\t周天/360\t   黄道矢度\t\t\t\t\t\t\t\t\t黄道半弧弦   赤道小股    赤道小弦\n");
  printf("deg360\tSun_arc\t   b  \t  S_arc360\t       Sun_Lat360   Theo_s_arc\t\tTheoSun_Lat\t\tSun_X    Center_Z  Center_Y\n");
  printf("\t\t\t    (dR=S_arc360-deg360)\t     (dR-TheoYR_Diff)\t(Sun_Lat360-TheoSun_Lat)\n");
  printf("===============================================================================================================================\n");
 
double  deg360 = -1.0;
double  y;
int m,i;
for (m = 0; m - 1 < 90; m ++)
{
          deg360 = deg360 + 1;
  double  Sun_arc = deg360 * SkyCircumference/360;        // Sun_arc = 黄道半弧背
  double  Ref_ad = 2*Sun_arc*d;                           // Ref_ad = 下廉，用於授時曆時，Ref_ad = 2*Sun_arc*d
  double  PosReal = Sun_arc*Sun_arc * d*d;                // PosReal = 正實，用於授時曆時，PosReal = Sun_arc*Sun_arc*d*d 
  double  NetReal[] = {PosReal, 0, 0, 0, 0};
  double  div = Ref_ddd;                                   // div = 下法
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
  printf("%3.0f\t%2.5f", deg360, Sun_arc);
  printf("   %2.5f", b);//---------------------------------------------------------------------------- 
  double  Center_X = d/2 - b;                         // 頁787-733：術以黄道矢(b)減周天半徑(d/2)，餘為黄赤道小弦(Center_X)
  double  Center_X_Z24Ref = Center_X * Center_Z24Ref; //            以黄赤道大股(Center_Z24Ref)乘之
  double  Center_Z = Center_X_Z24Ref/(d/2);           //            以黃赤道大弦(d/2)而一，為黄赤道小股(Center_Z)
 
  double  bb = b * b;                             
  double  Sun_arcDiff = bb/d;           
  double  Sun_X = Sun_arc - Sun_arcDiff;              //            以黄道背弦差減黄道度，餘為黄道半弧弦(Sun_X)(黄道度即半弧背) 
  
  double  Sun_XX = Sun_X*Sun_X;                       //            置黄道半弧弦自之
  double  Center_ZZ = Center_Z*Center_Z;              //            黄赤道小股自之 
  double  Center_Y = sqrt(Sun_XX + Center_ZZ);        //            相併，以平方開之，得赤道小弦(Center_Y)
  
  double  Sun_XRef = Sun_X*(d/2.0);                   //            置黄道半弧弦(Sun_X)(亦為赤道小股)，以半徑(d/2)乘之(半徑即赤道大弦)
  double  SW = Sun_XRef/Center_Y;                     //            以赤道小弦(Center_Y)而一，為赤道大股(SW)，又為赤道半弧弦
  
  double  Center_ZRef = Center_Z *(d/2.0);            //            置黄道小股(Center_Z)(亦為赤道橫勾)，以赤道大弦乘之
  double  Center_W = Center_ZRef/Center_Y;            //            以赤道小弦而一，為赤道大句(Center_W)
 
  double  WH_b = (d/2.0) - Center_W;                  //            以減半徑，餘為赤道横矢
  double  S_arcDiff = WH_b * WH_b/d;                  //            自之，以周天徑(d)而一，得半背弦差(s_arcDiff)
  double  S_arc = SW + S_arcDiff;                     //            減半弧背，餘為半弧弦
  double  S_arc360 = S_arc * 360/SkyCircumference; 
  printf("   %2.5f(%2.5f)", S_arc360, S_arc360 - deg360); //----------------------------------------------------------------------------
  double  SY_b=(d/2.0)-Center_Y;//頁787-737(二至前後黄道距赤道內外度):  置半徑以減赤道小弦，餘為赤道二弦差，一云赤道矢(SY_b)
                                               // 置半徑減黄道矢，餘為黃赤道弦，一為立股，若相近曰句，
  double  Sun_Y = Center_X * Sun_Y24Ref/(d/2.0); // 以二至內外黄赤道半弧弦乘之，以半徑六十度八七五而一，得黃赤道小弧弦(Sun_Y)
  double  Sun_S_arcDiff = SY_b * SY_b/d;       //   黄赤道內外半弧弦，一云黃道小句，置黄赤道小弧矢自之，以周天圓徑而一，為半背弦差 
  double  Sun_Lat = Sun_Y + Sun_S_arcDiff;     //   以加黄赤道半背弦，即為黄赤道內外半弧背(Sun_Lat)
  double  Sun_Lat360 = Sun_Lat * 360/SkyCircumference;
  printf("\t%2.5f", Sun_Lat360);  //------------------------------------------------------------------------------------------------------
  double  Ref_degree = 90 - deg360;
  double  Theo_s_arc = 90-180/pi * atan(tan(Ref_degree* pi/180) * cos(23.5328 * pi/180));
  double  TheoYR_Diff = Theo_s_arc - deg360;
  double  TheoSun_Lat = 180/pi * asin(sin(Ref_degree * pi/180) * sin(23.5328 * pi/180));
  printf("    %2.5f[%2.5f]\t%2.5f[%2.5f]\t%2.5f   %2.5f\t%2.5f\n", 
        Theo_s_arc, (S_arc360-deg360)-TheoYR_Diff, TheoSun_Lat, Sun_Lat360-TheoSun_Lat, Sun_X,Center_Z,Center_Y );
  if (deg360/10 == int(deg360/10)){printf("\n");}
 }
}