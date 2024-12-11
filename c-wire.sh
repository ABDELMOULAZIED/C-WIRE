#!/bin/bash

# Fonction d'aide
aide() {
    echo "Usage: $0 [OPTIONS][FICHIER][STATION][CONSOMMATEUR][ID CENTRALE]"
    echo "Options :"
    echo "  -h    Affiche ce message d'aide et arrête l'exécution"
    echo "Fichier :"
    echo "   Fichier .dat existant requis"
    echo "Station :"
    echo -e "   Indiquer le type de station a étudier :\n   hvb : Station de haut voltage B\n   hva : Station de haut voltage A\n   lv : Station de faible voltage"
    echo "Consommateur :"
    echo -e "   Indiquer le type de consommateur a étudier :\n   comp : Entreprises\n   indiv : Particuliers\n   all : Particuliers et Entreprises\n   A noter que les stations de haut voltage ne sont pas connecté aux particuliers."
    echo "Id Centrale :"
    echo -e "   Indiquer un identifiant de centrale, l'option est optionnelle et doit être un numéro x compris entre 0<x<n où n est le nombre de centrale."
    
    exit 1

}

# Vérification des arguments pour l'option -h
for arg in "$@"; do
    if [[ "$arg" == "-h" ]]; then
        aide
    fi
done




# Vérification des paramètres d'entré 
verif(){

	# Vérification que les trois options obligatoires sont présentes.
	if [ $# -lt 3 ]; then
		echo "Erreur : Vous devez passer au minimum 3 arguments en paramètre"
		return -1
	fi
	
	# Vérification que le fichier existe et son extension.
	if [[ -f "$arg1" && "$arg1" == *.dat ]]; then
	    :
	else
	    echo "Erreur : '$arg1' n'est pas un fichier .dat valide."
	    return -1
	fi

	# Vérification du second argument concernant les stations a traiter.
	if [[ "$arg2" != "hvb" && "$arg2" != "hva" && "$arg2" != "lv" ]]; then
		echo "Erreur : les stations a traiter sont : hvb ; hva ; lv "
		return -1
	fi


	# Vérification du troisième argument concernant les usagers a traiter.
	if [[ "$arg3" != "comp" && "$arg3" != "indiv" && "$arg3" != "all" ]]; then
		echo "Erreur : les consommateurs a traiter sont : comp ; indiv ; all "
		return -1
	fi
	
	ligne_fin=$(tac "$arg1" | grep -v '^[[:space:]]*$' | head -n 1 | awk -F';' '{print $1}')
	# Vérification du quatrième argument 
	if [[ -n "$arg4" && ! "$arg4" =~ ^[0-9]+$ || -n "$arg4" && "$ligne_fin" -lt "$arg4" ]];then
		echo "Erreur : Mauvais identifiant de central"
		return -1
	fi
}

# Création des dossiers utile au programme
crea_doss(){
	doss="tmp"
	if [ ! -d "$doss" ] ; then
		mkdir "$doss"
	else
		rm -rf $doss/{*,.*} 2>/dev/null
	fi
	doss="graphs"
	if [ ! -d "$doss" ] ; then
		mkdir "$doss"
	fi
	doss="rendu"
	if [ ! -d "$doss" ] ; then
		mkdir "$doss"
	fi
}
# Récupération des donnés sur la centrale et ses usagers.
recup_donne(){
	arg_fus="$arg2 $arg3"
	case "$arg_fus" in
		"hvb comp")
		if [ -z "$arg4" ];then
			station=$(grep  -P "^(\d+);(\d+);-;-;-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^(\d+);(\d+);-;-;(\d+);-;-;(\d+)" $arg1)
		else
			station=$(grep  -P "^($arg4);(\d+);-;-;-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^($arg4);(\d+);-;-;(\d+);-;-;(\d+)" $arg1)
		fi
		;;
		"hva comp")
		if [ -z "$arg4" ];then
			station=$(grep  -P "^(\d+);(\d+);(\d+);-;-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^(\d+);-;(\d+);-;(\d+);-;-;(\d+)" $arg1)
		else
			station=$(grep  -P "^($arg4);(\d+);(\d+);-;-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^($arg4);-;(\d+);-;(\d+);-;-;(\d+)" $arg1)
		fi
		;;
		"lv comp")
		if [ -z "$arg4" ];then
			station=$(grep  -P "^(\d+);-;(\d+);(\d+);-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^(\d+);-;-;(\d+);(\d+);-;-;(\d+)" $arg1)
		else
			station=$(grep  -P "^($arg4);-;(\d+);(\d+);-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^($arg4);-;-;(\d+);(\d+);-;-;(\d+)" $arg1)
		fi
		;;
		"lv indiv")
		if [ -z "$arg4" ];then
			station=$(grep  -P "^(\d+);-;(\d+);(\d+);-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^(\d+);-;-;(\d+);-;(\d+);-;(\d+)" $arg1)
		else 
			station=$(grep  -P "^($arg4);-;(\d+);(\d+);-;-;(\d+);-" $arg1)
			usagers=$(grep  -P "^($arg4);-;-;(\d+);-;(\d+);-;(\d+)" $arg1)
		fi
		;;
		"lv all")
		if [ -z "$arg4" ];then
			station=$(grep  -P "^(\d+);-;(\d+);(\d+);-;-;(\d+);-" $arg1)
			usagers_1=$(grep  -P "^(\d+);-;-;(\d+);(\d+);-;-;(\d+)" $arg1)
			usagers_2=$(grep  -P "^(\d+);-;-;(\d+);-;(\d+);-;(\d+)" $arg1)
		else
			station=$(grep  -P "^($arg4);-;(\d+);(\d+);-;-;(\d+);-" $arg1)
			usagers_1=$(grep  -P "^($arg4);-;-;(\d+);(\d+);-;-;(\d+)" $arg1)
			usagers_2=$(grep  -P "^($arg4);-;-;(\d+);-;(\d+);-;(\d+)" $arg1)
		fi
		usagers="$usagers_1\n$usagers_2"
		;;
		*)
		echo "Erreur : mode $arg_fus non pris en charge."
		exit -1
	esac
}

# Calcul le temps d'exécution d'une fonction passé en paramètre
timer(){
	local Nom="$1"
	local Fonction="$2"
	
	start_timer=$(date +%s)
	
	$Fonction "$arg1" "$arg2" "$arg3" "$arg4"
	local statut=$?
	
	end_timer=$(date +%s)
	
	if [ $statut -eq 0 ]; then
		duree=$(echo "$end_timer - $start_timer " | bc)
		echo "$Nom : $duree secondes"
	else
		duree=0
		echo "Erreur dans le traitement de la fonction $Fonction"
		echo "Durée de la fonction $Nom : $duree secondes"
		aide
		exit 1
		
	fi
	
	 
}


ecriture(){
    cat > tmp/temp_station.txt <<< "$station"
    cat > tmp/temp_usager.txt <<< "$usagers"	

}

# Fonction pour vérifier et exécuter l'exécutable Main
lancement_C() {
    # Nom de l'exécutable
    EXECUTABLE="Main"

    # Vérifier si l'exécutable existe et est accessible
    if [ -x "$EXECUTABLE" ]; then
        touch rendu/Donne_conso.txt
        ./$EXECUTABLE > rendu/Donne_conso.txt
    else
        make
        touch rendu/Donné_conso.txt
        ./$EXECUTABLE > rendu/Donné_conso.txt
    fi
}

arg1="$1"
arg2="$2"
arg3="$3"
arg4="$4"

barre_de_progression() {
    local nombre_total_etapes="$2"
    local etape_actuelle="$1"
    local progression=$((etape_actuelle * 100 / nombre_total_etapes)) #Pourcentage de progression
    local longueur_barre=20  #Longueur de la barre de progression
    local longueur_remplie=$((etape_actuelle * longueur_barre / nombre_total_etapes)) #Partie de la barre de progression censée être remplie 

    # Construire la barre de progression
    local barre=""
    for ((i=0; i<longueur_remplie; i++)); do
        barre="$barre#" #On ajoute ici des # pour chaque partie remplie de la barre.
    done
    for ((i=longueur_remplie; i<longueur_barre; i++)); do
        barre="$barre-" #On rajoute des - la ou la barre de progression est vide.
    done

    # Afficher la barre de progression
    printf "\r[%s] %d%% " "$barre" "$progression"
}
main(){
	local start_main=$(date +%s)
	nombre_total_etapes=5
	etape_actuelle=0


	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "Durée de la vérification des arguments" "verif"


	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "Durée de la création des dossiers" "crea_doss"


	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "Durée de la récupération des données" "recup_donne"


	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "Durée de l'écriture des fichiers temporaires" "ecriture"


	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "Durée de l'exécution du programme C" "lancement_C"
	echo "Fin de procédure le fichier final se trouve dans le dossier rendu" 
	local end_main=$(date +%s)
	duree=$(echo "$end_main - $start_main " | bc)
		echo "Durée du Script Shell : $duree secondes"
}
main
