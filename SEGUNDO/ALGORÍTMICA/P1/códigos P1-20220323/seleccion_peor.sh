#!/bin/bash

echo "" >> salidas_p.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./seleccion_peor $i "\n" >> salidas_p.dat
done 
echo "FIN"
