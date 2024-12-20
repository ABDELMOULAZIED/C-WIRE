#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    FILE *file = fopen("tmp/temp_station.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp_station.txt");
        return 1;
    }
    NoeudAVL *n = NULL;
    NoeudAVL *temp = MEP_Stations(file);
    while (temp != NULL) {
        n = insererAVL(n, temp);
        temp = MEP_Stations(file);
    }
    fclose(file);
    if (n == NULL){
      perror("Erreur lors de la construction AVL");
      return 1;
    }

    FILE *file2 = fopen("tmp/temp_usager.txt", "r");
    if (file2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp_usager.txt");
        free(n);
        return 1;
    }
    MAJ_Stations(file2, n);
    parcoursPrefixe(n);
    fclose(file2);
    liberer_Arbre(n);

    return 0;
}
