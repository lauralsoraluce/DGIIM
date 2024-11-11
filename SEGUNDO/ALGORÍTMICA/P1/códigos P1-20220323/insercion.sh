#!/bin/bash

echo "" >> salidai.dat
for (( i=20000; i<=200000; i=i+6900 ))
do
	./insercion $i "\n" >> salidai.dat
done 
echo "FIN"
