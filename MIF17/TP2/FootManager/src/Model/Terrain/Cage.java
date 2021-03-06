package Model.Terrain;

import java.awt.Point;

/**
 * Les cages du jeu de foot
 */
public class Cage {

    private Point coordonnees; /** coordonnées de l'angle supérieur gauche */
    private int largeur; /** la longueur de la cage */
    private int longueur; /** la largeur de la cage */


/*******************************  CONSTRUCTEUR  *******************************/

    /**
     * Constructeur : initialise la position et la taille des cages
     * @param xCoinSupG coordonnée en abscisse de l'angle supérieur gauche de la cage
     * @param yCoinSupG coordonnée en ordonné de l'angle supérieur gauche de la cage
     */
    public Cage(int xCoinSupG, int yCoinSupG) {

        coordonnees = new Point(xCoinSupG, yCoinSupG);

        longueur = Terrain.MARGESEINTE;
        largeur = 100; //attention, on part de l'angle sup gauche, donc 2*50
    }

/******************************  GETTER/SETTERS  ******************************/

    /**
     * @return retourne le point au centre de la cage
     */
    public Point getCentreCoordonnees(){
        return new Point((int) coordonnees.getX() + (longueur/2), (int) coordonnees.getY() + (largeur/2));
    }

    public Point getCoordonnees() {
        return coordonnees;
    }

    public int getLargeur() {
        return longueur;
    }

    public int getLongueur() {
        return largeur;
    }


}
