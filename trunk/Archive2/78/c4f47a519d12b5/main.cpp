#include <iostream>
#include <string>
#include <vector>
#include "graphics.h"
void efface_affiche(POINT A, POINT B)

{
    int i;
	i=1;
	
	
	while(i==1)
	{
	
	draw_fill_circle(A,25,rouge);
	wait_clic();
	fill_screen (black);
	
	draw_fill_circle(B,25,rouge);
	wait_clic();
	
	   	                      }}

int main ()
{
	init_graphics (1000,1000);
	
	POINT A,B;
	
	A.x=50;A.y=50;
	B.x=A.x+2;B.y=A.y+5;
	
	efface_affiche(A,B);
	
	
	wait_escape();
	exit(0);
}

