#include <stdio.h>

void interschimb1(int a, int b) {
	int aux = 0;
	aux = a;
	a = b;
	b = aux;
}

int main()
{
	int x = 9; int y = 7;
	printf("x=%d, y=%d", x, y);
	interschimb1(x, y);
	printf("x=%d, y=%d", x, y);
	return 0;
}