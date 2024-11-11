#!/bin/bash

echo "" >> salidah.dat
for (( i=20000; i<=1000000; i=i+37500 ))
do
	./heapsort $i "\n" >> salidah.dat
done 
echo "FIN"
