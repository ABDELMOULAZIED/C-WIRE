Reste a faire : 
- Renommer les variables et/ou annotations (faite par chatgpt) , souvent hors sujet pcq je me perd dans ce que je fait comme les fonction lire qui en fait ne font pas que lire 
- Separer le code AVL.h AVL.c etc...
- Verifier la robustesse du code.


#include <stdio.h>
#include <stdlib.h>

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
    NoeudAVL *n = (NoeudAVL *)malloc(sizeof(NoeudAVL));
    if (n == NULL) {
        perror("Erreur d'allocation mémoire");
        return NULL; // Gestion de l'erreur d'allocation
    }
    // Extraction des id et du type en fonction des conditions
    if (atoi(elt[3]) != 0) {
        n->id =atoi(elt[3]);
    } else if (atoi(elt[2]) != 0) {
        n->id =atoi(elt[2]);
    } else if(atoi(elt[1]) != 0) {
        n->id =atoi(elt[1]);
    }
    // Initialisation de la capacité
    n->capacite = atoll(elt[6]);
    n->id_centrale = atoi(elt[0]);
    // Initialisation de la hauteur
    n->hauteur = 0;
    return n;
}

NoeudAVL * rotationGauche(NoeudAVL * n) {
    NoeudAVL * temp = n->droite;   // Le sous-arbre droit devient la nouvelle racine.
    n->droite = temp->gauche;      // Le sous-arbre gauche de temp devient le sous-arbre droit de n.
    temp->gauche = n;              // n devient le sous-arbre gauche de temp.
    
    // Mise à jour des hauteurs
    n->hauteur = 1 + max((n->gauche ? n->gauche->hauteur : -1), (n->droite ? n->droite->hauteur : -1));
    temp->hauteur = 1 + max((temp->gauche ? temp->gauche->hauteur : -1), (temp->droite ? temp->droite->hauteur : -1));
    
    return temp;  // Retourne la nouvelle racine (temp).
}

NoeudAVL * rotationDroite(NoeudAVL * n) {
    NoeudAVL * temp = n->gauche;   // Le sous-arbre gauche devient la nouvelle racine.
    n->gauche = temp->droite;      // Le sous-arbre droit de temp devient le sous-arbre gauche de n.
    temp->droite = n;              // n devient le sous-arbre droit de temp.
    
    // Mise à jour des hauteurs
    n->hauteur = 1 + max((n->gauche ? n->gauche->hauteur : -1), (n->droite ? n->droite->hauteur : -1));
    temp->hauteur = 1 + max((temp->gauche ? temp->gauche->hauteur : -1), (temp->droite ? temp->droite->hauteur : -1));
    
    return temp;
}


NoeudAVL* inserer(NoeudAVL* n, NoeudAVL* nouveau) {
    if (n == NULL) {
        return nouveau;
    }
    if (nouveau->id < n->id) {
        n->gauche = inserer(n->gauche, nouveau);
    } else if (nouveau->id > n->id) {
        n->droite = inserer(n->droite, nouveau);
    } else {
        return n;
    }
    // Mise à jour de la hauteur du nœud courant.
    n->hauteur = 1 + max((n->gauche ? n->gauche->hauteur : -1),(n->droite ? n->droite->hauteur : -1));
    // Calcul du facteur d'équilibre (droite - gauche)
    int balance = (n->droite ? n->droite->hauteur : -1) - (n->gauche ? n->gauche->hauteur : -1);
    // Cas 1 : Déséquilibre à droite.
    if (balance > 1 && nouveau->id > n->droite->id) {
        return rotationGauche(n);
    }
    // Cas 2 : Déséquilibre à gauche.
    if (balance < -1 && nouveau->id < n->gauche->id) {
        return rotationDroite(n);
    }
    // Cas 3 : Déséquilibre droite-gauche.
    if (balance > 1 && nouveau->id < n->droite->id) {
        n->droite = rotationDroite(n->droite);
        return rotationGauche(n);
    }
    // Cas 4 : Déséquilibre gauche-droite.
    if (balance < -1 && nouveau->id > n->gauche->id) {
        n->gauche = rotationGauche(n->gauche);
        return rotationDroite(n);
    }
    return n; // Retourne la nouvelle racine locale.
}

NoeudAVL *rechercher(NoeudAVL *n, int id) {
    if (n == NULL) {
        return NULL;
    }
    if (n->id == id) {
        return n;
    }
    if (id < n->id) {
        return rechercher(n->gauche, id);
    }
    return rechercher(n->droite, id);
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

void parcours_pre(NoeudAVL * n){
  if (n==NULL){
    return ;
  }
  printf("Id :%d , Capacité :%lld , hauteur : %d , Consommation : %lld\n", n->id,n->capacite,n->hauteur,n->consommation);
  parcours_pre(n->gauche);
  parcours_pre(n->droite);

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
    printf("Parcours pré-ordre de l'AVL après chargement des stations :\n");
    parcours_pre(n);
    fclose(file);

    FILE *file2 = fopen("tmp/temp_usager.txt", "r");
    if (file2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp_usager.txt");
        free(n);
        return EXIT_FAILURE;
    }
    // Lire les usagers et modifier l'AVL
    lire_fichier_consommateur(file2, n);
    
    printf("Parcours pré-ordre de l'AVL après chargement des usagers :\n");
    parcours_pre(n);
    fclose(file2);
    free(n);

}
