#!/bin/bash

# ./nazwapliku.sh program_jeden progream_dwa nazwa_generator_testow folder_do_plikow liczba_testow ile_w_tescie zakres_min zakres_max

# przykladowa komenda 
#  ./skrypt_do_testowania.sh rozwiazanie pol generator_testow folder_z_testemi 1000 10 -20 20

plik1=$1
plik2=$2
generator=$3
folder=$4
ile_test=$5
jakie_n=$6
min=$7
max=$8

mkdir $folder
mkdir $folder/wejsc
mkdir $folder/odpow

g++ -DSORTOWANIE -std=c++17 -o ${plik1} ${plik1}.cpp
g++ -DSORTOWANIE -std=c++17 -o ${plik2} ${plik2}.cpp
g++ -std=c++17 -o ${generator} ${generator}.cpp

echo $jakie_n $min $max > $folder/zmienne_gen.in

for i in $(seq 1 $ile_test)
do 
	./${generator} < $folder/zmienne_gen.in > $folder/wejsc/$i.in 
	./${plik1} < $folder/wejsc/$i.in > $folder/odpow/${i}_1.out
	./${plik2} < $folder/wejsc/$i.in > $folder/odpow/${i}_2.out
	if (diff $folder/odpow/${i}_1.out $folder/odpow/${i}_2.out) then
		echo ok $i
	else
		echo nie $i 
		exit 1
	fi

done

rm $folder/wejsc/*
rm $folder/odpow/*
rm $folder/zmienne_gen.in
rmdir $folder/*
rmdir $folder

echo wszyskto git
