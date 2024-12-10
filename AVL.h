#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un nœud de l'arbre AVL
typedef struct NoeudAVL {
    int id;                     // Identifiant de la station
    int id_centrale;            // Identifiant de la centrale
    long long capacite;         // Capacité de la station
    long long consommation;     // Consommation de la station
    int hauteur;                // Hauteur du nœud
    struct NoeudAVL *gauche;    // Sous-arbre gauche
    struct NoeudAVL *droite;    // Sous-arbre droit
} NoeudAVL;

int max(int a, int b);

NoeudAVL* creerNoeudAVL(char* elts[]);

NoeudAVL* rotationGauche(NoeudAVL* n);
NoeudAVL* rotationDroite(NoeudAVL* n);
NoeudAVL* rotationGaucheDroite(NoeudAVL* n);
NoeudAVL* rotationDroiteGauche(NoeudAVL* n);

NoeudAVL* equilibrer(NoeudAVL* n);
NoeudAVL* insererAVL(NoeudAVL* racine, NoeudAVL* nouveau);

NoeudAVL* rechercher(NoeudAVL* racine, int id);

void traiter_Arbre(NoeudAVL* racine);
void parcoursPrefixe(NoeudAVL* racine);

void free_Arbre(NoeudAVL* racine);


#endif //AVL_H
