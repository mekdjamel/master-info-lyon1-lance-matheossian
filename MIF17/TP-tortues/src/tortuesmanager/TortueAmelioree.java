package tortuesmanager;


import java.util.ArrayList;


public class TortueAmelioree extends Tortue {


//######################################################################################################      ATTRIBUTS

    private String nom;     /** Le nom de la tortue */

    final int distMin; /** distance minimum entre deux tortues */

    private boolean saluer = true; /** précise si les tortues doivent se saluer */

    private ArrayList<Tortue> listeAmis;


 //######################################################################################################      CONSTRUCTEURS

   /**
    * Constructeur
    * @param tortueAmelioree la liste de toutes les tortues améliorée (du constructeur)
    * @param feuille la feuille de dessin
    * @param name le nom de la tortue
    */
    public TortueAmelioree(FeuilleDessin feuille, String name){

        super(feuille, false);

        listeAmis  = new ArrayList<Tortue>();

        if(name.equals(""))
            this.nom = "tortue" + this.feuille.getListeTortues().size();
        else this.nom = name;

        distMin = 15;
 
    }

//######################################################################################################      ACCESSEURS

    public ArrayList<Tortue> getListeAmis(){ return listeAmis; }
        
    public String getNom() {return nom;}

    public int getDistMin() {return distMin;}

    public boolean isSaluer() {return saluer;}

//######################################################################################################      MUTATEURS

    public void setSaluer(boolean saluer) {this.saluer = saluer;}

//######################################################################################################      METHODES

   /**
    * Retire une tortue de la liste d'amis
    * @param t la tortue amélioréee
    */
    //public void enleverTortue(TortueAmelioree t){listeAmis.remove(t);}

   

    /*-----------------------------------*/
    /*     DEPLACEMENT DES TORTUES
    /*-----------------------------------*/

    /**
     * La tortue se déplace aléatoirement, chaque tortue rencontrée doit se pousser
     * @param dist la distance à parcourire
     */
    public void deplacementAuHasard(int dist)
    {
        //Respect de la distance minimale ?
        int distMinimale = distMin;
        if(dist > distMin) distMinimale = dist;

        //déplacement aléatoire
        int angle = (int)(Math.random()*360);
        if(Math.random() > 0.5) droite(angle); else gauche(angle);
        avancer(distMinimale);

       //System.out.print(">-----DEBUT - Déplacement de " + nom + "\n");

        //pousser les tortues à proximité
        TortueAmelioree uneTortue = null;
        for(int i=0; i < feuille.getListeTortuesAmeliorees().size(); i++){

            uneTortue = feuille.getListeTortuesAmeliorees().get(i);

            if(distPoint(uneTortue.getX(), uneTortue.getY(), this.getX(), this.getY()) <= distMin && uneTortue != this){
                if(saluer) saluerUneTortue(uneTortue);
                uneTortue.pousserTortue(dir, distMinimale);
            }
        } //fin for

       //System.out.print(">-----FIN - Déplacement de " + nom + "\n");

    }



    /**
     * Déplace aléatoirement une tortue et pousse ses voisines si nécessaire
     * A la différence de la version précédante, la tortue va chercher une place
     * disponible, sans devoir pousser d'autres tortues.
     * @param dir la direction de la tortue pousseuse
     * @param dist la distance à parcourire pour la tortue pousseuse
     */
    public void pousserTortue(int dir, int dist){


        /* Variables ------------------------------------->*/

        int newX, newY; //les prochaines coordonnées
        int angle; //la direction
        boolean placeDispo; //aucune tortue voisine aux nouvelles coordonnées ?

        TortueAmelioree uneTortue = null;
        ArrayList<TortueAmelioree> liste = new ArrayList<TortueAmelioree>();
        ArrayList<TortueAmelioree> tortuesADeplacer = new ArrayList<TortueAmelioree>();

        //OPTIMISATION
        /* le nombre de tortues à pousser pour dégager le chemin */
        int nbrTortuesApousser = feuille.getListeTortuesAmeliorees().size();
        /* la meilleur direction en fonction du nombre de tortues à pousser */
        int meilleurAngle = dir;

        /*------------------------------------------------->*/


       for(int nbrEssais = 0; nbrEssais <= 20; nbrEssais++) {

            /* Direction de la tortue "pousseuse" +/-90° */
            angle = dir;
            if(Math.random() > 0.5)
                angle += (int) (Math.random() * 90);
            else angle -= (int) (Math.random() * 90);


            //Calcul de la nouvelle position, après déplacement
            newX = (int) Math.round(getX()+dist*Math.cos(convDegGrad*angle));
            newY = (int) Math.round(getY()+dist*Math.sin(convDegGrad*angle));


            placeDispo = true; //pour le moment la place est disponible
            liste.clear(); //on vide la liste de la boucle précédante

            for(int i=0; i < feuille.getListeTortuesAmeliorees().size(); i++){

                uneTortue = feuille.getListeTortuesAmeliorees().get(i);
       
                if(distPoint(uneTortue.getX(), uneTortue.getY(), newX, newY) <= distMin && uneTortue != this){
                    placeDispo = false;
                    liste.add(uneTortue); //une tortue en plus
                }
            }


            if(nbrTortuesApousser > liste.size()){
                nbrTortuesApousser = liste.size();
                meilleurAngle = angle;
                tortuesADeplacer.clear();
                tortuesADeplacer.addAll(liste);
            }

            //déplacement "aléatoire" (à faire avant de pousser les tortues)
            if((placeDispo) || (nbrEssais == 20)){
                dir = meilleurAngle;
                avancer(dist);
            }


            if(placeDispo){break;}
            else if (nbrEssais == 20){

                //aucune place trouvée, on pousse les tortues voisines
                for(int i = 0; i < tortuesADeplacer.size(); i++){
                    uneTortue = tortuesADeplacer.get(i);
                    if(saluer) saluerUneTortue(uneTortue);
                    tortuesADeplacer.get(i).pousserTortue(dir,dist);
                }

                break; //on sort de la boucle
            }

        }
    }



    /*-----------------------------------*/
    /*         GESTION DES AMIS
    /*-----------------------------------*/

    /**
     * Ajoute une tortue améliorée dans la liste d'amis.
     * @param uneTortue une tortue de type TortueAmelioree.
     */
    public void ajouterUnAmi(TortueAmelioree uneTortue)
    {
        if((uneTortue != this) && (uneTortue instanceof TortueAmelioree))
            listeAmis.add(uneTortue);
    }

    /**
     * Ajoute toutes les tortues améliorées dans la liste d'amis.
     */
    public void ajouterDesAmies()
    {
        ArrayList<TortueAmelioree> liste = feuille.getListeTortuesAmeliorees();

        for(int i = 0; i < liste.size(); i++)
            ajouterUnAmi(liste.get(i));
    }


    /**
     * Salut une tortue.
     * @param uneTortue une tortue de type TortueAmelioree.
     */
    public void saluerUneTortue(TortueAmelioree uneTortue){
        if(saluer) System.out.print(nom + " salut " + uneTortue.getNom() + " et lui demande de se déplacer !\n");
    }


}