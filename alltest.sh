#!/bin/bash

make clean
make

rm -f report.txt
touch report.txt

valid=0
cmpt=0
result=-1
state=""
arr=()

for dir in test/*
do
    for file in $dir/*
    do
        ./bin/tpcc $file
        result=$?
        echo "$file : $result" >> report.txt
        if [ $result -eq 0 ]
        then
            state="SUCCESS"
            ((valid=valid+1))
        else
            state="FAILURE"
        fi
        arr+=($state": test sur le fichier" $file)
        ((cmpt=cmpt+1))
    done
done

./bin/tpcas -w
echo "tpcas : $?" >> report.txt

echo ======================
echo ===== Resultats ======
echo ======================
echo
echo fichiers valides: $valid
echo fichier non valides: $(($cmpt-$valid))
echo Nombre de fichiers lus: $cmpt
echo 
for i in ${!arr[@]}; 
do
  echo ${arr[$i]}
done
echo
