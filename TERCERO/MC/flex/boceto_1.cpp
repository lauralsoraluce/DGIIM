// SECCIÓN DE DECLARACIONES

%{
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

using namespace std;

ifstream fichero;
int nc, np, nl;
void escribir_datos(int dato1, int dato2, int dato3);

%}

letraM [ABCDEFGHJKLMNPQRSTVWXYZ]
letra [a-zA-Z|\ñ]
digito [0-9]
let		[A-Za-z]
car	        ({let}|{digito}|\.|_)

nombre {letra}{1,30}
dni {digito}{8}{letraM}
idioma [ABC][12]
notaMedia {digito}{digito}?"'"{digito}{digito}
usuario (({letra}+{digito}+)|({digito}+{letra}+))
password {digito}{7}
correo {car}+@{car}+\.{let}{2,3}

%%

// SECCIÓN DE REGLAS




%%
