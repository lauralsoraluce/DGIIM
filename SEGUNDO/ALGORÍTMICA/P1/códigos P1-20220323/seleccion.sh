#!/bin/bash

echo "" >> salidas.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./seleccion $i "\n" >> salidas.dat
done 
echo "FIN"
