#include <stdio.h>
#include <stdlib.h>

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
