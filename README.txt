﻿/**
*
*Rendu 4
*
**/
Travail principale sur le rendu :
	On a passee beaucoup de temps pour retravailler le code des rendu précédent qui était trop "bordelique" et qui induisait pleins d'erreur a chaque implementation de nouvelles fonctionnalitees.
		
		Chaque variables est maintenant representee par un type de donnee "literal" qui contient :
			- un id : la "valeur absolue" du nom de la variable.
			- son etat : vrai/faux paris...
			- les deductions induites.
			- les clauses qu'elle a validee (une partie).

		Les clauses sont aussi representee par un type de donnee "clause" qui contient :
			- la valeur de la clause.
			- un boolean qui indique si la clause est deja valide ou non.
		Il n'y rien de plus car on n'a pas eu le temps de refaire les watched literals avec les nouveaux types de donnees.

		
		Pour les paris :
			On a remplacer la classe paris.cpp par des "parieur" a instancier et a passer en argument du solveur dpll.



/**
*
*Rendu 3
*
**/
Le code se compose en 3 parties :
	Main:			Gestion de l'affichage (réponse pour l'utilisateur), récupération des options.
	Parser/Tseitin: Lecture du fichier d'entrée et conversion de la formule logique en instance de SAT.
		Correction des bugs
		Implémentation de l'option -tseitin
	DPLL: 			Résolution du problème SAT pour savoir si il admet une solution.


Structures de données :
	Même que pour le rendu 2.
	-Graphe : vector<vector<int>>			:	Liste d'adjacence.

Répartition du travail:
	Parser/Tseitin: Mangold Paul, Polet Pierre-Etienne.
	DPLL: Polet Pierre-Etienne, Mangold Paul.
	Main: Polet Pierre-Etienne, Mangold Paul.

Performances:
	La partie clause learning n'a pas été traitée, donc l'utilisation du -wl ne fait que ralentir le programme car on calcul le graphe des conflits pour rien.

Commentaire:
	On a perdu énormément de temps à débuger Tseitin et l'affichage du graphe.
	Visiblement on a un problème avec les déductions mais on cherche encore l'origine.
	






	

/**
*
*Rendu 2
*
**/
Le code se compose maintenant de 3 parties :
	Main: 			Gestion de l'affichage (réponse pour l'utilisateur), récupération des options.
	Parser/Tseitin: Lecture du fichier d'entrée et conversion de la formule logique en instance de SAT.
	DPLL:			Résolution du problème SAT pour savoir si il admet une solution.
	

Structures de données :
	-vector<vector<int>> clauses 			:	Tableau de tableau d'entier pour représenter les clauses.
    -vector<int> paris						:	Tableau d'entier pour stocker les variables pariées.
    -vector<vector<int>> deductions			:	Tableau de tableau d'entier pour stocker les déductions liées aux paris. 
    -vector<int> varsStates	   				:	Tableau d'entier pour stocker l'état des variables au cours de DPLL 
													(ça pourrais être un tableau ternaire : -1 libre
																							0 faux
																							1 vrai)
    -vector<bool> clauses_valides			:	Tableau de booléen pour savoir quelles clauses sont déja valide (permet de ne pas avoir 
													à revérifier toutes les clauses à chaque recherche de clauses unitaire.
    -vector<vector<int>> deductions_clauses	:	Tableau de tableau d'entier pour stocker les clauses validé par chaques variables pariées.

Pour la transformation de Tseitin :
    -utilisation du lexer et transformation de l'expression obtenue
    -on remonte récursivement jusqu'aux variables en rajoutant une nouvelle variable à chaque sous expression
    -on utilise un std::set pour récupérer toutes les variables et les comptes
    -on crée un vector<Expr*> qui correspond aux expressions que l'on obtient à la fin de la transformation

Répartition du travail:
	Parser/Tseitin: Mangold Paul 
	DPLL: Polet Pierre-Etienne
	Main: Les deux.
	
Performances:
	- Sur des test à 20 variables et 90 clauses.
		Le code du rendu 1 traitait les codes en 10 à 15 secondes environs voir plus dans certains cas (backtracking peu efficace).
		Le code actuel les traite en 2 à 5 secondes.
	- Pour un problème très gros (plusieurs milliers de clauses et de variables) la résolution prenait beaucoup de temps (>10 minutes).
		
Suite:
	On a commencé a travailler sur une nouvelle structure de donnée pour vérifier si les clauses 
	sont valides plus rapidement et pour trouver facilement si une clause contient (xi ou -xi).
	
	
/**
*
*Rendu 1
*
**/
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
