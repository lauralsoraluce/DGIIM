#!/bin/bash

Script q muestre para el PID de un proceso que se pasa como argumento el uid,el nivel de prioridad y el tiempo total de CPU desde q comenzo

if [ #$ != 1 ] ;
	then echo "ERROR. Introduzca un PID"
else
	ps -p $1 -o uid
	ps -p $1 -o pri
	ps -p $1 -o time

