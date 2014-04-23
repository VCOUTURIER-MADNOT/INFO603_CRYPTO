#ifndef _VIGENERE_
#define _VIGENERE_

	#include "chiffrage.h"

	using namespace std;

	class Vigenere : public Chiffrage
	{

			char *key;
		
		public:
			typedef struct
			{
				int p; /* Position du motif */
				char *str; /* Pointeur sur le motif */
			} KMotif_t;
			
			Vigenere(const char *);
			~Vigenere();
		
			int kasiski(const char *);

			/* Méthodes héritées */
			char* chiffrer(const char* chaine);
			char* dechiffrer(const char* chaine);
			
	};
#endif