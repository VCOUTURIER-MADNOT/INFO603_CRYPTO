#ifndef _CHIFFRAGE_
#define _CHIFFRAGE_
	#include <string>

	using namespace std;

	class Chiffrage
	{
	public:
		// Constructeur - Destructeur
		Chiffrage();
		~Chiffrage();

		//Méthodes
		virtual char* chiffrer(const char* chaine) = 0;
		virtual char* dechiffrer(const char* chaine) = 0;
		
	};
#endif