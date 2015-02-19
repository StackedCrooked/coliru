#include <stdio.h>

int main (void)
{
    // y= resultado.a= dividendo.b= mutiplica  a X
  float a=0;
  float b=0;
  float x=0;
  float resultado=0;
  printf("ingresar a");
  scanf("%F",&a);
  printf("ingresar b");
  scanf("%f",&b);
  printf("ingresar x");
  scanf("%F",&x);
      resultado=b*x/a;
  printf ("valor y es: %f",resultado);
	return 0;
}
   
#include <stdio.h>
int main (void)
{
  float perimetro_de_circulo=0;
  float radio=0;
  float pi=3.141592;
  printf("ingresar radio");
  scanf("%f",&radio);
  float perimetro_de_radio=radio+radio+radio+radio;
  float perimetro_de_circulo = pi*2*radio;
  printf("elperimetro del circulo es:%f y el radio de  es%f",perimetro_de_circulo,perimetro_de_radio);

  return 0;
}