%Etat initial et final
initial( [h,h,h,b,b,b] ).
final( [b,b,b,h,h,h] ).

/*
	@see http://pcaboche.developpez.com/article/prolog/listes/?page=page_2#Lappend
	Remplacement d'une sous-liste par une autre dans une liste quelconque.
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
	L2 le prochaine �tat (il faut le construir en utilisant remp())
*/
opF( L1, r1, L2) :- remp([h,h], [b,b], L1, L2).
opF( L1, r2, L2) :- remp([h,b], [b,h], L1, L2).
opF( L1, r3, L2) :- remp([b,h], [h,b], L1, L2).
opF( L1, r4, L2) :- remp([b,b], [h,h], L1, L2).


%Recherche en profondeur simple et "brutale". Sans oublier de ne pas passer 2 fois par le m�me �tat.
rechPf(Ef,Ef, Letats, Letats).
rechPf(Ec, Ef, Letats, [Opx|Lop]) :-
	opF(Ec, Opx, Esuivant), %prend le premier opF qui fonctionne (ce qui n'est pas forc�ment le meilleur chemin)
	not(member(Esuivant,Letats)),
	rechPf(Esuivant, Ef, [Esuivant|Letats] , Lop).

	
% Affichage ligne par ligne
afficherLigne(X,[]):- write(X), nl.
afficherLigne(X, [T|Q]):- write(X), nl, afficherLigne(T,Q).
afficher([T|Q]):- afficherLigne(T,Q).
	
	
%r�solution g�n�ral
resoudre:- initial(Ei), final(Ef), rechPf(Ei, Ef, [Ei], S), afficher(S).


/*
 Pour une meilleur heuristique, il faudrait garder celle qui se rapproche le plus de la solution finale
*/