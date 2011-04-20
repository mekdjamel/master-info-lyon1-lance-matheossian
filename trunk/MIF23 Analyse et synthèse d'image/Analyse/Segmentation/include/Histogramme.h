#ifndef HISTOGRAMME _H
#define HISTOGRAMME _H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <vector>

/**
* @class Cette classe cr�e un histogramme, elle calcule pour chaque N dans l'intervalle [0;255] son intensit� dans l'image.
*/
class Histogramme
{
    public:

        /**
        * @param rvbG
        * <ol>
        *   <li>rvbG = 0 => on calcul l'histogramme pour la couleur rouge</li>
        *   <li>rvbG = 1 => on calcul l'histogramme pour la couleur verte</li>
        *   <li>rvbG = 2 => on calcul l'histogramme pour la couleur bleu</li>
        *   <li>rvbG = 3 => on calcul l'histogramme pour l'intensit� lumineuse</li>
        * </ol>
        */
        Histogramme(const IplImage* img_src, const unsigned int rvbG);
        virtual ~Histogramme();

        unsigned int getPicMax();

        std::vector<int>& getHistogramme();
        void listerValeurs() const;

    private:

        std::vector<int> histogramme; /** de 0 � 255 */

        int min; /** 0 au minimum */
        int max; /** 255 au maximum */

        int picMax; /** position en x du plus grand pic de l'histogramme (de 0 � 255) */

        void majMax(const unsigned int intensite);
        void majMin(const unsigned int intensite);

        /**
        * @brief Incr�ment d'une unit� l'intensite pass�e en param�tre
        */
        void cumule(const unsigned int intensite);

};

#endif // HISTOGRAMME _H
