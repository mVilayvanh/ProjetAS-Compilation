#!/bin/bash

# Chemin du répertoire contenant les fichiers à tester
test_dir="test/sem-err"

# Initialisation des compteurs
total_tests=0
error_count=0

# Boucle sur les fichiers du répertoire
for file in "$test_dir"/*
do
  if [ -f "$file" ]
  then
    # Exécute la commande bin/tpcc avec le fichier en entrée, et redirige la sortie standard et la sortie d'erreur standard vers des fichiers séparés
    bin/tpcc -t "$file" > stdout.txt 2> stderr.txt

    # Incrémente le compteur de tests effectués
    ((total_tests++))

    # Vérifie si le fichier stderr.txt contient du texte, ce qui indique une erreur
    if [ -s stderr.txt ]
    then
      # Incrémente le compteur d'erreurs
      ((error_count++))
    fi

    # Affiche le contenu du fichier stderr.txt
    cat stderr.txt
  fi
done

# Ajoute le nombre de tests et le nombre d'erreurs à la fin du fichier
echo "Nombre total de tests : $total_tests" >> stderr.txt
echo "Nombre d'erreurs : $error_count" >> stderr.txt
