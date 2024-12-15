#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Fonction vérification de l'allocation mémoire 
void* safeMalloc(size_t size) { // Type size_t, type non signé pour représenter la taille de qqc en mémoire
    void* temp = malloc(size);
    if (temp == NULL) {
       perror("Erreur : impossible d'allouer %zu octets de mémoire\n");
        exit(EXIT_FAILURE); 
    }
    return temp;
}


// Vérifier si l'élément est non vide 
int Verif_Elt(char *elt[]) {
    for (int i = 0; i < 8; i++) {
        if (elt[i] == NULL || strlen(elt[i]) == 0) {
            printf("Erreur, L'élément %d est vide.\n", i + 1);
            return 0;}
    }
    return 1;
}






int verifierID(char *str) {
    int id_temp = atoi(str);
    if (id_temp > 0) {
        return id_temp;
    }
    return 0; // C'est pas valide donc dans le programme on return NULL
}

// on cop colle vérifierID en adaptant le onom de la fonction et les variables 
long long verifierCapacite(char *str) {
    long long capa_temp = atoi(str);
    if (capa_temp >= 0) {
        return capa_temp;
    }
    return 0; //je ne sais pas si je return 0 ou -1 si on a une capa de 0, on verra
}

// on cop colle vérifierID en adaptant le onom de la fonction et les variables 
long long verifierConsommation(char *str) {
    long long conso_temp = atoi(str);
    if (conso_temp > 0) {
        return conso_temp;
    }
    return 0; //pareil ici, c'est du cop colle de verifier capa mais je ne sias pas si la capa peut être égale à 0 ou c'est strictement supérieur à 0
}

