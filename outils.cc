#include "outils.h"
#include <ctype.h>
#include <iostream>


void toUpperCase(char *src)
{
        while (*src != '\0') {
                if (islower(*src)) *src &= ~0x20;
                src++;
        }
}

int kmotifCpr(const void *a, const void *b)
{
	Vigenere::KMotif_t *ma, *mb;
	ma = (Vigenere::KMotif_t*)a;
	mb = (Vigenere::KMotif_t*)b;

	int i = 0;
	int egal = 1;

	while(i < TAILLE_FENETRE && egal)
	{
		if(ma->str[i] < mb->str[i])
		{
			return -1;
		}
		else if(ma->str[i] > mb->str[i])
		{
			return 1;
		}
		i++;
	}

	return 0;
}

int pgcd(int u, int v) {
	return (v != 0)?pgcd(v, u%v):u;
}

int alphaToInt(char c)
{
	return isupper(c)?(c -'A'):(c-'a');
}