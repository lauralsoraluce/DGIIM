#!/bin/bash

echo "" >> sDyV1.dat
for (( i=1; i<=500000; i=i+22727 ))
do
	./DyV1 $i >> sDyV1.dat
done 
echo "FIN"
