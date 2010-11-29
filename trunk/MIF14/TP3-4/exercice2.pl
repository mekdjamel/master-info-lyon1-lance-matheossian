/* Etat initial et final */
initial( [h,h,h,b,b,b] ).
final([b,b,b,h,h,h] ).
nbMaxDiff(6). /* nombre maximum de diff�rences entre l'�tat initial et l'�tat final */


/*
	Remplace une sous-liste par une autre dans une liste quelconque.
	Dans notre cas L2 = EtatSuivant.
	S1 la chaine � trouver
	S2 la chaine � remplacer
	L1 la chaine d'entr�e
	L2 la chaine r�sultante
*/
remp(S1, S2, L1, L2) :- 
	append(Tmp1, L1Suffixe, L1),
	append(L1Prefixe, S1, Tmp1),
	append(L1Prefixe, S2, Tmp2),
	append(Tmp2, L1Suffixe, L2).


/*
	Liste des op�rateurs disponibles pour arriver � l'�tat final
	L1 est l'�tat courant
	rN constante qui d�finit le nom de l'op�ration
	L2 le prochaine �tat (il faut le construire en utilisant remp())
*/
opF( L1, r1, L2) :- remp([h,h], [b,b], L1, L2).
opF( L1, r2, L2) :- remp([h,b], [b,h], L1, L2).
opF( L1, r3, L2) :- remp([b,h], [h,b], L1, L2).
opF( L1, r4, L2) :- remp([b,b], [h,h], L1, L2).


/*
	Compte le nombre de diff�rence(s) entre l'argument 1 et l'argument 2
	Nbdiff compte le nombre de diff�rence(s) entre l'�tat finale et l'�tat suivant 
*/

calculerDiff([H], [B], 0).
calculerDiff([I], [I], 1).

calculerDiff([T|Qs], [T|Qf], Nbdiff) :-  /* t�te identique */
	calculerDiff(Qs, Qf, Nbdiff).
	
calculerDiff([Ts|Qs], [Tf|Qf], Nbdiff) :- /* t�te diff�rente => incr�mentation du nombre de diff�rences */
	calculerDiff(Qs, Qf, NbdiffRec),
	Nbdiff is NbdiffRec + 1. /* passage obligatoire par une variable tmp */
	


/* L'�tat final est atteint */
rechPf(Ef, Ef, Letats, [], Nbdiff) :- write('Liste des �tapes successivent : '), nl, reverse(Letats, L), afficher(L), nl.

/* 
	Recherche de la liste des op�rations our atteindre Ef
	la liste des op�rateurs et des �tats sont assembl�s quand on remonte dans les appels => il faut reverse chacune des listes
*/
rechPf(Ec, Ef, Letats, [Topx|Qlop], Nbdiff) :- 
	opF(Ec, Topx, Esuivant), /* prend le premier opF qui fonctionne (ce qui n'est pas forc�ment le meilleur chemin) */
	not(member(Esuivant,Letats)),
	calculerDiff(Esuivant, Ef, NbdiffSuiv),
	NbdiffSuiv < Nbdiff,
	rechPf(Esuivant, Ef, [Esuivant | Letats], Qlop, NbdiffSuiv).

	
	
/* Affichage ligne par ligne */
afficherLigne(X,[]):- write(X), nl.
afficherLigne(X, [T|Q]):- write(X), nl, afficherLigne(T,Q).
afficher([T|Q]):- afficherLigne(T,Q).

		
/* r�solution g�n�ral */
resoudre:- initial(Ei), final(Ef), nbMaxDiff(N), rechPf(Ei, Ef, [Ei], ListeSuccOper, N),  write('Liste des op�rateurs successif :'), nl, afficher(ListeSuccOper).