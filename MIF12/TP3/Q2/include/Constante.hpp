#ifndef _CONSTANTE_
#define _CONSTANTE_

#include "Symbole.hpp"
/**
 * Gestion d'une constante.
 */
class Constante : public Symbole{

	private:
	
	

       
	public:

	/**
        *   @brief Constructeur, initialise la constante 
	*   @param _id identifiant du symbole
        */
        Constante(Type* _type, int _id);

        /**
        *   @brief Destructeur
        */
        ~Constante();	
	
};


#endif

