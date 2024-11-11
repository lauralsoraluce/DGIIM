set of int: Tareas = 1..10;
set of int: Dias = 1..48;
set of int: Trabajadores = 1..3;
set of int: Trabajadores_ext = 1..4;

array[Tareas, Trabajadores] of int: duracion_tarea = [| 3, 6, 9 | 7, 5, 3 | 3, 2, 4 | 5, 5, 8 | 4, 3, 6 | 3, 2, 1 | 2, 2, 3 | 2, 4, 2 | 2, 3, 4 | 3, 2, 1 |];
array [Trabajadores, Dias] of var Tareas: asignacion; % La restricción de que un trabajador no trabaja en más de una tarea a la vez ya está implícita


% Restricción: en cada tarea trabaja sólo un trabajador
constraint forall(j in Dias, k in Tareas)(
    sum(i in Trabajadores)(asignacion[i,j]=k)<=1
);

constraint forall(i in Trabajadores, k in Tareas)(
    sum(j in Dias)(asignacion[i,j]=k) in {0, duracion_tarea[k,i]}
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    asignacion[]
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[2, i]>=dia_inicio[1,j]+duracion_tarea[1,j]) \/ dia_inicio[2,i]=0 \/ dia_inicio[1,j]=0
);


var int: total;

% Buscamos que la última tarea que se acaba, se acabe lo antes posible
constraint total = max([j+duracion_tarea[asignacion[i,j],i] | i in Trabajadores, j in Dias where asignacion[i,j]>0]);

solve minimize total;