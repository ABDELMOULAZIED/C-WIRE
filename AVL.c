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

NoeudAVL *creerNoeud(char *elt[]) {
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


NoeudAVL* rotationGauche(NoeudAVL *racine) {
    NoeudAVL *temp = racine->droite;
    racine->droite = temp->gauche;
    temp->gauche = racine;
    racine->hauteur = 1 + max(calculerHauteur(racine->gauche), calculerHauteur(racine->droite));
    temp->hauteur = 1 + max(calculerHauteur(temp->gauche), calculerHauteur(temp->droite));
    return temp;
}

NoeudAVL* rotationDroite(NoeudAVL *racine) {
    NoeudAVL *temp = racine->gauche;
    racine->gauche = temp->droite;
    temp->droite = racine;
    racine->hauteur = 1 + max(calculerHauteur(racine->gauche), calculerHauteur(racine->droite));
    temp->hauteur = 1 + max(calculerHauteur(temp->gauche), calculerHauteur(temp->droite));
    return temp;
}

NoeudAVL *equilibrer(NoeudAVL *a) { // Code de zied pour l'équilibre
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


NoeudAVL *insererAVL(NoeudAVL *racine, NoeudAVL *nouveau) {
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

NoeudAVL *rechercher(NoeudAVL *racine, int id) {
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


NoeudAVL * lire_fichier_station(FILE *fic) {
    char ligne[256];
    // Déclaration des tableaux de chaînes pour chaque élément
    char *elt1 = (char*)malloc(256 * sizeof(char));
    char *elt2 = (char*)malloc(256 * sizeof(char));
    char *elt3 = (char*)malloc(256 * sizeof(char));
    char *elt4 = (char*)malloc(256 * sizeof(char));
    char *elt5 = (char*)malloc(256 * sizeof(char));
    char *elt6 = (char*)malloc(256 * sizeof(char));
    char *elt7 = (char*)malloc(256 * sizeof(char));
    char *elt8 = (char*)malloc(256 * sizeof(char));
    NoeudAVL *n = NULL;
    if (fic == NULL) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }
    // Lire une ligne du fichier
    if (fgets(ligne, sizeof(ligne), fic) != NULL) {
        // Extraction des éléments de la ligne en utilisant sscanf
        int items_read = sscanf(ligne, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]",elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8);
        // Vérification si tous les champs ont été lus correctement
        if (items_read == 8) {
            char *element[] = {elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8};
              n = creerNoeud(element);
        } else {
            printf("Erreur de format dans la ligne: %s\n", ligne);
        }
    }
    // Libération de la mémoire allouée pour les éléments
    free(elt1);
    free(elt2);
    free(elt3);
    free(elt4);
    free(elt5);
    free(elt6);
    free(elt7);
    free(elt8);
    return n;
}


void lire_fichier_consommateur(FILE *fic, NoeudAVL *n) {
    char ligne[256];
    char *elt1 = (char *)malloc(256 * sizeof(char));
    char *elt2 = (char *)malloc(256 * sizeof(char));
    char *elt3 = (char *)malloc(256 * sizeof(char));
    char *elt4 = (char *)malloc(256 * sizeof(char));
    char *elt5 = (char *)malloc(256 * sizeof(char));
    char *elt6 = (char *)malloc(256 * sizeof(char));
    char *elt7 = (char *)malloc(256 * sizeof(char));
    char *elt8 = (char *)malloc(256 * sizeof(char));
    int id;
    if (fic == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }
    // Lire chaque ligne du fichier jusqu'à EOF
    while (fgets(ligne, sizeof(ligne), fic) != NULL) {
        // Extraction des éléments de la ligne en utilisant sscanf
        int items_read = sscanf(ligne, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]",elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8);
        if (items_read == 8) {
            char *element[] = {elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8};
            if (atoi(element[3]) != 0) {
                id = atoi(element[3]);
            } else if (atoi(element[2]) != 0) {
                id = atoi(element[2]);
            } else if (atoi(element[1]) != 0) {
                id = atoi(element[1]);
            }
            // Rechercher le nœud correspondant dans l'AVL et mettre à jour sa consommation
            NoeudAVL *noeud = rechercher(n, id);
            if (noeud != NULL) {
                noeud->consommation += atoll(element[7]);
            } else {
                printf("Aucun nœud trouvé avec l'ID %d\n", id);
            }
        } else {
            printf("Erreur de format dans la ligne : %s\n", ligne);
        }
    }
    // Libération de la mémoire allouée pour les éléments
    free(elt1);
    free(elt2);
    free(elt3);
    free(elt4);
    free(elt5);
    free(elt6);
    free(elt7);
    free(elt8);
}

void parcours_prefixe(NoeudAVL * n){
  if (n==NULL){
    return ;
  }
  printf("%d;%lld;%lld\n", n->id,n->capacite,n->consommation);
  parcours_prefixe(n->gauche);
  parcours_prefixe(n->droite);

}

int main() {
    FILE *file = fopen("tmp/temp_station.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp_station.txt");
        return EXIT_FAILURE;
    }
    NoeudAVL *n = NULL;
    NoeudAVL *temp = lire_fichier_station(file);
    while (temp != NULL) {
        n = inserer(n, temp);
        temp = lire_fichier_station(file);
    }
    fclose(file);

    FILE *file2 = fopen("tmp/temp_usager.txt", "r");
    if (file2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp_usager.txt");
        free(n);
        return EXIT_FAILURE;
    }
    // Lire les usagers et modifier l'AVL
    lire_fichier_consommateur(file2, n);
    parcours_prefixe(n);
    fclose(file2);
    free(n);

}
