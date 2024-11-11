#!/bin/bash

echo "" >> sObvio1.dat
for (( i=20000; i<=500000; i=i+21800 ))
do
	./obvio1 $i >> sObvio1.dat
done 
echo "FIN"
