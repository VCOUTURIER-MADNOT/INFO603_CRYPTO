#include "constantes.h"
#include "vigenere.h"
#include "outils.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>

using namespace std;
Vigenere::Vigenere(const char *key)
{
	this->key = strdup(key);
	toUpperCase(this->key);
}

Vigenere::~Vigenere()
{
	delete(this->key);
}

char* Vigenere::chiffrer(const char* chaine)
{
	int i, klen, slen;
    char *dest;

    dest = strdup(chaine);
    toUpperCase(dest);

    /* On enlève les caractères non alpha-numériques */
    for (i = 0, slen = 0; dest[slen] != '\0'; slen++)
            if (isupper(dest[slen]))
                    dest[i++] = dest[slen];

    dest[slen = i] = '\0'; /* Pour plus de sécurité, on termine la chaine après les caractères utiles */

    klen = strlen(this->key);
    for (i = 0; i < slen; i++) {
            if (!isupper(dest[i])) continue;
            dest[i] = 'A' + (dest[i] - this->key[i % klen] + 26) % 26;
    }

    return dest;
}


char* Vigenere::dechiffrer(const char* chaine)
{
	int i, klen, slen;
    char *dest;

    dest = strdup(chaine);
    toUpperCase(dest);

    /* On enlève les caractères non alpha-numériques (les espaces sont laissés) */
    for (i = 0, slen = 0; dest[slen] != '\0'; slen++)
            if (isupper(dest[slen]))
                    dest[i++] = dest[slen];

    dest[slen = i] = '\0'; /* Pour plus de sécurité, on termine la chaine après les caractères utiles */

    klen = strlen(this->key);
    for (i = 0; i < slen; i++) {
            if (!isupper(dest[i])) continue;
            dest[i] = 'A' + (dest[i] - 'A' + this->key[i % klen] - 'A') % 26;
    }

    return dest;
}

int Vigenere::kasiski(const char* chaine)
{
	//char *dest;
	char *temp = strdup(chaine);
	int taille = strlen(chaine);
	Vigenere::KMotif_t *motifs = new Vigenere::KMotif_t[taille];

	for(int i =0; i<taille; i++)
	{
		motifs[i].p = i;
		motifs[i].str = &temp[i];
	}

	qsort(motifs, taille, sizeof(Vigenere::KMotif_t), kmotifCpr);
	
    int tailleCle = 0;
    for(int i =0; i<taille-1; i++)
    {
        //cout << "Comparaison :" << endl;
        //cout << "\t" << motifs[i].str[0] << motifs[i].str[1] << motifs[i].str[2] << motifs[i].str[3] << endl;
        //cout << "\t" << motifs[i+1].str[0] << motifs[i+1].str[1] << motifs[i+1].str[2] << motifs[i+1].str[3] << endl;
        int j = 0;
        int egal = 1;
        while(j < TAILLE_FENETRE && egal)
        {
            if(motifs[i].str[j] != motifs[i+1].str[j])
            {
                egal = 0;
            }

            j++;
        }
        if(egal)
        {
            tailleCle = pgcd(tailleCle, abs(motifs[i].p - motifs[i+1].p));
            cout << "Distance : " << abs(motifs[i].p - motifs[i+1].p) << endl;
        }
        
    }

    delete[] temp;
    delete[] motifs;
	return tailleCle;

}

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout << "Syntaxe : " << endl;
        cout << "\t ./Vigenere clé fichier" << endl;
        return 0;
    }

    std::ifstream is (argv[2], std::ifstream::binary);
    if(is)
    {
        is.seekg(0, is.end);
        int taille = is.tellg();
        is.seekg(0, is.beg);

        char * fichierData = new char[taille];

        is.read(fichierData,taille);
        is.close();

    	Vigenere v(argv[1]);

    	char * chiffree = v.chiffrer(fichierData);
    	//cout << "Chaine chiffrée : " << chiffree << endl;

    	char * dechiffree = v.dechiffrer(chiffree);
    	//cout << "Chaine déchiffrée : " << dechiffree << endl;

        int k = v.kasiski(chiffree);
        cout << "Taille de la clé : " << k << endl;

        delete[] fichierData;
        delete[] chiffree;
        delete[] dechiffree;
    }
	return 1;
}