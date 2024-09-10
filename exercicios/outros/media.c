#include <stdio.h>

int main () {

	int a, b;
	float c;
	
	printf("entre com o valor de a: ");
	scanf("%d", &a); // indica que o valor a ser recebido é decimal e que ele será alocado no endereço da memória da variável a

	printf("entre com o valor de b: ");
	scanf("%d", &b);

	c = (a + b) / 2.0; // evitar que o resultado não seja inteiro

	printf("a = %d, b = %d\n", a, b);
	printf("a media simples de a e b eh %f\n", c);

	return (0);
}
