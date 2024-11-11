#!/bin/bash

echo "" >> sDyV11.dat
for (( i=20000; i<=5000000; i=i+226364 ))
do
	./DyV11 $i >> sDyV11.dat
done 
echo "FIN"
