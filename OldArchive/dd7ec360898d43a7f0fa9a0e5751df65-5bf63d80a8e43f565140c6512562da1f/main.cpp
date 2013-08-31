// hello clever programmers, would you like to play a game?
// where's the bug?
// by 0xabad1dea :)

#include <stdio.h>
#include <string.h>

int main() {
      char input[16] = "stringstring!!!";
	char output[8];
	
	//so this will leave it not terminated//
	strncpy(output, input, 8);
	//but this will fix it right??/
	output[7] = '\0';
	
	//so what happens here?//
	printf("%s\n", output);
	
	return 0;	
	
}

// HINT: the behavior of this program depends on whether your
// compiler has turned ON or OFF a certain genuine ANSI C feature!

// also, modern stack protectors will keep this from being
// usefully exploitable, but that's besides the point