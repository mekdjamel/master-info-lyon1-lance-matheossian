package tortuesmanager;

import java.awt.*;
import java.util.ArrayList;


/*************************************************************************

	Un petit Logo minimal qui devra être amélioré par la suite

				J. Ferber - 1999-2001

				Cours de DESS TNI - Montpellier II

	@version 2.0
	@date 25/09/2001

**************************************************************************/

/*
 * La classe Tortue qui se déplace en coordonnées polaires
 */
class Tortue extends Thread
{

     //######################################################################################################      ATTRIBUTS


    FeuilleDessin feuille;     /** la feuille de dessin sur laquelle dessine la tortue */

    private int x, y;	/** les coordonnees de la tortue */

    double convDegGrad = 0.0174533;     /** la constante de conversion de degres en gradient  */
    protected int dir;	/** la direction de la tortue */
    boolean crayon = true; /** si vrai alors le cayon est baissé, faux sinon */
    protected int traitCouleur; /** couleur du trait de la tortue courante */

    /**
    * Couleur de la tortue.
    */
    protected  Color tortueCouleur;


    //######################################################################################################      CONSTRUCTEURS

   /**
    * Constructeur
    * @param feuille la feuille de dessin
    * @param crayon si vrai alors le cayon est baiss
    */
    public Tortue(FeuilleDessin feuille, boolean crayon){
        reset();
        this.feuille = feuille;
        this.crayon = crayon;
        tortueCouleur = Color.GREEN;
        this.feuille.getListeTortues().add(this);
    }


    //######################################################################################################      ACCESSEURS

    /**
    * Retourne la couleur de la tortue
    */
    public Color getCouleur(){return tortueCouleur;}

    public int getX(){return x;}

    public int getY(){return y;}

    public int getDir(){return dir;}

    //######################################################################################################      MUTATEURS

    /**
    * Change la couleur de la tortue
    * @param n Nouvelle couleur pour la tortue
    */
    public void setCouleur(Color coul1){tortueCouleur = coul1;}

    /**
    * Modifie le booleen crayon qui détermine si la tortue laisse un trait en se déplaçant
    * @param b booleen 
    */
    public void setCrayon(boolean b){crayon = b;}

    public void setColor(int n){traitCouleur = n;}

    public void setX(int x) {this.x = x;}

    public void setY(int y) {this.y = y;}

    public void setDir(int dir) { this.dir = dir; }

    //######################################################################################################      METHODES


    //####################################################################################### M: PLACEMENT

   /**
    * Positionne la tortue en (250;180), vers le haut et avec le crayon levé
    */
    void reset()
    {
        x = 250;
        y = 180;
        dir = -90;
        crayon = true;
    }



    /*--------------------------------------------------------*/
    /*  les procedures de base de fonctionnement de la tortue
    /*--------------------------------------------------------*/
    
   /**
    * Fait avancer la tortue sur une certaine distance
    * @param dist la distance à parcourir
    * TODO :
    * - prendre en compte les bords
    * - la tortue ne doit pas être à la même position qu'une autre
    * - si la tortue ne bouge pas, rien ajouter à la liste d'amis
    * @param dist la distance à parcourir en pixel
    */
    void avancer(int dist)
    {
        Graphics g = feuille.getImageGraphics();

        int newX = (int) Math.round(x+dist*Math.cos(convDegGrad*dir));
        int newY = (int) Math.round(y+dist*Math.sin(convDegGrad*dir));

        if (crayon) {
                g.setColor(feuille.decodeColor(traitCouleur));
                g.drawLine(x,y,newX,newY);
        }

        x = newX;
        y = newY;
        
        //if (getShowTurtle())
        //  this.drawTurtle(g);
        //System.out.println("dir: " + dir);
        feuille.drawIt();
    }


    /**
    * Aller à droite
    * @param ang l'angle de rotation
    */
    void droite(int ang)
    {
            dir = (dir + ang) % 360;
            feuille.drawIt();
    }

    /**
    * Aller à gauche
    * @param ang l'angle de rotation
    */
    void gauche(int ang)
    {
            dir = (dir - ang) % 360;
            feuille.drawIt();
    }

    //####################################################################################### M: DIVERS

    /*
     * Recherche la tortue la plus proche
     * @return retourne la tortue la plus proche
     */
    public Tortue tortueLaPlusProche(){

        Tortue uneTortue = null;
        ArrayList<Tortue> listeAmies = feuille.getListeTortues();

        //Initialisation
        Tortue tortueProche = listeAmies.get(0);
        int dist = distPoint(getX(), getY(), tortueProche.getX(), tortueProche.getY());

        for(int i=1; i < listeAmies.size(); i++){

            uneTortue = listeAmies.get(i);

            if(uneTortue != this && distPoint(getX(), getY(), uneTortue.getX(), uneTortue.getY()) < dist){
                dist = distPoint(getX(), getY(), uneTortue.getX(), uneTortue.getY());
                tortueProche = uneTortue;
             }
        }
        return tortueProche;
    }

    //####################################################################################### M: DESSIN

    /**
    *  Baisse le crayon pour dessiner
    */
    void baisserCrayon(){crayon = true;}

    /**
     * lever le crayon pour ne plus dessiner
     */
    void leverCrayon(){crayon = false;}

    /**
     * Attribut une nouvelle couleur au trait de dessin
     * @param n le code couleur entier positif
     */
    void couleur(int n){traitCouleur = n % 12;}

    /**
     * Passer à la couleur suivante
     */
    void couleurSuivante() {couleur(traitCouleur+1);}



   /**
    * Retourne la distance entre la tortue et un point (x,y)
    * @param x coordonnee en abscisse
    * @param y coordonnee en ordonnée
    * @return distance entre la tortue et le point
    */
   public int distPoint(int x, int y)
   {
       return (int) Math.round(Math.sqrt(Math.pow((x - this.x),2) + Math.pow((y - this.y),2)));
   }

   /**
    * Retourne la distance entre la tortue et un point (x,y)
    * @param x1 première coordonnee en abscisse
    * @param y1 première coordonnee en ordonnée
    * @param x2 seconde coordonnee en abscisse
    * @param y2 seconde coordonnee en ordonnée
    * @return distance entre la tortue et le point
    */
   public int distPoint(int x1, int y1, int x2, int y2)
   {
       return (int) Math.round(Math.sqrt(Math.pow((x2 - x1),2) + Math.pow((y2 - y1),2)));
   }


   /**
    * Calcul la distance entre deux tortues
    * @param tortue la deuxieme tortue
    * @return la distance entre les deux tortues
    */
   public int distTortue(Tortue tortue)
   {
       int coord_x = tortue.x;
       int coord_y = tortue.y;
       return distPoint(coord_x,coord_y);
   }

    /*-----------------------------------*/
    /*              FIGURES
    /*-----------------------------------*/

    /**
     * Dessine un carré
     */
    void carre() {
        for (int i=0;i<4;i++) {
                avancer(100);
                droite(90);
        }
    }


    /**
     * Dessine un polygone
     */
    void poly(int n, int a) {
        for (int j=0;j<a;j++) {
                avancer(n);
                droite(360/a);
        }
    }

     /**
     * Dessine une spirale
     */
    void spiral(int n, int k, int a) {
        for (int i = 0; i < k; i++) {
                couleur(traitCouleur+1);
                avancer(n);
                droite(360/a);
                n = n+1;
        }
    }


    /*-----------------------IMMEUBLE----------------------------->*/

     /**
     * Dessine une fenêtre
     */
    void window(){
        for(int i = 0; i < 2; i++){
            avancer(7);
            droite(90);
            avancer(5);
            droite(90);
        }
    }


     /**
     * Décalage du crayon
     * @param x coordonnée polaire
     * @param y coordonnée polaire
     */
    void decalageD(int x, int y){
        crayon = false;
        droite(90);
        avancer(x);
        gauche(90);
        avancer(-y);
        crayon = true;
    }


     /**
     * Décalage du crayon
     * @param x coordonnée polaire
     * @param y coordonnée polaire
     */
     void decalageG(int x, int y){
        crayon = false;
        droite(90);
        avancer(-x);
        gauche(90);
        avancer(-y);
        crayon = true;
    }

     /**
     * Dessine un immeuble
     */
    void immeuble(){
        crayon = true;

        for (int i = 0; i< 2; i++){
            avancer(100);
            droite(90);
            avancer(45);
            droite(90);
        }

        droite(90);
        avancer(20);
        gauche(90);
        avancer(10);
        droite(90);
        avancer(5);
        droite(90);
        avancer(10);
        crayon = false;
        droite(90);
        avancer(20);
        droite(90);
        avancer(90);
        crayon = true;

        int coul1 = traitCouleur;
        couleur(5);

        for (int i = 0 ; i < 8; i++) {
            for (int j = 0 ; j < 4 ; j++) {
                window();
                if (j < 4) decalageD(10,0);

            }
            decalageG(40,0);
            decalageD(0,10);
        }
        couleur(coul1);
    }

    /*---------------------------------------------------------->*/



     /**
     * Dessine un astérisque
     * @param t la taille des branches
     * @param n le nombre de branche(s)
     */
    void asterisque(int t, int n){
        crayon = true;
        for(int i=0; i <= 360;i+=n){
            droite(360/n);
            avancer(t);
            avancer(-t);
        }
    }

}