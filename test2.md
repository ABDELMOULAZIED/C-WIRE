# Sommaire : 
![[## Description Générale]]
![[## Prérequis ]]
![[## Guide d'utilisation :]]
![[## Description des Programmes]]
![[## Commandes interdites :]]
![[#Carnet de bord de Commandes]]


## Description Générale :

- **Filtrage des Données**: Extraire les informations qui nous intéressent à partir d’un fichier CSV.
- **Traitement des Données**: Calculer la somme des consommations par station en utilisant un AVL.
- **Analyse de Performance**: Déterminer les situations de surproduction ou de sous-production d’énergie et évaluer la répartition de la consommation entre entreprises et particuliers.
- **Génération de Rapports**: Sauvegarder les résultats dans des fichiers CSV et créer des graphiques pour visualiser les données.
  

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
    - `-i` : Trier par identifiant de station
    - `-c` : Trier par consommation des stations
	
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

#### Afficher l’aide

Affiche une aide détaillée sur l’utilisation du script, incluant la description des paramètres et des options disponibles.
`./c-wire.sh -h`

**Sortie Attendue**:

- Description détaillée de l’utilisation du script.
- Explication des paramètres et des options disponibles.

![c-wire1](https://github.com/user-attachments/assets/318919e3-73c2-4ddd-8e62-7c8eaca1ca29)


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

![c-wire2](https://github.com/user-attachments/assets/0d837fa5-ff9d-4218-b03d-6e1896445d05)



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

![c-wire3](https://github.com/user-attachments/assets/19a6092b-2ea3-4943-9bb4-adcc2f21a5fd)


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

![c-wire4](https://github.com/user-attachments/assets/c921045b-ade2-451a-94d4-ef46976970a3)


### Vérifier les Résultats

1. **Accéder au Dossier des Résultats**
    `cd rendu ls`
    
2. **Consulter un Fichier de Sortie**
    Par exemple, pour afficher le contenu de `lv_all.csv`, exécutez :
    `cat lv_all.csv`
   
    ![c-wire5](https://github.com/user-attachments/assets/17dbef67-0e3b-4fbf-be38-fcd522969030)

4. **Visualiser les Graphiques (si l’option `-e` est utilisée)**
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

## Description des Programmes :

### Script Shell (`c-wire.sh`)

Ce script gère l'ensemble du programme, depuis le filtrage des données jusqu'à la génération des rapports et des graphiques. Il s'assure également que le programme C est correctement compilé et exécuté.

### Programme C (`codeC/main.c & avl.c` )

Le programme C est responsable du calcul des consommations en utilisant un AVL. Il lit les données filtrées, effectue les calculs nécessaires et génère les fichiers de sortie.

### Makefile (`codeC/Makefile`)

Le Makefile automatise la compilation du programme C. Il contient des commandes pour compiler le projet et nettoyer les fichiers générés.


## Commandes interdites :

| Station | Consommateur | Explication de l'interdiction                                     |
| ------- | ------------ | ----------------------------------------------------------------- |
| `hvb`   | `all`        | Seules les entreprises (`comp`) sont connectées aux stations HV-B |
| `hvb`   | `indiv`      | Seules les entreprises (`comp`) sont connectées aux stations HV-B |
| `hva`   | `all`        | Seules les entreprises (`comp`) sont connectées aux stations HV-A |
| `hva`   | `indiv`      | Seules les entreprises (`comp`) sont connectées aux stations HV-A |


## Carnet de bord de Commandes :

### 1. Afficher l'Aide

**Commande :**
`./c-wire.sh -h`

**Ce que fait cette commande :**
- Affiche une description détaillée de toutes les options et paramètres disponibles.

### 2. Analyser les Stations HV-B pour les Entreprises

**Commande :**
`./c-wire.sh input/DATA_CWIRE.csv hvb comp`

**Ce que fait cette commande :**
- Filtrer les données pour les stations High Voltage B (`hvb`).
- Analyser les consommateurs de type entreprises (`comp`).
- Centrale : Toutes les centrales sont prises en compte car aucun identifiant spécifique n'est donné.

**Résultat Attendu :**
Un fichier appelé `hvb_comp.csv` sera généré dans le dossier `rendu/`, contenant :
- Identifiant de la station HV-B
- Capacité en kWh
- Consommation totale des entreprises en kWh

### 3. Analyser les Postes LV pour Tous les Consommateurs dans une Centrale Spécifique avec Rapport d’Efficience

**Commande :**
`./c-wire.sh -e input/DATA_CWIRE.csv lv all 2 

**Ce que fait cette commande :**
- Filtrer les données pour les postes Low Voltage (`lv`).
- Analyser tous les types de consommateurs (`all`).
- Centrale : Filtre pour la centrale numéro `2`.
- Option : `-e` pour activer le rapport d'efficience.

**Résultat Attendu :**
- Génération du fichier `lv_all_2.csv` dans le dossier `rendu/`, contenant :
    - Identifiant du poste LV
    - Capacité en kWh
    - Consommation totale des consommateurs en kWh
- Avec l’option `-e` :
    - Création du fichier `lv_all_minmax_2.csv` dans `rendu/`, listant les 10 postes LV les plus consommés et les 10 postes LV les moins consommés.
    - Génération des graphiques dans le dossier `graphs/`, ils illustrent ces postes avec des couleurs indiquant la surconsommation (rouge) ou la marge (vert).

### 4. Analyser les Postes HV-A pour les Entreprises avec Rapport d’Efficience

**Commande :**
`./c-wire.sh -e input/DATA_CWIRE.csv hva comp 3`

**Ce que fait cette commande :**
- Filtrer les données pour les stations High Voltage A (`hva`).
- Analyser les consommateurs de type entreprises (`comp`).
- Centrale : Filtre pour la centrale numéro `3`.
- Option : `-e` pour activer le rapport d'efficience.

**Résultat Attendu :**
- Génération du fichier `hva_comp_3.csv` dans le dossier `rendu/`, contenant :
    - Identifiant de la station HV-A
    - Capacité en kWh
    - Consommation totale des entreprises en kWh
- Avec l’option `-e` :
    - Création du fichier `lv_all_minmax_2.csv` dans `rendu/`, listant les 10 postes LV les plus consommés et les 10 postes LV les moins consommés.
    - Génération des graphiques dans le dossier `graphs/`, ils illustrent ces postes avec des couleurs indiquant la surconsommation (rouge) ou la marge (vert).

### 5. Analyser les Postes HV-A pour les Particuliers

**Commande :**
`./c-wire.sh input/DATA_CWIRE.csv hva indiv`

**Ce que fait cette commande :**
- Filtrer les données pour les stations High Voltage A (`hva`).
- Analyse les consommateurs de type particuliers (`indiv`).
- Centrale : Toutes les centrales sont prises en compte car aucun identifiant spécifique n'est donné.

**Attention :** Selon le descriptif des paramètres certaines combinaisons peuvent être interdites. Vérifiez que `hva indiv` est une combinaison valide.

### 6. Analyser les Postes HV-B pour les Particuliers

**Commande :**
`./c-wire.sh input/DATA_CWIRE.csv hvb indiv`

**Ce que fait cette commande :**
- Filtrer les données pour les stations High Voltage B (`hvb`).
- Analyser les consommateurs de type particuliers (`indiv`).
- Centrale : Toutes les centrales sont prises en compte car aucun identifiant spécifique n'est fourni.

**Attention :** Certaines combinaisons comme `hvb indiv` peuvent être interdites car seules les entreprises sont connectées aux stations HV-B et HV-A.
