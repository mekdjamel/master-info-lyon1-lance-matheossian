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

        std::vector<double>& getHistogramme();
        void listerValeurs() const;

    private:

        std::vector<double> histogramme; /** de 0 � 255 */

        double min; /** 0 au minimum */
        double max; /** 255 au maximum */

        int picMax; /** position en x du plus grand pic de l'histogramme */

        void majMax(const unsigned int valeur);
        void majMin(const unsigned int valeur);
        void cumule(const unsigned int valeur);

};

#endif // HISTOGRAMME _H
