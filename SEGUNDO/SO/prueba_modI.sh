#!/bin/bash
#Autor: Laura Lázaro
#Descripción: Examen Módulo I

if [ $# != 1 ] ;
	then echo "ERROR: introduzca un sólo PID"

else 
	echo "Tamaño de memoria virtual: "
	ps -p $1 -o vsz
	echo "Memoria real usada: "
	ps -p $1 -o rss
	echo "SHR: Memoria compartida: "
	top -p $1

fi;
	
