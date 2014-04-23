#ifndef _FEISTEL_
#define _FEISTEL_

#include "chiffrage.h"

	using namespace std;

	class Feistel : public Chiffrage
	{
		
		public:
			Feistel();
			~Feistel();
		
			/* Méthodes héritées */
			char* chiffrer(const char* chaine);
			char* dechiffrer(const char* chaine);
			
	};
#endif