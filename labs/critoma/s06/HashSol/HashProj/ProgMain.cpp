#include <stdio.h>
#include <memory.h>

struct Angajat {
	unsigned char nume[10];
	float salariu;
};

unsigned long int joaat_hash(unsigned char* key, int len) {
	unsigned long int hash = 0;
	int i = 0;
	for(i = 0; i < len; i++) {
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

unsigned long int java_hash(unsigned char* key) {
	unsigned long int hash = 0;
	hash = (unsigned long int)key;
	return hash;
}

void main()
{
	Angajat vs[3]; int i = 0;
	for (i = 0; i < 3; i++)
		memset(&(vs[i].nume), 0x00, 10);
	
	memcpy(&(vs[0].nume), "Ion", 4); vs[0].salariu = 302.1;
	memcpy(&(vs[1].nume), "Anda", 5); vs[1].salariu = 1050;
	memcpy(&(vs[2].nume), "Nicu", 5); vs[2].salariu = 1071.4;
	
	unsigned long int ki1 = 0, ki2 = 0, ki3 = 0;
	ki1 = joaat_hash(&(vs[0].nume[0]), 10);
	ki2 = joaat_hash(&(vs[1].nume[1]), 10);
	ki3 = joaat_hash(&(vs[2].nume[2]), 10);
	printf("\n ki1 = %u, ki2 = %u, ki3 = %u", ki1, ki2, ki3);

	unsigned long int ji1 = 0, ji2 = 0, ji3 = 0;
	ji1 = java_hash(&(vs[0].nume[0]));
	ji2 = java_hash(&(vs[1].nume[0]));
	ji3 = java_hash(&(vs[2].nume[0]));
	printf("\n ji1 = %u, ji2 = %u, ji3 = %u", ji1, ji2, ji3);
}