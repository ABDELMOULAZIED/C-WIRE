/*
Creation d'un tableau 
Chaque case du tableau est l'ensemble des stations raccroché a la station numero[case]
id < 10 = Centrale
10<id<200 = HVB
200<id<1000 = HVA
id>1000 = LV
Code partiellement corrigé avec CHATGPT si vous voyez quelque chose qui peut se faire + "humainement" allez y
Pour l'instant affiche les stations lié a la centrale 1

Reste a faire : 
  Insertion de la consommation (J'ai separé les fichier de sortie Shell en deux )
  DONC 
  Prendre les fichier dans temp_usager.txt
  Retrouver la station correspondante
  MAJ sa consommation 
  MAJ conso parent
  MAJ conso parent->parent
  Surement creer une fonction RechercheId (Simple)
  Fin

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int id_parent;
  int id_centrale;
  int id;
  long long capacite;
  long consommation;
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
        n->id = 1000 + atoi(elt[3]);
        n->id_parent = 200+atoi(elt[2]);
        n->id_centrale = atoi(elt[0]);
    } else if (atoi(elt[2]) != 0) {
        n->id = 200 + atoi(elt[2]);
        n->id_parent = 10+atoi(elt[1]);
        n->id_centrale = atoi(elt[0]);
    } else if(atoi(elt[1]) != 0) {
        n->id = 10 + atoi(elt[1]);
        n->id_centrale = atoi(elt[0]);
        n->id_parent = -1;
    }
    else{
        n->id = atoi(elt[0]);
        n->id_parent = -1;
        n->id_centrale = -1;

    }
    // Initialisation de la capacité
    n->capacite = atoll(elt[6]);

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
    
    return temp;  // Retourne la nouvelle racine (temp).
}


NoeudAVL* inserer(NoeudAVL* n, NoeudAVL* nouveau) {
    if (n == NULL) {
        return nouveau; // Insère le nouveau nœud ici.
    }

    if (nouveau->id < n->id) {
        n->gauche = inserer(n->gauche, nouveau); // Insertion dans le sous-arbre gauche.
    } else if (nouveau->id > n->id) {
        n->droite = inserer(n->droite, nouveau); // Insertion dans le sous-arbre droit.
    } else {
        return n; // Pas de duplication des clés.
    }

    // Mise à jour de la hauteur du nœud courant.
    n->hauteur = 1 + max((n->gauche ? n->gauche->hauteur : -1), 
                         (n->droite ? n->droite->hauteur : -1));

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


NoeudAVL * lire_fichier(FILE *fic) {
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
        int items_read = sscanf(ligne, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]",
                                elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8);
        
        // Vérification si tous les champs ont été lus correctement
        if (items_read == 8) {
            // Création d'un tableau d'éléments pour passer à la fonction creerNoeud
            char *element[] = {elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8};
            n = creerNoeud(element);
        } else {
            printf("Erreur de format dans la ligne: %s\n", ligne);
        }
    } else {
        printf("Erreur de lecture du fichier ou fin de fichier atteinte.\n");
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

void parcours_pre(NoeudAVL * n){
  if (n==NULL){
    return ;
  }
  printf("Id :%d , Capacité :%lld , hauteur : %d\n", n->id,n->capacite,n->hauteur);
  parcours_pre(n->gauche);
  parcours_pre(n->droite);

}

int main(){
	FILE * file = fopen("tmp/temp_station.txt", "r");
	NoeudAVL * n;
	NoeudAVL* arbresAVL[10]={NULL};
        n = lire_fichier(file);
        while(n!=NULL){
          if (n->id < 10){
            arbresAVL[n->id] = n;
          }
          else{
            arbresAVL[n->id_centrale] = inserer(arbresAVL[n->id_centrale],n);
          }
          n=lire_fichier(file);
      }
  parcours_pre(arbresAVL[1]);
	fclose(file);
}
