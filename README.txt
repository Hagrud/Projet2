Le code se compose en 2 partie, le parser et l'algorithme DPLL.

Structures de données:
	Instance de SAT: 
		chaque clause est représenté par un vecteur d'entier: vector<int>
	L'instance complète: vector<vector<int>>
	

Répartition du travail:
	Parser: Paul Mangold
	DPLL: Polet Pierre-Etienne
	
On a ensuite travaillé à deux sur une version plus élaborée de
l'algorithme DPLL. (Avec déduction et paris sur les variables).
Mais l'algorithme n'était pas assez abouti pour le rendu.

Performances:
	L'algorithme devient très long dès qu'on augmente le nombre de variables.