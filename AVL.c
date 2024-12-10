#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

typedef struct node{
  int id;
  int id_centrale;
  long long capacite;
  long long consommation;
  int hauteur;
  struct node * droite;
  struct node *gauche;
}NoeudAVL;


int max(int a , int b){
  return (a>b)?a:b;
}


NoeudAVL* creerNoeud(char* elt[]) {
    // Allocation mémoire pour le nœud
    NoeudAVL *nouveau = (NoeudAVL *)malloc(sizeof(NoeudAVL));
    if (nouveau == NULL) {
        perror("Erreur d'allocation mémoire");
        return NULL; // Gestion de l'erreur d'allocation
    }
    // Extraction des id et du type en fonction des conditions
    if (atoi(elt[3]) != 0) { 
        nouveau->id =atoi(elt[3]);
    } else if (atoi(elt[2]) != 0) {
        nouveau->id =atoi(elt[2]);
    } else if(atoi(elt[1]) != 0) {
        nouveau->id =atoi(elt[1]);
    }
    // Initialisation de la capacité
    nouveau->capacite = atoll(elt[6]);
    nouveau->id_centrale = atoi(elt[0]);

    nouveau->consommation = 0;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    // Initialisation de la hauteur
    nouveau->hauteur = 0;
    return nouveau;
}


NoeudAVL* rotationGauche(NoeudAVL* racine) {
    NoeudAVL *temp = racine->droite;
    racine->droite = temp->gauche;
    temp->gauche = racine;
    racine->hauteur = 1 + max(calculerHauteur(racine->gauche), calculerHauteur(racine->droite));
    temp->hauteur = 1 + max(calculerHauteur(temp->gauche), calculerHauteur(temp->droite));
    return temp;
}


NoeudAVL* rotationDroite(NoeudAVL* racine) {
    NoeudAVL *temp = racine->gauche;
    racine->gauche = temp->droite;
    temp->droite = racine;
    racine->hauteur = 1 + max(calculerHauteur(racine->gauche), calculerHauteur(racine->droite));
    temp->hauteur = 1 + max(calculerHauteur(temp->gauche), calculerHauteur(temp->droite));
    return temp;
}


NoeudAVL* equilibrer(NoeudAVL* a) { // Code de zied pour l'équilibre
    int hauteurG = (a->gauche ? a->gauche->hauteur : -1);
    int hauteurD = (a->droite ? a->droite->hauteur : -1);
    int fe = hauteurD - hauteurG;

    if (fe == 2) {
        // Sous-arbre droit plus lourd
        int hauteurDroiteG = (a->droite->gauche ? a->droite->gauche->hauteur : -1);
        int hauteurDroiteD = (a->droite->droite ? a->droite->droite->hauteur : -1);
        if (hauteurDroiteD >= hauteurDroiteG) {
            return rotationGauche(a); // Cas RR
        } else {
            return rotationDroiteGauche(a); // Cas RL
        }
    } else if (fe == -2) {
        // Sous-arbre gauche plus lourd
        int hauteurGaucheG = (a->gauche->gauche ? a->gauche->gauche->hauteur : -1);
        int hauteurGaucheD = (a->gauche->droite ? a->gauche->droite->hauteur : -1);
        if (hauteurGaucheG >= hauteurGaucheD) {
            return rotationDroite(a); // Cas LL
        } else {
            return rotationGaucheDroite(a); // Cas LR
        }
    }

    return a;
}


NoeudAVL* insererAVL(NoeudAVL* racine, NoeudAVL* nouveau) {
    if (racine == NULL) {
        return nouveau;
    }

    if (nouveau->id < racine->id) {
        racine->gauche = insererAVL(racine->gauche, nouveau);
    } else if (nouveau->id > racine->id) {
        racine->droite = insererAVL(racine->droite, nouveau);
    } else {
        return racine;
    }

    racine->hauteur = 1 + max((racine->gauche ? racine->gauche->hauteur : -1),
                              (racine->droite ? racine->droite->hauteur : -1));

    // Équilibrage
    racine = equilibrer(racine); // ce qu'on avait fait avec balance ca marchait pas quand on lance le programme

    return racine;
}

NoeudAVL* rechercher(NoeudAVL* racine, int id) {
    if (racine == NULL) {
        return NULL;
    }
    if (racine->id == id) {
        return n;
    }
    if (id < racine->id) {
        return rechercher(racine->gauche, id);
    }
    return rechercher(racine->droite, id);
}


void traiter_Arbre(NoeudAVL* racine) {
if(racine==NULL){
return;
}
printf("%d;%lld;%lld\n", racine->id, racine->capacite, racine->consommation);
}


void parcoursPrefixe(NoeudAVL* racine) {
    if (racine == NULL) return;
    traiter_Arbre(racine);
  parcoursPrefixe(racine->gauche);
  parcoursPrefixe(racine->droite);
}


void free_Arbre(NoeudAVL* racine) {
    if (racine == NULL) {
      return;
    }
    libererArbre(racine->gauche);
    libererArbre(racine->droite);
    free(racine);
}



