/*appart v�rifie si un �l�ment donn� appartient � une liste*/
appart(X,[X|_]).
appart(X,[_|Z]):-appart(X,Z).


%************************CONFIGURATION DU RESEAU LYONNAIS*************************

/*ligne indique la liste des stations qui appartiennent � une ligne
  Ce pr�dicat nous permet, lorsqu'on lui passe un nom de ligne en param�tre,de r�cup�rer la liste de 
  stations correspondantes.*/
ligne(a,[perrache,ampere,bellecour,cordeliers,hotel_de_ville,foch,massena,charpennes,republique,gratte-ciel,flachet,cusset,laurent_bonnevay]).
ligne(b,[charpennes,brotteaux,part-dieu,place_guichard,saxe-gambetta,jean_mace,place_jean_jaures,debourg,stade_de_gerland]).
ligne(c,[hotel_de_ville,croix-paquet,croix-rousse,henon,cuire]).
ligne(d,[gare_de_vaise,valmy,gorge_de_loup,vieux_lyon,bellecour,guillotiere,saxe-gambetta,garibaldi,sans-souci,monplaisir,grange_blanche,lannec,mermoz_pinel,parilly,gare_de_venissieux]).


/*quelle_ligne permet de trouver sur quelle ligne se trouve une station donn�e.*/
quelle_ligne(X,L):- ligne(L,B),appart(X,B).


/*meme_ligne v�rifie que deux stations sont sur la meme ligne.*/
meme_ligne(X,Y,L):- ligne(L,A),appart(X,A),appart(Y,A).


/*rang indique la position d'une station donn�e sur une ligne.*/    
rang(S,[S|_],1).
rang(S,[_|Z],P):- rang(S,Z,T),P is T+1.


/*
Direction indique le sens de d�placement sur une ligne donn�e. 
Parametres: 
	- station1,
	- station2,
	- ligne � laquelle elles appartiennent,
	- direction,
	- le nombre de stations parcourues entre la station1 et la station2.
*/
direction(X,Y,L,D,C):- ligne(L,Ligne),rang(X,Ligne,P1),rang(Y,Ligne,P2),P2>P1,C is P2-P1,length(Ligne,N),rang(D,Ligne,N).
direction(X,Y,L,D,C):- ligne(L,Ligne),rang(X,Ligne,P1),rang(Y,Ligne,P2),P2<P1,C is P1-P2,rang(D,Ligne,1).


/*recherche croisement permet de trouver le permier croisement d'une ligne donn�e a avec une autre.*/
recherche_croisement(L,SC):- ligne(L,Ligne),appart(SC,Ligne),ligne(L2,Lig2),L2\==L,appart(SC,Lig2).


%***************************CALCULS DE FIN DE PARCOURS*****************************


/*nbstation calcule la somme des entiers appartenant � une liste donn�e.
  On initialise S � la fin de la r�cursivit� et au fur et � mesure que l'on remonte la r�cursivit�,on 
  incr�mente S*/
nbstation(0,[]).
nbstation(S,[X|Z]):- nbstation(M,Z),S is M+X. 


/*nb_changement permet de calculer le nombre de changements de ligne effectu�s lors d'un voyage, et ce 
  pour chaque voyage possible d'une station a une autre. Ce pr�dicat peut etre utilis�e apr�s le findall.
  Nbb est une liste qui contiendra le nombre de changements effectu�s pour chaque trajet.*/
nb_changement(Nb,[],Nb).
nb_changement(Nb,[X|L],Nbb):- length(X,N),append(Nb,[N],T),nb_changement(T,L,Nbb).


%***********************************AFFICHAGE***************************************

/*Affichage_liste permet d'afficher tout le parcours du voyageur � partir de la liste I.*/
affichage_liste([]).
affichage_liste([[X,Y,Z]|II]):- 
write('Vous prenez la ligne '),
write(Y),
write(' en direction de '),
write(X),
write(' jusqu''� '),
write(Z),nl,
affichage_liste(II).


/*Affichage_lignes affiche l'ensemble des lignes du m�tro lyonnais*/
affichage_lignes:- write('*** Ligne A ***'),nl, 
		ligne(a,LA),
		write(LA),nl,nl,
		write('*** Ligne B ***'),nl,
		ligne(b,LB),
		write(LB),nl,nl,
		write('*** Ligne C ***'),nl, 
		ligne(c,LC),
		write(LC),nl,nl,		
		write('*** Ligne D ***'),nl,
		ligne(d,LD),
		write(LD),nl.


%************************CALCUL DU MININUM DANS UNE LISTE****************************

/*Recherche du plus petit �l�ment dans une liste*/

min([L],L).
min([A,B|L],Re):- A>B,min([B|L],Re).
min([A,B|L],Re):- B>=A,min([A|L],Re).


%****************TRAJET DE METRO SIMPLE,ON RESTE SUR LA MEME LIGNE DE M�TRO******************

/*Condition d'arret: trajet d'une station � elle-meme*/
parcours(S1,S1,_,_,_,_,_).

parcours(S1,S2,I,I,J,Z,Z) :- 
	meme_ligne(S1,S2,Ligne),nl,
	direction(S1,S2,Ligne,Dir,C),
	append(J,[C],W),
	nbstation(S,W),Z is S, 
	append(I,[[Dir,Ligne,S2]],T),
	affichage_liste(T),nl,
	length(I,N),

	write('Nombre de stations � parcourir: '),write(Z),nl,
	write('Nombre de changements � effectuer:  '),write(N),nl,nl,
	write('			--------------------'),nl,nl.

/*Lors de la recherche d'un parcours entre deux stations donn�es, le pr�dicat parcours teste d'abord
si les deux stations sont sur la meme ligne de m�tro.
Quelque soit le parcours effectu�, les diff�rents d�placements du voyageur entre les diff�rents 
changements de lignes, sont stock�s dans la liste I sous la forme: [Direction,Ligne,Station de Croisement].
Cette liste sera utilis�e lors de l'affichage de tout le parcours du voyageur.*/ 


%******************************TRAJET DE M�TRO AVEC CROISEMENT********************************
/*On doit rappeler en recursif le pr�dicat parcours en prenant comme station de d�part le 
croisement trouv�*/



parcours(S1,S2,I,II,J,_,ZZ) :- 
	not(meme_ligne(S1,S2,Ligne)),
	quelle_ligne(S1,Ligne),
	recherche_croisement(Ligne,SC),
	direction(S1,SC,Ligne,Dir,C),
	append(J,[C],W),
	not(appart([_,_,SC],I)),
	not(appart([_,Ligne,_],I)),
	append(I,[[Dir,Ligne,SC]],T),
	parcours(SC,S2,T,II,W,_,ZZ).



/*I est une liste de listes, [Direction,ligne,Station de croisement].
  Avec le deuxieme not appart, � chaque rencontre de croisement, le voyageur change de ligne, cela �vite
  au voyageur de revenir sur ses pas*/

%******************************************MENU********************************************

metro:- menu.

menu :- write('		      ************************************'),nl,
	write('		      **          METRO DE LYON	        **'),nl,
	write('		      ************************************'),nl,nl,nl,
	write('	----------'),nl,
	write('	|  MENU  |'),nl,
	write('	----------'),nl,nl,
	write('1- Afficher toutes les lignes de m�tro'),nl,
	write('2- Chercher un itin�raire particulier avec le nombre de stations � parcourir '),nl,
	write('3- Chercher un itin�raire particulier avec le nombre de changements � effectuer '),nl,
	write('4- Quitter ?'),nl,nl,
	write('Choix => '),
	read(Choix),
	fonction(Choix).
	
	
/*On traite la r�ponse donn�e par le voyageur, et selon son choix, on lance les traitements correspondants*/
fonction(1):- affichage_lignes,nl,
		write('Avez-vous une autre demande ?(pour oui,tapez 1. / pour non tapez 2.)'),nl,
		write('Choix => '),read(Rep),
		reponse(Rep).

fonction(2):- write('Tapez votre station de d�part : '),read(S1),
	write('Tapez votre station d''arriv�e : '),read(S2),nl,nl,
	write('-------------------------PARCOURS POSSIBLES-------------------------'),nl,
	findall(ZZ,parcours(S1,S2,[],_,[],_,ZZ),Listezz),
	min(Listezz,Resultat),
	rang(Resultat,Listezz,R),
	write('LE PARCOURS LE PLUS COURT EST LE PARCOURS N�  '),write(R),nl,
	nl,write('Avez-vous une autre demande ?(pour oui,tapez 1. / pour non tapez 2.)'),nl,
	write('Choix => '),read(Rep),
	reponse(Rep).

fonction(3):- write('Tapez votre station de d�part : '),read(S1),
	write('Tapez votre station d''arriv�e : '),read(S2),nl,nl,
	write('-------------------------PARCOURS POSSIBLES-------------------------'),nl,
	findall(II,parcours(S1,S2,[],II,[],_,_),Listeii),
	nb_changement(_,Listeii,Nb),
	min(Nb,Resultat),
	rang(Resultat,Nb,R),
	write('LE PARCOURS CONTENANT LE MOINS DE CHANGEMENTS EST LE PARCOURS N�  '),write(R),nl,
	nl,write('Avez-vous une autre demande ?(pour oui,tapez 1. / pour non tapez 2.)'),nl,
	write('Choix => '),read(Rep),
	reponse(Rep).


fonction(4):- write('******* MERCI D''AVOIR CHOISI NOTRE RESEAU *******'),nl,
	write('**** Nous vous souhaitons un agr�able trajet ****'),nl,nl,
	write(' Le M�tro de Lyon vous souhaite une BONNE et HEUREUSE ANNEE!'). 


/*reponse permet de relancer le menu apr�s une recherche ou de quitter le programme*/
reponse(1):- nl,nl,menu.
reponse(2):- nl,nl,fonction(4).





