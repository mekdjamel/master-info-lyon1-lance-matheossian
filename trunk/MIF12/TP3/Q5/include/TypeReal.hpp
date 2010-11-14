#ifndef _TYPEREAL_
#define _TYPEREAL_

#include "Type.hpp"

/**
*	@brief Type d'un symbole.
*/
class TypeReal : public Type {

	public:
	
		/**
		* @brief Cr�e un type R�el et stocke le nom "Real"
		*/
		TypeReal();

		/**
		* @brief Destructeur
		*/
		~TypeReal();

};

#endif
