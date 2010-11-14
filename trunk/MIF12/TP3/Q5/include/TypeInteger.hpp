#ifndef _TYPEINTEGER_
#define _TYPEINTEGER_

#include "Type.hpp"

/**
*	@brief Type d'un symbole.
*/
class TypeInteger : public Type {

	public:
	
		/**
		* @brief Constructeur Cr�e un type Integer et stocke le nom "Integer"
		*/
		TypeInteger();

		/**
		* @brief Destructeur
		*/
		~TypeInteger();

};

#endif
