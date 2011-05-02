#ifndef ICELLULE_H
#define ICELLULE_H

#include <vector>

#include "Point.h"

/**
* @class On pr�ferera utiliser une clase de base "Cellule" � la m�ta-programmation (au cas o� le fichier texte source varie)
*/
class Cellule
{
    public:
        const unsigned int& getDimension() const{return dimension;}

    private:
        unsigned int dimension;
};


/**
* @class Classe I-Cellule :
* en dimension 0, une 0-cellule est un point,
* en dimension 1, une 1-cellule est un segment,
* en dimension 2, une 2-cellule est un carr�,
* en dimension 3, une 3-cellule est un cube,
* en dimension 4, une 4-cellule est un tesseract.
*/

template <unsigned int DIMENSION, class T = double, unsigned int DIMPOINT = 2>
class ICellule : Cellule
{
    public:

        /**
        * @param nouvBords les bords sont forc�ment des (i-1)-Cellules
        */
        ICellule(std::vector< ICellule<DIMENSION-1, T, DIMPOINT>* > nouvBords){dimension = DIMENSION;}
        virtual ~ICellule();

        ICellule* operator[](int i){return getBord(i);}
        const ICellule* operator[](int i) const{return getBord(i);}

    protected:

    private:

        /**
        * Bord :
        * un segment � 2 sommets (2 bords)
        * un carr� � 4 segments (4 bords)
        * un cube � 6 faces (6 bords)
        * Le nombre de bords = 2 * DIMENSION
        * les 0-cellules (sommets) contiendront juste un point associ� au sommet (voir sp�cialisation)
        */
        std::vector< ICellule<DIMENSION-1, T, DIMPOINT> > bords;

        const ICellule* getBord(const unsigned int i) const{return (i < bords.size())?bords[i]:NULL;}

        /**
        * @brief Ajoute un bord � la cellule
        * @param icellule
        */
        void addBord(ICellule* icellule){bords.push_back(icellule);}

};


//Sp�cialisation : on a une 0-Cellule
template <class T, unsigned int DIMPOINT>
class ICellule<0, T, DIMPOINT> : Cellule
{
    public:

        /**
        * @param nouvSommet le sommet car on est dans une 0-Cellules
        */
        ICellule(ICellule<0, T, DIMPOINT>* nouvSommet){dimension = 0;}

        virtual ~ICellule();

    private:

        Point<T, DIMPOINT> sommet; /** Un point contenant 3 donn�es de type T.
                                    *  Exemple : 3 double pour repr�senter les coordonn�es x, y et z */

        const Point<T, DIMPOINT>* getBord() const{return sommet;}
};

#endif // ICELLULE_H
