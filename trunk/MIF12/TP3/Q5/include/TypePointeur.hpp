#ifndef _TYPEPOINTEUR_
#define _TYPEPOINTEUR_

#include "Type.hpp"

/**
*	@brief Type d'un symbole.
*/
class TypePointeur : public Type {

	private:

	Type* reference; /** un pointeur sur un Type */

	public:
	
		/**
		* @brief Cr�e un type Pointeur pour stocker l'adresse d'un Type
		*/
		TypePointeur();
		~TypePointeur();

		/**
		* @brief Cr�e un type Pointeur pour stocker l'adresse d'un Type
		* @param ref l'adresse du type � assigner au pointeur
		*/
		TypePointeur(const Type &ref);

		//Type* getReference() const;
		//std::string* getStringType();
};

#endif
