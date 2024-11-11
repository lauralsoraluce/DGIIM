#!/bin/bash

echo "" >> salidai_p.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./insercion_peor $i "\n" >> salidai_p.dat
done 
echo "FIN"
