#ifndef _TYPERECORD__
#define _TYPERECORD_

#include "Type.hpp"
#include "TDS.hpp"

/**
*	@brief Type d'un symbole.
*/
class TypeRecord : public Type {

	private:

		TableDesSymboles* TDSLocale; /**< TDSLocale table des symboles correspondant � ce nouveau contexte */

	public:
	
		/**
		* @brief Cr�e un type Record et stocke le nom "Record"
		*/
		TypeRecord();

		/**
		* @brief Destructeur
		*/
		~TypeRecord();
		
		/**
		* @brief Cr�e un type Record, stocke le nom "Record" et lui assigne une tabel des symboles
		* @param _TDSLocale pointeur sur une table des symboles
		*/
		TypeRecord(TableDesSymboles* _TDSLocale);


};

#endif
