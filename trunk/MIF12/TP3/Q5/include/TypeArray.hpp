#ifndef _TYPEARRAY_
#define _TYPEARRAY_

#include "Type.hpp"
#include "TypeInterval.hpp"

/**
*	@brief Type d'un symbole.
*/
class TypeArray : public Type {

	private:
	
		TypeInterval* intervalArray; /** @var intervalArray un interval */
		Type* typeArray; /** @var typeArray le Type des �l�ments stock�s dans le tableau */
	
	public:
	
		/**
		* @brief Cr�e un type Array et stocke le nom "Array"
		*/
		TypeArray();

		/**
		* @brief Cr�e un type Array, depuis une instance TypeArray existante
		* @param _ta le contenu � copier
		*/
		TypeArray(TypeArray* _ta);
		
		/**
		* @brief Cr�e un type Array, depuis une instance d'un TypeInterval et d'un Type
		* @param _interval l'interval � copier
		* @param _type le type � copier
		*/
		TypeArray(TypeInterval* _interval, Type* _type);
		
		~TypeArray();

		/**
		* @brief R�cup�re le type stock� par le tableau
		* @return retourne l'adresse d'une instance de type Type 
		*/
		Type* getTypeTab();
		
		/**
		* @brief R�cup�re le TypeInterval du tableau
		* @return retourne l'adresse d'une instance de type TypeInterval 
		*/
		TypeInterval* getInterval();
		

};

#endif
