#!/bin/bash

# Chemin du dossier principal (où tu veux le fichier final)
dossier_destination="dossier_principal"
# Nom du fichier final
fichier_final="tout_reuni.c"

# Création du dossier principal s'il n'existe pas
mkdir -p "$dossier_destination"

# Fichier de sortie complet
chemin_fichier_final="$dossier_destination/$fichier_final"

# Vider le fichier s'il existe déjà
> "$chemin_fichier_final"

# Parcourir tous les fichiers .c dans les dossiers enfants
for fichier in */*.c; do
    echo "// ==== Contenu de : $fichier ====" >> "$chemin_fichier_final"
    cat "$fichier" >> "$chemin_fichier_final"
    echo -e "\n" >> "$chemin_fichier_final"
done

echo "Fusion terminée. Tous les fichiers .c sont réunis dans : $chemin_fichier_final"

