#ifndef AVL.H
#define AVL.H

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




NoeudAVL *creerNoeud(char *elt[]);
NoeudAVL* inserer(NoeudAVL* n, NoeudAVL* nouveau);
NoeudAVL *rechercher(NoeudAVL *n, int id);
void parcours_pre(NoeudAVL * n);

