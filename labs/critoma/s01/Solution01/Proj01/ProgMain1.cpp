#include <stdio.h>

void interschimb1(int a, int b) {
	int aux = 0;
	aux = a;
	a = b;
	b = aux;
}

void interschimb2(int* pa, int* pb) {
	int aux = 0;
	aux = *pa;
	*pa = *pb;
	*pb = aux;
}

int main()
{
	int x = 9; int y = 7;
	printf("x=%d, y=%d", x, y);
	interschimb1(x, y);
	interschimb2(&x, &y);
	printf("x=%d, y=%d", x, y);
	return 0;
}