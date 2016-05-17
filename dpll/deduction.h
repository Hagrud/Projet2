#include <vector>
#include <iostream>
#include <stdlib.h>

#include "checker.h"

using namespace std;

/**
 *@desc Cherche une clause unitaire.
 *@return True si la fonction a trouvé une clause unitaire.
 */
bool dedUnitaire(vector<Clause *>& clauses, vector<Literal>& literals, Literal &paris);

/**
 *@desc Cherche une variable qui a une polarité unique.
 *@return True si la fonction a trouvé une variable qui a une polarité unique.
 */
bool polarite_unique(vector<Clause *>& clauses, vector<Literal>& literals, Literal &paris);
