#!/bin/bash

echo "" >> salidaf.dat
for (( i=100; i<=1500; i=i+50 ))
do
	./floyd $i >> salidaf.dat
done 
echo "FIN"
