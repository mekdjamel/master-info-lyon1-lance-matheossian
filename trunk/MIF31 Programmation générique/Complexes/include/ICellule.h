#ifndef ICELLULE_H
#define ICELLULE_H

#include <vector>

#include "Point.h"

/**
* @class Classe I-Cellule :
* en dimension 0, une 0-cellule est un point,
* en dimension 1, une 1-cellule est un segment,
* en dimension 2, une 2-cellule est un carr�,
* en dimension 3, une 3-cellule est un cube,
* en dimension 4, une 4-cellule est un tesseract.
*/

template <unsigned int DIMENSION, class T = int, unsigned int DIMPOINT = 0>
class ICellule
{
    public:
        ICellule();
        virtual ~ICellule();

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
        std::vector<ICellule*> bords;

        const ICellule* getBord(const unsigned int i) const;
        void setBord(const unsigned int i, const ICellule& icellule);

};


//Sp�cialisation : on a une 0-Cellule
template <class T, unsigned int DIMPOINT>
class ICellule<0, T, DIMPOINT>
{
    public:
        ICellule();
        virtual ~ICellule();

    private:

        Point<T, DIMPOINT> sommet; /** un point contenant 3 donn�es de type T.
                                    *  Exemple : 3 double pour repr�senter les coordonn�es x, y et z */

        const Point<T, DIMPOINT>* getBord() const;
        void setBord(Point<T, DIMPOINT>& point);
};

#endif // ICELLULE_H
