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
	Carte* info;
	Nod* next;
};

Nod* insNodInceputStiva(Nod* v, Carte* pc) {
	Nod* nou = (Nod*)malloc(1 * sizeof(Nod));
	//nou->info.isbn = pc->isbn;
	//nou->info.den = pc->den;
	//nou->info.anpub = pc->anpub;
	nou->info = pc;
	nou->next = v;
	return nou;
}

void afisNoduriStiva(Nod* head) {
	//Nod* t = head;
	//while(t) {
	//}
	while(head) {
		printf("\n isbn = %d, den = %s, anpub = %d", head->info->isbn, head->info->den, head->info->anpub);
		head = head->next;
	}
}

void insNodInceputStiva(Nod** varf, Carte* infoUtil) {
	Nod* temp = (*varf);
	
	*varf = (Nod*)malloc(1*sizeof(Nod));
	(*varf)->info = infoUtil;
	(*varf)->next = temp;
}

void stergNodInceput(Nod** varf) {
	Nod* temp = (*varf);
	if(temp != NULL) {
		(*varf) = (*varf)->next;
		if(temp->info != NULL) {
			if(temp->info->den != NULL)
				free(temp->info->den);

			free(temp->info);
		}
		free(temp);	
	}
}

void sortel(Nod* varf) {
	if(!varf || !varf->next) return;
	Nod* i, *j;	
	Carte* temp;

	for( i = varf; i->next; i = i->next)
		for(j = i->next; j; j = j->next)
			if(i->info->isbn > j->info->isbn) {
				temp = j->info;
				j->info = i->info;
				i->info = temp;
			}
}

int main(int argc, char** argv)
{
	Nod* varf = NULL;
	Carte* artc = NULL;
	char tbuf[10];

	artc = (Carte*)malloc(1 * sizeof(Carte));

	printf("isbn = "); scanf("%d", &(artc->isbn));
	while(artc->isbn != 0)
	{
		printf("den = "); scanf("%s", &tbuf);
		artc->den = (char*)malloc(sizeof(char) * (strlen(tbuf) + 1));
		strcpy(artc->den, tbuf);
		
		printf("anpub = "); scanf("%d", &(artc->anpub));

		insNodInceputStiva(&varf, artc);
		artc = (Carte*)malloc(1 * sizeof(Carte));

		printf("isbn = "); scanf("%d", &(artc->isbn));
	}

	afisNoduriStiva(varf);
	stergNodInceput(&varf);
	afisNoduriStiva(varf);
	sortel(varf);
	afisNoduriStiva(varf);

	return 0;
}









