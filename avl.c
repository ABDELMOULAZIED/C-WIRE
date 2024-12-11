#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// Fonction max
int max(int a , int b) {
    return (a > b) ? a : b;
}

// Fonction pour créer un nœud AVL
NoeudAVL *creerNoeudAVL(char *elt[]) {
    NoeudAVL *racine = (NoeudAVL *)malloc(sizeof(NoeudAVL));
    if (racine == NULL) {
        perror("Erreur d'allocation mémoire");
        return NULL;
    }
    if (atoi(elt[3]) != 0) {
        racine->id = atoi(elt[3]);
    } else if (atoi(elt[2]) != 0) {
        racine->id = atoi(elt[2]);
    } else if (atoi(elt[1]) != 0) {
        racine->id = atoi(elt[1]);
    }
    racine->capacite = atoll(elt[6]);
    racine->id_centrale = atoi(elt[0]);
    racine->hauteur = 0;
    return racine;
}

// Rotation gauche
NoeudAVL *rotationGauche(NoeudAVL *racine) {
    NoeudAVL *temp = racine->droite;
    racine->droite = temp->gauche;
    temp->gauche = racine;
    racine->hauteur = 1 + max((racine->gauche ? racine->gauche->hauteur : -1), (racine->droite ? racine->droite->hauteur : -1));
    temp->hauteur = 1 + max((temp->gauche ? temp->gauche->hauteur : -1), (temp->droite ? temp->droite->hauteur : -1));
    return temp;
}

// Rotation droite
NoeudAVL *rotationDroite(NoeudAVL *racine) {
    NoeudAVL *temp = racine->gauche;
    racine->gauche = temp->droite;
    temp->droite = racine;
    racine->hauteur = 1 + max((racine->gauche ? racine->gauche->hauteur : -1), (racine->droite ? racine->droite->hauteur : -1));
    temp->hauteur = 1 + max((temp->gauche ? temp->gauche->hauteur : -1), (temp->droite ? temp->droite->hauteur : -1));
    return temp;
}


// Insertion dans l'AVL
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
    racine->hauteur = 1 + max((racine->gauche ? racine->gauche->hauteur : -1), (racine->droite ? racine->droite->hauteur : -1));
    int balance = (racine->droite ? racine->droite->hauteur : -1) - (racine->gauche ? racine->gauche->hauteur : -1);
    if (balance > 1 && nouveau->id > racine->droite->id) {
        return rotationGauche(racine);
    }
    if (balance < -1 && nouveau->id < racine->gauche->id) {
        return rotationDroite(racine);
    }
    if (balance > 1 && nouveau->id < racine->droite->id) {
        racine->droite = rotationDroite(racine->droite);
        return rotationGauche(racine);
    }
    if (balance < -1 && nouveau->id > racine->gauche->id) {
        racine->gauche = rotationGauche(racine->gauche);
        return rotationDroite(racine);
    }
    return racine;
}

// Recherche dans l'AVL
NoeudAVL *rechercher(NoeudAVL *racine, int id) {
    if (racine == NULL) {
        return NULL;
    }
    if (racine->id == id) {
        return racine;
    }
    if (id < racine->id) {
        return rechercher(racine->gauche, id);
    }
    return rechercher(racine->droite, id);
}

// Lecture d'un fichier pour les stations
NoeudAVL *lire_fichier_station(FILE *fic) {
    char ligne[256];
    char *elt1 = (char*)malloc(256 * sizeof(char));
    char *elt2 = (char*)malloc(256 * sizeof(char));
    char *elt3 = (char*)malloc(256 * sizeof(char));
    char *elt4 = (char*)malloc(256 * sizeof(char));
    char *elt5 = (char*)malloc(256 * sizeof(char));
    char *elt6 = (char*)malloc(256 * sizeof(char));
    char *elt7 = (char*)malloc(256 * sizeof(char));
    char *elt8 = (char*)malloc(256 * sizeof(char));
    NoeudAVL *racine = NULL;
    if (fic == NULL) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }
    if (fgets(ligne, sizeof(ligne), fic) != NULL) {
        int items_read = sscanf(ligne, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8);
        if (items_read == 8) {
            char *element[] = {elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8};
            racine = creerNoeudAVL(element);
        }
    }
    free(elt1);
    free(elt2);
    free(elt3);
    free(elt4);
    free(elt5);
    free(elt6);
    free(elt7);
    free(elt8);
    return racine;
}

void lire_fichier_consommateur(FILE *fic, NoeudAVL *racine) {
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
            NoeudAVL *noeud = rechercher(racine, id);
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

void traiter_Arbre(NoeudAVL* racine) {
if(racine==NULL){
return;
}
printf("%d %lld %lld\n", racine->id, racine->capacite, racine->consommation);
}


void parcoursPrefixe(NoeudAVL* racine) {
    if (racine == NULL){
    return;
    }
    traiter_Arbre(racine);
  parcoursPrefixe(racine->gauche);
  parcoursPrefixe(racine->droite);
}

void liberer_Arbre(NoeudAVL* racine) {
    if (racine == NULL){
      return;
    }
    liberer_Arbre(racine->gauche);
    liberer_Arbre(racine->droite);
    free(racine);
}
