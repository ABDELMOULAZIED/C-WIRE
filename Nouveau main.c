#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"


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

void parcours_pre(NoeudAVL * n){
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
    free_Arbre(n);

}
