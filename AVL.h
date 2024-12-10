#ifndef AVL.H
#define AVL.H


typedef struct node{
  int id;
  int id_centrale;
  long long capacite;
  long long consommation;
  int hauteur;
  struct node * droite;
  struct node *gauche;
}NoeudAVL;




NoeudAVL *creerNoeud(char *elt[]);
NoeudAVL* inserer(NoeudAVL* n, NoeudAVL* nouveau);
NoeudAVL *rechercher(NoeudAVL *n, int id);
void parcours_pre(NoeudAVL * n);

