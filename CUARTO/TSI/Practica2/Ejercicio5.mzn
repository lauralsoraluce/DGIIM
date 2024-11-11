set of int: Ntsiutils = 1..192;
% Pesos
array[Ntsiutils] of int : Pesostsiutils = [50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500,50,500,1000,3000,1500,3000,500,1000,2000,500,250,500];
% Prioridad
array[Ntsiutils] of int : Prioridadtsiutils = [100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40,100,90,75,95,85,10,5,70,90,20,50,40];

predicate pesosN(array[int] of var int: inlist) =
   forall(i in 1..length(inlist))(inlist[i] == Pesostsiutils[i]);
predicate prioridadN(array[int] of var int: inlist) =
   forall(i in 1..length(inlist))(inlist[i] == Prioridadtsiutils[i]);

% Set de valores
int: size;
% Pesos
array[1..size] of var int : Pesos;
constraint pesosN(Pesos);
% Prioridad
array[1..size] of var int : Prioridad;
constraint prioridadN(Prioridad);

% Va a valer 1 en la posición de los objetos que se meten en la mochila y 0 en la de los que no
array[1..size] of var 0..1 : Mochila;

% Número de objetos que hemos incluido en la mochila
var int : incluidos = sum(i in 1..size)(Mochila[i]=1);

% Suma del peso de los objetos que incluimos en la mochila, y que obligamos a que sea menor o igual que 5kg.
var int: peso_total = sum(i in 1..size)(Mochila[i]*Pesos[i]);
constraint peso_total <=5000;

% Suma de prioridades
var int : total = sum(i in 1..size)(Mochila[i]*Prioridad[i]);


solve maximize total;

% Salida formateada
output["Objetos ="];

output[" O\(i)" | i in 1..size where fix(Mochila[i])=1];
% Fix se usa para obtener el valor de la variable después de haber resuelto el problema

output ["  | Número de objetos = \(incluidos) | Prioridades = \(total) | PesoFinal = \(peso_total/1000) kgs\n"];