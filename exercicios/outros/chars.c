#include <stdio.h>

int main() {
	char c;

	c = getchar(); // leitura de caractere
	
	while (c != EOF) { // enquanto a entreda não terminar
		if (c == ' ')
			c = '_';
		
		putchar(c);
		
		c = getchar();
	}

	return(0);
}
