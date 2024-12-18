#!/bin/bash


# Fonction d'aide
aide() {
    echo "Usage : $0 [OPTIONS] [FICHIER] [STATION] [CONSOMMATEUR] [ID CENTRALE]"
    echo "Options :"
    echo -e "  -h    Affiche ce message d'aide et arrête l'exécution\n  -e    Ajoute le rapport d'efficience\n  -i    Trie le fichier de rendu par identifiant de station\n  -c    Trie le fichier de rendu par la consommation des stations"
    echo "Fichier :"
    echo "   Fichier .dat existant requis"
    echo "Station :"
    echo -e "   Indiquer le type de station à étudier :\n   hvb : Station de haut voltage B\n   hva : Station de haut voltage A\n   lv : Station de faible voltage"
    echo "Consommateur :"
    echo -e "   Indiquer le type de consommateur à étudier :\n   comp : Entreprises\n   indiv : Particuliers\n   all : Particuliers et Entreprises\n   À noter que les stations de haut voltage ne sont pas connectées aux particuliers."
    echo "Id Centrale :"
    echo -e "   Indiquer un identifiant de centrale, l'option est optionnelle et doit être un numéro x compris entre 0 < x < n où n est le nombre de centrales."
    
    exit 1
}





activer_efficience=false
tri=""
    while getopts ":ehaci" opt; do
        case $opt in
            e)
                activer_efficience=true
                tri="eff"
                ;;
            h)
            	aide
            	;;
            c)
            	tri="conso"
            	;;
            i)
            	tri="id"
            	;;
            \?)
                echo "Option invalide : -$OPTARG" >&2
                exit 1
                ;;
        esac
    done
    shift $((OPTIND - 1)) # Décale les arguments pour ignorer les options déjà traitées

# Fonction de vérification
verif() {


    # Vérification du nombre minimum d'arguments restants
    if [ $# -lt 3 ]; then
        echo "Erreur : Vous devez passer au minimum 3 arguments après les options."
        return -1
    fi
    # Vérification que le fichier existe et son extension
    if [[ -f "$arg1" && "$arg1" == *.dat ]]; then
        :
    else
        echo "Erreur : '$arg1' n'est pas un fichier .dat valide."
        return -1
    fi

    # Vérification du second argument concernant les stations à traiter
    if [[ "$arg2" != "hvb" && "$arg2" != "hva" && "$arg2" != "lv" ]]; then
        echo "Erreur : Les stations à traiter sont : hvb ; hva ; lv"
        return -1
    fi

    # Vérification du troisième argument concernant les usagers à traiter
    if [[ "$arg3" != "comp" && "$arg3" != "indiv" && "$arg3" != "all" ]]; then
        echo "Erreur : Les consommateurs à traiter sont : comp ; indiv ; all"
        return -1
    fi

    # Vérification du quatrième argument
    ligne_fin=$(tac "$arg1" | grep -v '^[[:space:]]*$' | head -n 1 | awk -F';' '{print $1}')
    if [[ -n "$arg4" && ! "$arg4" =~ ^[0-9]+$ || -n "$arg4" && "$ligne_fin" -lt "$arg4" ]]; then
        echo "Erreur : Mauvais identifiant de central"
        return -1
    fi

}

# Création des dossiers utile au programme
crea_doss(){
	doss="test"
	if [ ! -d "$doss" ] ; then
		mkdir "$doss"
	fi
	doss="tmp"
	if [ ! -d "$doss" ] ; then
		mkdir -p "$doss"
		sudo mount -t tmpfs -o size=350M tmpfs tmp
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
	else
		mv $doss/* test
	fi
}

# Récupération des donnés sur la centrale et ses usagers.
recup_donne() {
	# Construction des expressions régulières en fonction de arg2, arg3 et arg4
    case "$arg2" in
        "hvb")
            if [ "$arg3" == "comp" ]; then
                station_regex="^(\d+);(\d+);-;-;-;-;(\d+);-$"
                usagers_regex="^(\d+);(\d+);-;-;(\d+);-;-;(\d+)"
            else
                echo "Erreur : mode $arg2/$arg3 non pris en charge."
                exit 1
            fi
            ;;
        "hva")
            if [ "$arg3" == "comp" ]; then
                station_regex="^(\d+);(\d+);(\d+);-;-;-;(\d+);-$"
                usagers_regex="^(\d+);-;(\d+);-;(\d+);-;-;(\d+)"
            else
                echo "Erreur : mode $arg2/$arg3 non pris en charge."
                exit 1
            fi
            ;;
        "lv")
            case "$arg3" in
                "comp")
                    station_regex="^(\d+);-;(\d+);(\d+);-;-;(\d+);-$"
                    usagers_regex="^(\d+);-;-;(\d+);(\d+);-;-;(\d+)"
                    ;;
                "indiv")
                    station_regex="^(\d+);-;(\d+);(\d+);-;-;(\d+);-$"
                    usagers_regex="^(\d+);-;-;(\d+);-;(\d+);-;(\d+)"
                    ;;
                "all")
                    station_regex="^(\d+);-;(\d+);(\d+);-;-;(\d+);-$"
                    usagers_regex="^(\d+);-;-;(\d+);(\d+);-;-;(\d+)|^(\d+);-;-;(\d+);-;(\d+);-;(\d+)"
                    ;;
                *)
                    echo "Erreur : mode $arg2/$arg3 non pris en charge."
                    exit 1
                    ;;
            esac
            ;;
        *)
            echo "Erreur : mode $arg2/$arg3 non pris en charge."
            exit 1
            ;;
    esac

    # Si un argument 4 est passé, on l'intègre dans les regex pour une recherche plus précise
    if [ -n "$arg4" ]; then
    	if [ "$arg2" == "lv" ] && [ "$arg3" == "all" ]; then
    		station_regex="^$arg4;${station_regex#*;}"
    		usagers_regex="^$arg4;-;-;(\d+);(\d+);-;-;(\d+)|^$arg4;-;-;(\d+);-;(\d+);-;(\d+)"
    	else
    		station_regex="^$arg4;${station_regex#*;}"
    		usagers_regex="^$arg4;${usagers_regex#*;}"
    	fi
    fi
    grep -P "$station_regex" "$arg1" > tmp/temp_station.txt
    grep -P "$usagers_regex" "$arg1" > tmp/temp_usager.txt

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

# Fonction pour vérifier et exécuter l'exécutable Main
lancement_C() {
    EXECUTABLE="codeC/Main"
    # Vérifier si l'exécutable existe et est accessible
    echo "ID:CAPACITE:CONSOMMATION:(OPTION EFFICIENCE)" > rendu/${arg2}_${arg3}.csv
    if [ -x "$EXECUTABLE" ]; then
    	case "$tri" in 
    	"id")
    	    ./$EXECUTABLE | sort -t: -k1,1n >> "rendu/${arg2}_${arg3}.csv"
    	    ;;
    	"conso")
    	    ./$EXECUTABLE | sort -t: -k3,3n >> "rendu/${arg2}_${arg3}.csv"
    	    ;;
    	*)
    	    ./$EXECUTABLE | sort -t: -k2,2n >> "rendu/${arg2}_${arg3}.csv"
    	    ;;
    	esac
    else
        cd codeC
        make > /dev/null 2>&1
        cd ..
        case "$tri" in 
    	"id")
    	    ./$EXECUTABLE | sort -t: -k1,1n >> "rendu/${arg2}_${arg3}.csv"
    	    ;;
    	"conso")
    	    ./$EXECUTABLE | sort -t: -k3,3n >> "rendu/${arg2}_${arg3}.csv"
    	    ;;
    	*)
    	    ./$EXECUTABLE | sort -t: -k2,2n >> "rendu/${arg2}_${arg3}.csv"
    	    ;;
    	esac

    fi
}

ajouter_colonne_ratio() {
    fichier="$1"
    if [ ! -f "$fichier" ]; then
        echo "Erreur : Le fichier '$fichier' n'existe pas."
        return 1
    fi

    # Traitement avec awk pour ajouter la 4ème colonne (ratio), en utilisant ':' comme séparateur
    awk -F: '{ 
        if ($2 != 0) {
            ratio = $3 / $2
        } else {
            ratio = "N/A"
        }
        print $1 ":" $2 ":" $3 ":" ratio
    }' "$fichier" > "$fichier.temp" && mv "$fichier.temp" "$fichier"
    
    # Trier par la 4ème colonne après avoir ajouté la colonne "ratio"
    sort -t: -k4,4n "$fichier" > "$fichier.temp" && mv "$fichier.temp" "$fichier"
}


lv_all_max_min(){
	fichier=$1
	if [[  "$arg2" == "lv" && "$arg3" == "all" ]]; then
		if [ ! -f "$fichier" ]; then
			echo "Erreur : Le fichier '$fichier' n'existe pas."
			return 1
		fi
	echo "$(sort -t: -k3,3n "$fichier" | head -n 10)" > rendu/lv_all_min_max 
	echo "" >> rendu/lv_all_min_max 
	echo "$(sort -t: -k3,3n "$fichier" | tail -n 10)" >> rendu/lv_all_min_max 
	fi	
			


}

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
	nombre_total_etapes=$1
	etape_actuelle=0
	if [[ $activer_efficience == true ]]; then
		((nombre_total_etapes+=1))
	fi
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
	timer "Durée de l'exécution du programme C" "lancement_C"
	 
	
	if [[ $activer_efficience == true ]]; then
	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "Ajout du rapport d'efficience" "ajouter_colonne_ratio rendu/${arg2}_${arg3}.csv"
	fi
	
	
	etape_actuelle=$((etape_actuelle + 1))
	barre_de_progression $etape_actuelle $nombre_total_etapes
	timer "LV all min max " "lv_all_max_min rendu/${arg2}_${arg3}.csv"
	
	echo "Fin de procédure le fichier final se trouve dans le dossier rendu"
	local end_main=$(date +%s)
	duree=$(echo "$end_main - $start_main " | bc)
		echo "Durée du Script Shell : $duree secondes"
}

arg1="$1"
arg2="$2"
arg3="$3"
arg4="$4"

main 5
#rm "tmp/temp_station.txt"
#rm "tmp/temp_usager.txt"
#sudo umount tmp
#rmdir "tmp"
