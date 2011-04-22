/**
* LANCE Florian : n�10604720
* MATHEOSSIAN Dimitri : n�10604950
* Nous avons choisit d�effectuer la m�thode d�accroissement de r�gions sous CodeBlocks avec OpenCv.
* Notre code est compatible sous Ubuntu et Windows 7.
* Un makefile est dipsonible poura compiler sous Linux.
*/

#include <opencv/cv.h>
#include <opencv/highgui.h>
// -lcv -lhighgui -lcvaux -lml -lcxcore
#include <vector>
#include <string>

#include "../include/Histogramme.h"

#include "../include/Accroissement.h"
#include "../include/Graine.h"

using namespace std;


int theFlag = 0;
CvPoint* tmp = (CvPoint*) malloc(sizeof( CvPoint ) );
void onLClick(int event, int x, int y, int flags, void* param);
void onLClick(int event, int x, int y, int flags, void* param){
    theFlag = flags;
    tmp->x = x;
    tmp->y = y;
}

/**
* @brief Affiche l'image et la redimenssionne avec une largeur de 640px si la largeur de l'image d�passe 640px;
*/
void afficherImage(const std::string nomImage, const IplImage* img);

/**
* @return renvoie le nom de l'image choisit
*/
string demanderImage();

/**
* @brief Demande le seuillage � utiliser (histogramme || ancien seuil || nouvelle valeur)
*/
double demanderSeuil(const IplImage* img_src);

/**
* @brief Disposition manuelle des graines (les coordonn�es seront visibles dans la console).
* Il faut :
* 1- focus la fen�tre de l'image source
* 2- placer la souris sur le point d�sir�
* 3- appuyer sur la lettre 't' pour sauvgarder la graine
* 4- r�it�rer le proc�d� autant de fois que vous le voullez
*/
void demanderDispoGraine(const IplImage* img_src, std::vector<Graine>* graines);

/**
* @brief Dispose automatiquement les graines.
* On divise la largeur et hauteur de l'image par "decoupe" pour obtenir un pasX et pasY.
* Si un des deux pas est trop petit, il est fix� � 10.
*/
void dispositionAutomatique(const IplImage* img_src, vector<Graine>* graines, const unsigned int decoupe);

/**
* @brief Dispose al�atoirement les graines.
*
*/
void dispositionAleatoire(const IplImage* img_src, vector<Graine>* graines, const unsigned int nombre);


vector<IplImage*> listeALiberer; //liste des images � lib�rer � chaque tour de boucle (il faut les conserver jusqu'� la fin).

int main()
{
    string nomImage, cheminImg, cheminImage, rep;
    string nomFenetreSrc  = "Image Source";
    string nomFenetreSeg  = "Image Segment�e";

    char key = '----';
    while (key != 'q' && key != 'Q'){

        cvNamedWindow(nomFenetreSrc.c_str(), CV_WINDOW_AUTOSIZE);
        cvResizeWindow(nomFenetreSrc.c_str(), 1,1);
        cvMoveWindow(nomFenetreSrc.c_str(),10,0);

        cvNamedWindow(nomFenetreSeg.c_str(), CV_WINDOW_AUTOSIZE);
        cvResizeWindow(nomFenetreSeg.c_str(), 1,1);
        cvMoveWindow(nomFenetreSeg.c_str(),665,0);

        cheminImg = "images/";

        IplImage* img_src = NULL;
        bool bonChemin = false;

        //------------------------ Demande l'image � segmenter ------>

        while (!bonChemin)
        {
            cheminImage = cheminImg;
            cheminImage += demanderImage().c_str();

            img_src = cvLoadImage(cheminImage.c_str());
            if(img_src == NULL){cout << "Mauvais chemin d'image !" << endl;}
            else {bonChemin = true;}
        }

        //--------- Affichage ------>

        afficherImage(nomFenetreSrc, img_src);

        //------------------------ Cr�e et r�cu�re les graines, modifie le seuil et le % d'occupation ------>

        double occupationMin = 70; /* taux d'occupation minimal des r�gions */
        std::vector<Graine>* graines = new std::vector<Graine>;
        double seuil = demanderSeuil(img_src);
        demanderDispoGraine(img_src, graines);

        //------------------------ Lance l'algorithme si il y a des graines ------>

        if(graines->size())
        {

            //--------- Accroissement  ---->

            Accroissement acc(img_src, seuil, occupationMin);
            acc.demarrer(*graines);

            //--------- Affichage  ------>

            afficherImage(nomFenetreSeg, acc.getImgSeg());

            //------------------------ Sauvegarde de l'image segment�e ----------->

            cvSaveImage("images/resultat.jpg",acc.getImgSeg());
            cout << "Image segmentee sauvegardee: images/resultat.jpg" << endl;

            rep.clear();
            cout << "Cliquez sur une fenetre d'OpenCv puis (q) pour pour quitter, (s) pour segmenter une nouvelle image." << endl;
            key = '-----';
            while(key != 'q' && key != 's' && key != 'Q' && key != 'S') key = cvWaitKey(50);

        }

        delete graines;
        cvReleaseImage(&img_src);
        cvDestroyAllWindows();

        //------------------------ On lib�re les images cr��es dans afficherImage() ----------->
        for(unsigned int i = 0; i < listeALiberer.size(); i++) cvReleaseImage(&listeALiberer[i]);
        listeALiberer.clear();

        cout << endl << "-----------------------------------------------------------------" << endl << endl;
    }

}


//-------------- Listing des images disponibles ----------------->
//**************************************************************//


string demanderImage()
{

    //<-----------------------------------------------------AJOUTER LES IMAGES DE TESTS ICI
    std::vector<string> images;
    images.push_back("deuxcarre.pgm (256*256)");
    images.push_back("deuxcarre3d.pgm (256*256)");

    images.push_back("notre-dame-de-paris.jpg (500*336)");
    images.push_back("opera-lyon.jpg (540*360)");
    images.push_back("cellules.jpg (768*512)");

    images.push_back("paysage-colore.jpg (1024*768)");
    images.push_back("paysage-de-riziere.jpg (1280*857)");
    images.push_back("NewYork.jpg (1468*1101)");
    //------------------------------------------------------------------------------------<


    cout << "Entrez le numero de l'image a segmenter : " << endl;

    for(unsigned int i = 0; i < images.size(); i++) cout << i << " - " << images[i] << endl;

    while(true)
    {
        string tmp;
        cin >> tmp;
        int choix = atof(tmp.c_str());
        if(choix < images.size() && choix >= 0)
        {
            tmp = images[choix]; //on r�cup�re le contenu
            tmp = tmp.substr(0,tmp.find(" ")); //on r�cup�re l'image sans le (taille*taille)
            cout << tmp << endl << endl;
            return tmp;
        }
        cout << "Le numero d'image choisit n'existe pas. " << tmp << " Reeseyez : " << endl;
    }

}

//-------------- Affichage des images ----------------->
//****************************************************//

void afficherImage(const string nomFenetreSeg, const IplImage* img)
{
    IplImage* tmp;

    if(img->width > 640)
    {
        tmp = cvCreateImage(cvSize(640, img->height * ((double) 640/(double) img->width)), IPL_DEPTH_8U, 3);
        listeALiberer.push_back(tmp);
        cvResize(img, tmp);
        cvShowImage( nomFenetreSeg.c_str(),tmp);
    }
    else cvShowImage( nomFenetreSeg.c_str(), img);

    cvWaitKey(100);
}


//--------------------- Seuillage ------------------------------->
//***************************************************************//


double demanderSeuil(const IplImage* img_src)
{
    std::string rep;
    double tmpSeuil, seuil = 10;

    tmpSeuil = Histogramme(img_src, 3).getPicMax();

    if(tmpSeuil != 0)
    {
        cout << "Prendre le seuil = au pic d'intensite dans l'histogramme = " << tmpSeuil << " ? y/n" << endl;
        while(rep.compare("y") && rep.compare("n") && rep.compare("Y") && rep.compare("N")) cin >> rep;
        if(!rep.compare("y") || !rep.compare("Y")) seuil = tmpSeuil;
    }
    else
    {
        cout << "Le pic de plus forte intensite dans l'histogramme est nul donc non-exploitable. " << endl;
        rep = "n"; // pour passer au if ci-dessous
    }

    if(!rep.compare("n") || !rep.compare("N"))
    {
        rep.clear();
        cout << "Seuil actuel : " << seuil << "." << endl << endl << "Si vous desirez le conserver entrez la lettre 'y', sinon entrez un nombre : " << endl;
        cin >> rep;

        if(!rep.compare("y") || !rep.compare("Y")){}
        else
        {
            tmpSeuil = atof(rep.c_str());

            if(tmpSeuil == 0)
                cout << "Vous avez entre un seuil null donc non-exploitable. " << endl;
            else
                seuil = tmpSeuil;

            cout << "Nouveau seuil : " << seuil << endl << endl;
        }
    }

    return seuil;
}



//--------------------- Disposition des graines  ------------------------------->
//*****************************************************************************//


void demanderDispoGraine(const IplImage* img_src, std::vector<Graine>* graines)
{

    std::string rep;
    char* nomFenetre = "Deposez vos graines";

    cout << "Choix de disposition des graines (entrez la lettre entre parenthese) :" << endl <<
    "- (a)utomatique (cadrillage)" << endl <<
    "- au (h)asard" << endl <<
    "- au (c)hoix (selection a la souris)" << endl;

    char key = '---';
    while(rep.compare("a") && rep.compare("h") && rep.compare("c")) cin >> rep;

    if(!rep.compare("c"))
    {
        cvNamedWindow(nomFenetre, CV_WINDOW_AUTOSIZE);
        cvMoveWindow(nomFenetre,340,0);
        IplImage* clone = cvCloneImage(img_src);
        cvShowImage(nomFenetre, clone);

        cout << endl << "1- Selectionnez la nouvelle fenetre" << endl;
        cout << "2- Positionnez la souris ou vous desirez poser la graine" << endl;
        cout << "3- Appuyez sur 't' pour sauvegarder la graines" << endl;
        cout << "4- Reiterez le proceder." << endl;
        cout << "Quand vous aurez termine, appuyez sur 'q' en restant dans la fenetre de l'image." << endl;

        while(key != 'q')
        {
            cvSetMouseCallback(nomFenetre, onLClick);

            if(key == 't')
            {
                graines->push_back(Graine(tmp->x,tmp->y));
                cout << "Graine " << graines->size() << " : (" << tmp->x << "," << tmp->y << ")." << endl;
                cvCircle(clone, cvPoint(tmp->x,tmp->y), 4, CV_RGB(255,255,0), -1);
                cvShowImage(nomFenetre, clone);
                theFlag = 0;
                key = '---';
            }

            key = cvWaitKey(20);
        }

        cvReleaseImage(&clone);
        cvDestroyWindow(nomFenetre);

    }
    else if(!rep.compare("a"))
    {
        cout << "Disposition automatique des graines." << endl;

        bool nMax = img_src->width/10 > img_src->height/10;

        cout << "Donnez la valeur de N : (N <= " << (nMax?ceil(img_src->height/10):ceil(img_src->width/10)) << ") : " << endl;
        cout << "Calcul du pas : PasX = largeurImg/N et PasY = hauteurImg/N" << endl;
        cout << "Chaque graine sera repartie sur l'image en respectant le PasX et le PasY."<< endl;
        cin >> rep;
        dispositionAutomatique(img_src, graines, atof(rep.c_str()));
    }
    else
    {
        cout << "Disposition au hasard des graines. " << endl;

        bool nMax = img_src->height/3 > img_src->width/3;

        cout << "Nombre de graine N a rependre (avec N <= " << (nMax?ceil(img_src->width/3)*2:ceil(img_src->height/3)*2) << ") : " << endl;

        cin >> rep;

        dispositionAleatoire(img_src, graines, atof(rep.c_str()));
    }

    cout << endl;
}


void dispositionAutomatique(const IplImage* img_src, vector<Graine>* graines, const unsigned int decoupe)
{
    double pasX;
    double pasY;

    unsigned largeur = img_src->width;
    unsigned hauteur = img_src->height;

    if(decoupe != 0)
    {    //comme c'est de l'al�atoire, on ajoute une facteur *2
        pasX = (double) largeur/(double) decoupe;
        pasY = (double) hauteur/(double) decoupe;
    }

    if(pasX < 10) pasX = 10;
    if(pasY < 10) pasY = 10;

    string nomFenetre = "Repartition Automatique";
    cvNamedWindow(nomFenetre.c_str(), CV_WINDOW_AUTOSIZE);
    IplImage* clone = cvCloneImage(img_src);

    unsigned int x = 0, y = 0;

    while(y < hauteur)
    {
        x = 0;

        while(x < largeur)
        {
            graines->push_back(Graine(x,y));
            cvCircle(clone, cvPoint(x,y), 4, CV_RGB(255,255,0), -1);
            x += pasX;
        }

        y += pasY;
    }

    afficherImage(nomFenetre.c_str(), clone);
    cvReleaseImage(&clone);
}

void dispositionAleatoire(const IplImage* img_src, vector<Graine>* graines, const unsigned int nombre)
{

    unsigned int nb = nombre;

    unsigned int pasX;
    unsigned int pasY;

    unsigned int largeur = img_src->width;
    unsigned int hauteur = img_src->height;

    if(nb != 0)
    {    //comme c'est de l'al�atoire, on ajoute une facteur *2
        pasX = 2*largeur/nb;
        pasY = 2*hauteur/nb;
    }

    //on conserve le c�t� le plus petit
    if(pasX < 3 || pasY < 3)
        if((double) (hauteur/3) > (double) (largeur/3))
            nb = ceil(largeur/3);
        else
            nb = ceil(hauteur/3);

    string nomFenetre = "Repartition Al�atoire";
    cvNamedWindow(nomFenetre.c_str(), CV_WINDOW_AUTOSIZE);
    IplImage* clone = cvCloneImage(img_src);

    for(unsigned int i = 0; i < nb; i++)
    {
        unsigned int x = rand()%largeur;
        unsigned int y = rand()%hauteur;
        graines->push_back(Graine(x,y));
        cvCircle(clone, cvPoint(x,y), 4, CV_RGB(255,255,0), -1);
    }

    afficherImage(nomFenetre.c_str(), clone);
    cvReleaseImage(&clone);
}
