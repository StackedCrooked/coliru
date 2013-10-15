#include <stdio.h>

/* Die 10 Eingabe-Leitungen werden durch je ein einzelnes Bit  */
/* im Eingabewort repraesentiert; die nachfolgenden Funktionen */
/* extrahieren dieses Bit; der Wahrheitswert steht ab jetzt    */
/* allein im untersten Bit.                                    */

unsigned Input_0(unsigned b) { return 1u & (b >> 0); }
unsigned Input_1(unsigned b) { return 1u & (b >> 1); }
unsigned Input_2(unsigned b) { return 1u & (b >> 2); }
unsigned Input_3(unsigned b) { return 1u & (b >> 3); }
unsigned Input_4(unsigned b) { return 1u & (b >> 4); }
unsigned Input_5(unsigned b) { return 1u & (b >> 5); }
unsigned Input_6(unsigned b) { return 1u & (b >> 6); }
unsigned Input_7(unsigned b) { return 1u & (b >> 7); }
unsigned Input_8(unsigned b) { return 1u & (b >> 8); }
unsigned Input_9(unsigned b) { return 1u & (b >> 9); }

/* Insgesamt 9 UND-Gatter auf der linken Seite, von oben nach   */
/* unten gezaehlt ist das oberste And_0, das mittlere (= das    */
/* einzige mit drei Eingaengen) ist And_4, das unterste And_8.  */
/* Die Eingabeleitungen werden nun entsprechend der Schaltung   */
/* miteinander verknuepft.                                      */

unsigned And_0(unsigned b) { return  Input_0(b) && Input_1(b); }
unsigned And_1(unsigned b) { return  Input_1(b) && Input_2(b); }
unsigned And_2(unsigned b) { return  Input_2(b) && Input_3(b); }
unsigned And_3(unsigned b) { return  Input_0(b) && Input_3(b); }
unsigned And_4(unsigned b) { return  Input_4(b) && Input_6(b) && Input_5(b); }
unsigned And_5(unsigned b) { return  Input_5(b) && Input_6(b); }
unsigned And_6(unsigned b) { return  Input_9(b) && Input_7(b); }
unsigned And_7(unsigned b) { return !Input_7(b) && Input_8(b); }
unsigned And_8(unsigned b) { return  Input_8(b) && Input_9(b); }

/* Insgesamt 10 ODER-Verknüpfungen auf der rechten Seite, von  */
/* oben nach unten gezaehlt ist das oberste Or_0, das unterste */
/* Or_10. Die Eingaenge sind mit den Ausgaengen der Und-Gatter */
/* beschaltet, in einem Fall auch direkt mit einem Input_.     */
/* Noch steht der Wahrheitswert allein im untersten Bit.       */

unsigned Or_0(unsigned b) { return  And_0(b) ||  And_2(b); }
unsigned Or_1(unsigned b) { return  And_1(b) ||  And_8(b); }
unsigned Or_2(unsigned b) { return  And_1(b) ||  And_3(b); }
unsigned Or_3(unsigned b) { return !And_2(b) ||  And_3(b); }
unsigned Or_4(unsigned b) { return  And_5(b) ||  And_4(b); }
unsigned Or_5(unsigned b) { return !And_4(b) ||  And_6(b); }
unsigned Or_6(unsigned b) { return  And_6(b) ||  And_5(b); }
unsigned Or_7(unsigned b) { return  And_7(b) || !And_6(b); }
unsigned Or_8(unsigned b) { return  And_6(b) ||  And_8(b); }
unsigned Or_9(unsigned b) { return  And_7(b) ||  Input_9(b); }

/* Hier werden die einzelnen Ergebnisse (reprasentiert durch das */
/* unterste Bit) abschliessend zu einem Gesamtwort verbunden, so */
/* dass diese wie in der ursprünglichen Eingabe angeordnet sind. */

unsigned Output(unsigned b) {
    return (Or_0(b) << 0)
	     | (Or_1(b) << 1)
	     | (Or_2(b) << 2)
	     | (Or_3(b) << 3)
	     | (Or_4(b) << 4)
	     | (Or_5(b) << 5)
	     | (Or_6(b) << 6)
	     | (Or_7(b) << 7)
	     | (Or_8(b) << 8)
	     | (Or_9(b) << 9)
	     ;
}

/* Hilfsfunktion zur Ausgabe der 10 Bits eines Bitmusters. */

void showbits(unsigned v, const char* z) {
	for (int i = 10; i-- > 0;) {
		printf("%d ", (v & (1u<<i)) >> i);
	}
	printf("%s", z);
}

#if 0
int main() {
	for (unsigned input = 0; input < 1024; ++input) {
		showbits(input, "=> ");
		showbits(Output(input), "\n");
	}
	printf("--------------\n");
}
#else
char input[10][5] = {
	"0101",
	"0010",
	"0011",
	"1001",
	"0110",
	"0100",
	"0101",
	"0011",
	"0100",
	"0010"
};
char output[10][5];

unsigned xdigit(const char *s) {
	unsigned result = 0;
	for (; *s; ++s) {
		result <<= 1;
		if (*s == '1')
			result |= 1;
	}
	return result;
}

int main() {
	for (int i = 0; i < 4; ++i) {
		unsigned in = {0};
		for (int j = 0; j < 10; ++j) {
			if (input[j][i] == '1')
				in |= 1<<j;
		}
		unsigned out = Output(in);
		for (int j = 0; j < 10; ++j) {
			output[j][i] = (out & (1<<j)) ? '1' : '0';
		}
	}
	for (int j = 0; j < 10; ++j) {
		printf("(%X) %s %2s %s (%X)\n",
			xdigit(input[j]), input[j],
			(j==5 ? "=>" : ""),
			output[j], xdigit(output[j]));
	}
}
#endif
