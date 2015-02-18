#include <stdio.h>

int main (void)
{
    // y= resultado.a= dividendo.b= mutiplica x
  float a=0;
  float b=0;
  float x=0;
  float y=0;
  printf("ingresar a");
  scanf("%F",&a);
  printf("ingresar b");
  scanf("%f",&b);
  printf("ingresar x");
  scanf("%F",&x);
      y=b*x/a;
  printf ("y es: %f" );
	return 0;
}
   
#include <stdio.h>
int main (void)
{
  float perimetro=0;
  float radio=0;
  float pi=3.141592;
  printf("ingresar radio");
  scanf("%f",&radio);
  float perimetro_de_radio=radio+radio+radio+radio;
  float perimetro_de_circulo = pi*2*radio;
  printf("elperimetro del circulo es:%f y el radio de  es%f",perimetro_de_circulo,perimetro_de_radio);

  return 0;
}