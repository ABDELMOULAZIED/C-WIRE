#include <stdio.h>
#include <stdlib.h>

int verifierID(char *str) {
    int id_temp = atoi(str);
    if (id_temp > 0) {
        return id_temp;
    }
    return 0; // C'est pas valide donc dans le programme on return NULL
}


long long verifierCapacite(char *str) {
    long long capa_temp = atoi(str);
    if (capa_temp >= 0) {
        return capa_temp;
    }
    return 0; //je ne sais pas si je return 0 ou -1 si on a une capa de 0, on verra
}
