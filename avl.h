#ifndef AVL_H
#define AVL_H

typedef struct node {
    int id;
    int id_centrale;
    long long capacite;
    long long consommation;
    int hauteur;
    struct node *droite;
    struct node *gauche;
} NoeudAVL;

int max(int a, int b);
NoeudAVL *creerNoeudAVL(char *elts[]);
NoeudAVL *rotationGauche(NoeudAVL *racine);
NoeudAVL *rotationDroite(NoeudAVL *racine);
NoeudAVL *insererAVL(NoeudAVL *racine, NoeudAVL *nouveau);
NoeudAVL *rechercher(NoeudAVL *n, int id);
NoeudAVL *lire_fichier_station(FILE *fic);
void lire_fichier_consommateur(FILE *fic, NoeudAVL *n);
void parcoursPrefixe(NoeudAVL *n);
NoeudAVL* equilibrer(NoeudAVL* n);

void traiter_Arbre(NoeudAVL* racine);
void liberer_Arbre(NoeudAVL* racine);

#endif // AVL_H
