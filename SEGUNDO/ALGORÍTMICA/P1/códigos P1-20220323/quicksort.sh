#!/bin/bash

echo "" >> salidaq.dat
for (( i=20000; i<=1000000; i=i+37500 ))
do
	./quicksort $i "\n" >> salidaq.dat
done 
echo "FIN"
