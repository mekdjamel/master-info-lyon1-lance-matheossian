package Vue;

import Model.Joueur;
import java.awt.Graphics;

import java.awt.Point;
import java.awt.Polygon;

/**
 * La classe qui représente visuellement un joueur
 * TODO :
 * un joueur doit pouvoir noifier sa VueJoueur, et VuJoueur doit mettre à jour son affichage (et non VueTerrain)
 * -> déjà testé mais les joueurs ne s'affichaient pas. Voir pour plus tard.
 */
class VueJoueur extends VueElemMobiles {

    Joueur unJoueur; /** la vue à une référence sur le model */

    protected static final Integer rp = 10, rb = 5; /** pour le tracé des joueurs  */

    /**
     * Les coordonnées du model serviront à dessiner le joueur
     * @param unJoueur une joueur du model
     */
    public VueJoueur(Joueur unJoueur) {
        this.unJoueur = unJoueur;
    }

    /**
     * Dessine le joueur
     */
    public void dessiner(Graphics g, Boolean clear){
        
        //System.out.println("Joueur " + unJoueur.getNom() + " dessiné.");


        //Calcule les 3 coins du triangle a partir de la position du joueur
        Point pointUn = new Point(unJoueur.getX(),unJoueur.getY());

        Polygon arrow = new Polygon();

        //Calcule des deux bases

        //Angle de la droite
        double theta = Joueur.convDegGrad * (- unJoueur.getAngle());
        //Demi angle au sommet du triangle
        double alpha = Math.atan( (float) rb / (float)rp );
        //Rayon de la fleche
        double r = Math.sqrt( rp*rp + rb*rb );
        //Sens de la fleche

        //Pointe
        Point pointDeux = new Point((int) Math.round(pointUn.getX()+r*Math.cos(theta)),
                             (int) Math.round(pointUn.y-r*Math.sin(theta)));

        arrow.addPoint(pointDeux.x,pointDeux.y);

        arrow.addPoint((int) Math.round( pointDeux.getX()-r*Math.cos(theta + alpha) ),
                       (int) Math.round( pointDeux.y+r*Math.sin(theta + alpha) ));

        //Base2
        arrow.addPoint((int) Math.round( pointDeux.x-r*Math.cos(theta - alpha) ),
                       (int) Math.round( pointDeux.y+r*Math.sin(theta - alpha) ));

        arrow.addPoint(pointDeux.x,pointDeux.y);

        g.setColor(unJoueur.getMonEquipe().getCouleur());
        
        g.fillPolygon(arrow);


        /* Autre dessin (rectangle à angles arrondis)
        Point point = new Point(unJoueur.getX(),unJoueur.getY());

        //on accède au modèle pour récupérer la couleur de l'équipe
        g.setColor(unJoueur.getMonEquipe().getCouleur());

        g.fillRoundRect((int) point.getX(), (int) point.getY(), 10, 10, 15, 15);
        */


    }

}
