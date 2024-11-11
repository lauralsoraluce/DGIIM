#!/bin/bash
#Titulo: 
#Fecha: 20/09/2021
#Autor: Laura Lázaro
#Versión: 1.0
#Descripción: Automatización de apertura de entorno
#Opciones: Ninguna
#Uso: Lo indicado en la descripción

cp Fedora14-x86-root_fs.gz kernel32-3.0.4.gz /tmp

cd /tmp

gunzip Fedora14-x86-root_fs.gz

gunzip kernel32-3.0.4.gz

chmod u+x Fedora14-x86-root_fs

chmod u+x kernel32-3.0.4

./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
