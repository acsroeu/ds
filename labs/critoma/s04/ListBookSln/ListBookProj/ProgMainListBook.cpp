#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Carte
{
	int isbn;
	char* den;
	int anpub;
};

struct Nod
{
	Carte info;
	Nod* next;
};




Nod* insNodInceputStiva(Nod* v, Carte* pc) {
	Nod* nou = (Nod*)malloc(1 * sizeof(Nod));
	//nou->info.isbn = pc->isbn;
	//nou->info.den = pc->den;
	//nou->info.anpub = pc->anpub;
	nou->info = *pc;
	nou->next = v;
	return nou;
}

void afisNoduriStiva(Nod* head) {
	//Nod* t = head;
	//while(t) {
	//}
	while(head) {
		printf("\n isbn = %d, den = %s, anpub = %d", head->info.isbn, head->info.den, head->info.anpub);
		head = head->next;
	}
}

int main(int argc, char** argv)
{
	Nod* varf = NULL;
	Carte artc;
	char tbuf[10];

	printf("isbn = "); scanf("%d", &artc.isbn);
	while(artc.isbn != 0)
	{
		printf("den = "); scanf("%s", &tbuf);
		artc.den = (char*)malloc(sizeof(char) * (strlen(tbuf) + 1));
		strcpy(artc.den, tbuf);
		
		printf("anpub = "); scanf("%d", &artc.anpub);

		varf = insNodInceputStiva(varf, &artc);

		printf("isbn = "); scanf("%d", &artc.isbn);
	}

	afisNoduriStiva(varf);

	return 0;
}









