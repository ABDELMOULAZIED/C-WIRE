#ifndef SMARTROBUSTESSE_H
#define SMARTROBUSTESSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// Taille maximale des lignes et éléments
#define TAILLE_MAX 256

// Fonction de vérification de l'allocation mémoire 
void* safeMalloc(size_t size);int Verif_Elt(char *elt[]);
int verifierID(char *str);
long long verifierCapacite(char *str);
long long verifierConsommation(char *str);

#endif // SMARTROBUSTESSE_H
