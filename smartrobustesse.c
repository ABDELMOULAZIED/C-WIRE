#include <stdio.h>
#include <stdlib.h>

int verifierID(char *str) {
    int id_temp = atoi(str);
    if (id_temp > 0) {
        return id_temp;
    }
    return 0; // C'est pas valide donc dans le programme on return NULL
}
