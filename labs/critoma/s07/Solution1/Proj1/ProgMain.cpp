#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Carte
{
	int isbn;
	float pret;
};

struct nodArbBin
{
	nodArbBin* ss;
	Carte* info;
	nodArbBin* sd;
};

nodArbBin* creareNod(Carte* pc, nodArbBin* sstang, nodArbBin* sdrept) {
	nodArbBin* t = (nodArbBin*)malloc(1 * sizeof(nodArbBin));
	t->info = pc;
	t->ss = sstang;
	t->sd = sdrept;
	return t;
}

nodArbBin* insNodInceput(nodArbBin* v, Carte* pcinfo) {
	nodArbBin* aux = NULL;
	if (!v) return creareNod(pcinfo, NULL, NULL);
	else {
		aux = v;
		while (1) {
			if (pcinfo->isbn < v->info->isbn) {
				if(v->ss) {
					v = v->ss;
				} else {
					v->ss = creareNod(pcinfo, NULL, NULL);
					return aux;
				}
			} else {
				if (pcinfo->isbn > v->info->isbn) {
					if(v->sd) {
						v = v->sd;
					} else {
						v->sd = creareNod(pcinfo, NULL, NULL);
						return aux;
					}
				} else {
					//nodul exista deja
					return aux;
				}
			}
		} //end while
	}
}

void afisNoduri(nodArbBin* vp) {//afisare in ordine SRD
	if (vp) {
		afisNoduri(vp->ss);
		printf("\n isbn = %d, pret = %f", vp->info->isbn, vp->info->pret);
		afisNoduri(vp->sd);
	}
}

nodArbBin* cauta(int isbnCautat, struct nodArbBin* r) {
	nodArbBin* aux = NULL;
	if (!r) return aux;
	while (1) {
		if(isbnCautat < r->info->isbn) {
			if (r->ss) r = r->ss;
			else return aux;
		} else {
			if (isbnCautat > r->info->isbn) {
				if (r->sd) r = r->sd;
				else return aux;
			} else {
				aux = r;
				return aux;
			}
		}
	}
}

void main()
{
	nodArbBin* radacina = NULL;
	Carte* partc = NULL;
	int isbnc = 0;
	nodArbBin* nodGasit = NULL;

	partc = (Carte*)malloc(1 * sizeof(Carte));
	printf("isbn = "); scanf("%d", &partc->isbn);
	while(partc->isbn != 0) {
		printf("pret = "); scanf("%f", &partc->pret);

		radacina = insNodInceput(radacina, partc);

		partc = (Carte*)malloc(1 * sizeof(Carte));
		printf("isbn = "); scanf("%d", &partc->isbn);
	}
	afisNoduri(radacina);

	printf("\n isbn de cautat="); scanf("%d", &isbnc);
	
	nodGasit = cauta(isbnc, radacina);
	
	if (nodGasit) 
		printf("\n isbn gasit=%d, pret gasit=%f",nodGasit->info->isbn, nodGasit->info->pret);
	else 
		printf("\n nodul nu a fost gasit");
}