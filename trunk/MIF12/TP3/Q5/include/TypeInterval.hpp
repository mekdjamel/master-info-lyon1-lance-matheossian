#ifndef _TYPEINTERVAL_
#define _TYPEINTERVAL_

#include "Type.hpp"

/**
*	@brief Type d'un symbole.
*/
class TypeInterval : public Type {

	private:

		 int debut; /**< debut borne inf�rieure = o� commence l'interval */
		 int fin; /**< fin borne sup�rieure = o� se termine l'interval */

	public:
	
		/**
		* @brief Cr�e un type TypeInterval et stocke le nom "Interval"
		*/
		TypeInterval();

		/**
		* @brief Destructeur
		*/
		~TypeInterval();
		
		/**
		* @brief Cr�e un type TypeInterval, stock le nom "Interval", ainsi que la brone inf�rieure et sup�rieure
		* @param _debut borne inf�rieure de l'interval
		* @param _fin borne sup�rieure de l'interval
		*/
		TypeInterval(int _debut, int _fin);

		
		/**
		* @return retourne un entier qui repr�sente le d�but de l'interval (borne inf�rieure)
		*/
		int getDebut();

		/**
		* @return retourne un entier qui repr�sente la fin de l'interval (borne sup�rieure)
		*/
		int getFin();

};

#endif
