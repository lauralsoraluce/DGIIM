#!/bin/bash

echo "" >> salida.dat
for (( i=8; i<=33; i++ ))
do
	./hanoi $i "\n" >> salida.dat
done 
echo "FIN"
