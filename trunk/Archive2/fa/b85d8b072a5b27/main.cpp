#include <stdio.h>

 char toUpper (char eingabe1) {


    if ('a'<= eingabe1 && eingabe1 <='z'){

		return eingabe1 -32;
	}


	if ('ä'== eingabe1)
				return  'Ä';
	if ('ü'== eingabe1)
				return  'Ü';
	if ('ö'== eingabe1)
				return  'Ö';
	return eingabe1;

}

int main (){

	setbuf(stdout, NULL);

	char eingabe1;

	printf("Geben Sie einen Buchstabe ein:\n");
	scanf("%c", &eingabe1);

	eingabe1 = toUpper (eingabe1);

	printf("Buchstabe gewechselt : %c\n", eingabe1);

    return 0;
}
