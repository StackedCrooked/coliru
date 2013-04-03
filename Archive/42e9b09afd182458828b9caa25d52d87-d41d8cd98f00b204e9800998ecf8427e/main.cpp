#include<iostream.h>
#include<math.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<sdio.h>
void draw_ellipsoid()
{
     int arr[4];
     int xrad=2000;
     int yrad=500;
     int zrad=1000;
     for(double i=0;i<=90;i=i+1)
     {
     double phi=((3.14159)/180)*i;
	 for(double j=0 ;j<90;j=j+0.005)
	 {
		   double theta,x,y,z;
	       theta=((3.14159)/180)*j;
	       x=xrad*cos(phi)*cos(theta);
	       y=yrad*sin(theta)*cos(phi);
	       z=zrad*sin(phi);
	       putxyz(int(x),-int(y),(int)z,arr,BLUE);
	       putxyz(int(x),-int(y),-(int)z,arr, BLUE);
	       putxyz(-int(x),-int(y),(int)z,arr,MAGENTA);
	       putxyz(-int(x),-int(y),-(int)z,arr,MAGENTA);
	 }
     }
     for(  i=0;i<=90;i=i+1) //0.5
     {
	       double phi=((3.14159)/180)*i;
	 for(double j=0;j<90;j=j+0.005)//0.01
	 {
		   double theta,x,y,z;
	       theta=((3.14159)/180)*j;
	       x=xrad*cos(phi)*cos(theta);
	       y=yrad*sin(theta)*cos(phi);
	       z=zrad*sin(phi);
	       putxyz(int(x),int(y),(int)z,arr,GREEN);
	       putxyz(int(x),int(y),-(int)z,arr,GREEN);
	       putxyz(-int(x),int(y),-(int)z,arr,RED);
	       putxyz(-int(x),int(y),(int)z,arr,RED);
	 }
     }
}

void main()
{
    clrscr();
      int gd=DETECT,gm;
      initgraph(&gd,&gm,"c:\\tc\\bgi");
      DRAW3DFRAME();
      cleardevice();
      draw_ellipsoid();
      getch();
      closegraph();
}
