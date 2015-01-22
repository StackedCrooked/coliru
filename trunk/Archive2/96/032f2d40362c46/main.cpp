


#include "CImg.h"
#include <iostream>
#include <math.h>

using namespace cimg_library;
using namespace std;







     bool defineSegmentColor(int v,char *str){
       bool bool_var = 0;

       if (str[0]=='b') {
    	bool_var = v<400?1:0;
	} else {
	    	bool_var = v>600?1:0;	
      	}

	return bool_var;
    }





      int main(int arg, char ** source) {
//	cout << "ExFile |file template| color border gradient" << endl;
//	cout << "Example: ./test myfile.jpg  |white| or |black|" << endl;

  	
 	CImg<unsigned char> image("lable.jpg"), vi(image.width(),image.height(),1,3,0);
	


	  

	int yr = 0, yg=0, yb=0;
	int t=0, t1=0, t2=0;
	int counter =0;
	int height = image.height();
	int width  = image.width();
	for(int w1=1; w1<width; w1++){
		for(int h1=1; h1<height; h1++){
			
			t = image(w1,h1,0,0);
			t1 = image(w1,h1,0,1);
			t2 = image(w1,h1,0,2);


			int 	radius = 0, 
				counter=1;
	
			//initialize var for generate matrix
			int minH=h1-(int)round(radius*0.5), 
			    minW=w1-(int)round(radius*0.5),
			    maxH=h1+(int)round(radius*0.5),
			    maxW=w1+(int)round(radius*0.5),		 
			    max_step=radius*2;
	

			if(maxH>height) maxH=height;
			if(maxW>width)	maxW=width;
			if(minH<=0)	minH=0;
			if(minW<=0)	minW=0;	

	
	
			for(int w=minW;w<=maxW;w++){
				for(int h=minH;h<=maxH;h++){
					yr+=image(w,h,0,0);
					yg+=image(w,h,0,1);
					yb+=image(w,h,0,2);		
					counter++;
				}
			}

			yr/=counter;
			yg/=counter;
			yb/=counter;
			counter=0;
	


			
			vi(w1,h1,0,0) = yr;
			vi(w1,h1,0,1) = yg;	
			vi(w1,h1,0,2) = yb;
			
				}
			}


		       int segment_c = 0xfe;

		
	/*		
			int coeff_gradient = 2.5, border_gradient=0x4f;
			for(int w1=1; w1<(int)image.width(); w1++){
					for(int h1=1; h1<(int)image.height(); h1++){
						int r = image(w1,h1,0,0);
						int g = image(w1,h1,0,1);
						int b = image(w1,h1,0,2);
						
						if(r*0.5>g && r*0.5>b) r=((250-r)*0.2)+r;
						if(g>r && g>b) g=((250-g)*0.2)+g;
						if(b>r && b>g) b=((250-b)*0.2)+b;
						
						vi(w1,h1,0,0) = r;
						vi(w1,h1,0,1) = g;	
						vi(w1,h1,0,2) = b;


/*
						int bl_color_mask = 80, wh_color_mask = 300;
						int r = (image(w1,h1,0,0)+image(w1,h1,0,1)+image(w1,h1,0,2))/3;

							vi(w1,h1,0,0) = image(w1,h1,0,0);
							vi(w1,h1,0,1) = image(w1,h1,0,1);	
							vi(w1,h1,0,2) = image(w1,h1,0,2);
				
						if(r<border_gradient){
							
							vi(w1,h1,0,0) = (image(w1,h1,0,0)+bl_color_mask)/coeff_gradient;
							vi(w1,h1,0,1) = (image(w1,h1,0,1)+bl_color_mask)/coeff_gradient;	
							vi(w1,h1,0,2) = (image(w1,h1,0,2)+bl_color_mask)/coeff_gradient;
						}
//*
					}
				}
*/


/*
	CImg<unsigned char> lable(source[1]);

	for(int w1=1; w1<(int)lable.width(); w1++){
		for(int h1=1; h1<(int)lable.height(); h1++){

			if( defineSegmentColor(lable(w1,h1,0,0)+lable(w1,h1,0,1)+lable(w1,h1,0,2), source[2]) ) {
				cout << lable(w1,h1,0,0)+lable(w1,h1,0,1)+lable(w1,h1,0,2) << endl;
				vi(w1+20, h1+10, 0, 0) = (250+vi(w1+20, h1+10, 0, 0))/2.8;
				vi(w1+20, h1+10, 0, 1) = (250+vi(w1+20, h1+10, 0, 1))/2.8;
				vi(w1+20, h1+10, 0, 2) = (250+vi(w1+20, h1+10, 0, 2))/2.8;



			}



		}
	}
*/

	vi.display();
	vi.save("t.jpg");
	

	  return 0;
}
      
//g++ -o i i.cpp -lX11 -lpthread
