#Point de d�part
rive(1)

#Point d'arriv�
rive(2)

fermier(fermier).
loup(loup).
chevre(chevre)
choux(choux).


#
protagoniste

#Verification du type de la valeur en param�tre
type_respect(Fermier, Loup, Chevre, Choux) :- fermier(Fermier), loup(Loup), chevre(Chevre), choux(Choux).

#D�finition des �tats interdits
interdit(Fermier, Loup, Chevre, Choux) :- Fermier == 0, Loup == 1, Chevre == 1.
interdit(Fermier, Loup, Chevre, Choux) :- Fermier == 0, Chevre == 1, Choux == 1.

#
peutPasser(Protagoniste, Rive) :- 