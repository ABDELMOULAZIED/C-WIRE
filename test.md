## Description Générale

- **Filtrage des Données**: Extraire les informations qui nous intéressent à partir d’un fichier CSV.
- **Traitement des Données**: Calculer la somme des consommations par station en utilisant un AVL.
- **Analyse de Performance**: Déterminer les situations de surproduction ou de sous-production d’énergie et évaluer la répartition de la consommation entre entreprises et particuliers.
- **Génération de Rapports**: Sauvegarder les résultats dans des fichiers CSV et créer des graphiques pour visualiser les données.
  
## Description des Programmes

### Script Shell (`c-wire.sh`)

Ce script gère l'ensemble du programme, depuis le filtrage des données jusqu'à la génération des rapports et des graphiques. Il s'assure également que le programme C est correctement compilé et exécuté.

### Programme C (`codeC/main.c & avl.c` )

Le programme C est responsable du calcul des consommations en utilisant un AVL. Il lit les données filtrées, effectue les calculs nécessaires et génère les fichiers de sortie.

### Makefile (`codeC/Makefile`)

Le Makefile automatise la compilation du programme C. Il contient des commandes pour compiler le projet et nettoyer les fichiers générés.



## Prérequis :

**Compiler le Programme C**
    Entrer dans le dossier `codeC` et compilez le programme en utilisant `make`
    Entrer `cd -` pour sortir du dossier et effectuer les étapes suivantes. 

## Guide d'utilisation :

Le script principal du projet est `c-wire.sh`. Il est important de l'exécuter depuis la racine du projet (`C-Wire/`) et non depuis le répertoire `codeC/`.


### Syntaxe de la Commande

`./c-wire.sh [OPTIONS] [FICHIER] [STATION] [CONSOMMATEUR] [ID_CENTRALE]`


### Description des Paramètres

- **`[OPTIONS]`** (Optionnel)
    - `-h` : Affiche l'aide détaillée.
    - `-e` : Active le rapport d'efficience (bonus).
      
- **`[FICHIER]`** (Obligatoire)
    - Chemin vers le fichier CSV d'entrée. Exemple : ` c-wire_v25.dat`
      
- **`[STATION]`** (Obligatoire)
    - Type de station à traiter :
        - `hvb` : High Voltage B
        - `hva` : High Voltage A
        - `lv` : Low Voltage
          
- **`[CONSOMMATEUR]`** (Obligatoire)
    - Type de consommateur à analyser :
        - `comp` : Entreprises
        - `indiv` : Particuliers
        - `all` : Tous
          
- **`[ID_CENTRALE]`** (Optionnel)
    - Identifiant d'une centrale spécifique. Si oublié, toutes les centrales sont prises en compte.


### Exemples d'Exécution

##### Afficher l’aide

Affiche une aide détaillée sur l’utilisation du script, incluant la description des paramètres et des options disponibles.
`./c-wire.sh -h`

**Sortie Attendue**:

- Description détaillée de l’utilisation du script.
- Explication des paramètres et des options disponibles.
![[c-wire1.jpg]]

#### Exemple 1 : Analyser les Postes LV pour Tous les Consommateurs

1. **Commande**
    `./c-wire.sh fichier_du_sujet lv all`
    
2. **Explication**
    - **Filtrer** les données pour les postes Low Voltage (`lv`).
    - **Analyser** tous les types de consommateurs (`all`).
    - **Centrale** : Toutes les centrales sont prises en compte car aucun identifiant n'est spécifié.
      
3. **Résultat Attendu**
    - Génération du fichier `lv_all.csv` dans le dossier `rendu/`, contenant :
        - Identifiant du poste LV
        - Capacité en kWh
        - Consommation totale des consommateurs en kWh
![[c-wire2.jpg]]


#### Exemple 2 : Analyser les Postes LV pour Tous les Consommateurs dans une Centrale Spécifique (ID Centrale : 2) 
1. **Commande**
    `./c-wire.sh fichier_du_sujet lv all 2 `
    
2. **Explication**
    - **Filtrer** les données pour les postes Low Voltage (`lv`).
    - **Analyser** tous les types de consommateurs (`all`).
    - **Centrale** : Identifier spécifiquement la centrale numéro `2`.
      
3. **Résultat Attendu**
    - Génération du fichier `lv_all_2.csv` dans le dossier `rendu/`, contenant :
        - Identifiant du poste LV
        - Capacité en kWh
        - Consommation totale des consommateurs en kWh
![[c-wire3.jpg]]

#### Exemple 3 : Analyser les Postes LV pour Tous les Consommateurs avec Rapport d’Efficience

1. **Commande**
    `./c-wire.sh -e fichier_du_sujet lv all `
    
2. **Explication**
    - **Filtrer** les données pour les postes Low Voltage (`lv`).
    - **Analyser** tous les types de consommateurs (`all`).
    - **Centrale** : Toutes les centrales sont prises en compte car aucun identifiant n'est spécifié.
    - **Option** : `-e` pour activer le rapport d'efficience.
      
3. **Résultat Attendu**
    - Génération du fichier `lv_all.csv` dans le dossier `rendu/`, contenant :
        - Identifiant du poste LV
        - Capacité en kWh
        - Consommation totale des consommateurs en kWh
          
    - Avec l’option `-e` :
        - Création du fichier `lv_all_minmax.csv` dans `rendu/`, listant les 10 postes LV les plus et les 10 postes LV les moins consommés.
        - Génération des graphiques correspondants dans le dossier `graphs/`, illustrant ces postes avec des couleurs indiquant la surconsommation (rouge) ou la marge (vert).
![[c-wire4.jpg]]

### Vérifier les Résultats

1. **Accéder au Dossier des Résultats**
    `cd rendu ls`
    
2. **Consulter un Fichier de Sortie**
    Par exemple, pour afficher le contenu de `lv_all.csv`, exécutez :
    `cat lv_all.csv`
    ![[c-wire5.jpg]]
3. **Visualiser les Graphiques (si l’option `-e` est utilisée)**
    Les graphiques sont générés dans le dossier `graphs/` si l’option `-e` a été utilisée. Vous pouvez les ouvrir avec votre visualiseur d'images préféré ou en utilisant GnuPlot. Par exemple :
    `gnuplot graphs/lv_all_minmax_2.gp`
    
    Ou ouvrez directement l'image générée :
    `xdg-open graphs/lv_all_minmax_2.png`
Le script principal du projet est `c-wire.sh`. Il est important de l'exécuter depuis la racine du projet (`C-Wire/`) et non depuis le répertoire `codeC/`.


### Nettoyer l'Environnement

Si vous souhaitez supprimer les fichiers temporaires ou réinitialiser l'environnement, vous pouvez exécuter le script avec l'option `clean` ou le faire manuellement.

1. **Supprimer les Fichiers Temporaires**
    `rm -rf tmp/*`
    
2. **Nettoyer la Compilation**
    Naviguez dans le dossier `codeC` et exécutez `make clean` :
    `cd codeC 
	`make clean 
	`cd ..`
    
    Cela supprimera l’exécutable généré lors de la compilation.


