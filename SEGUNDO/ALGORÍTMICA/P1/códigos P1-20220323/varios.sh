#!/bin/bash

echo "" >> salidas_p.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./seleccion_peor $i "\n" >> salidas_p.dat
done 
echo "FIN"

echo "" >> salidas_m.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./seleccion_mejor $i "\n" >> salidas_m.dat
done 
echo "FIN"

echo "" >> salidai_m.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./insercion_mejor $i "\n" >> salidai_m.dat
done 
echo "FIN"
