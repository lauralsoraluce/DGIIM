% Definir los datos de entrada
set of int: Trabajadores = 1..3;
set of int: Tareas = 1..10;
array[Tareas, Trabajadores] of int: duracion_tarea = [| 3, 6, 9 | 7, 5, 3 | 3, 2, 4 | 5, 5, 8 | 4, 3, 6 | 3, 2, 1 | 2, 2, 3 | 2, 4, 2 | 2, 3, 4 | 3, 2, 1 |];

array[Tareas, Trabajadores] of var 0..48: dia_inicio;

% Restricción: sólo un trabajador trabaja en una tarea
constraint forall(i in Tareas)(
    sum(j in Trabajadores)(dia_inicio[i,j]>0)=1
);

% Restricción: un trabajador no trabaja a la vez en dos tareas distintas
constraint forall(i in Trabajadores, j in Tareas, k in Tareas)(
    dia_inicio[j,i]!=dia_inicio[k,i] \/ dia_inicio[j,i]=0 \/ j=k 
);

% Restricciones: precedencia de Tareas
constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[2, i]>=dia_inicio[1,j]+duracion_tarea[1,j]) \/ dia_inicio[2,i]=0 \/ dia_inicio[1,j]=0
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[3, i]>=dia_inicio[2,j]+duracion_tarea[2,j]) \/ dia_inicio[3,i]=0 \/ dia_inicio[2,j]=0
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[4, i]>=dia_inicio[1,j]+duracion_tarea[1,j] \/ dia_inicio[4,i]=0 \/ dia_inicio[1,j]=0) /\ (dia_inicio[4, i]>=dia_inicio[3,j]+duracion_tarea[3,j] \/ dia_inicio[4,i]=0 \/ dia_inicio[3,j]=0)
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[5, i]>=dia_inicio[3,j]+duracion_tarea[3,j]) \/ dia_inicio[5,i]=0 \/ dia_inicio[3,j]=0
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[6, i]>=dia_inicio[3,j]+duracion_tarea[3,j]) \/ dia_inicio[6,i]=0 \/ dia_inicio[3,j]=0
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[7, i]>=dia_inicio[3,j]+duracion_tarea[3,j] \/ dia_inicio[7,i]=0 \/ dia_inicio[3,j]=0) /\ (dia_inicio[7, i]>=dia_inicio[4,j]+duracion_tarea[4,j] \/ dia_inicio[7,i]=0 \/ dia_inicio[4,j]=0)
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[8, i]>=dia_inicio[7,j]+duracion_tarea[7,j]) \/ dia_inicio[8,i]=0 \/ dia_inicio[7,j]=0
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[9, i]>=dia_inicio[6,j]+duracion_tarea[6,j] \/ dia_inicio[9,i]=0 \/ dia_inicio[6,j]=0) /\ (dia_inicio[9, i]>=dia_inicio[8,j]+duracion_tarea[8,j] \/ dia_inicio[9,i]=0 \/ dia_inicio[8,j]=0)
);

constraint forall(i in Trabajadores, j in Trabajadores)(
    (dia_inicio[10, i]>=dia_inicio[7,j]+duracion_tarea[7,j] \/ dia_inicio[10,i]=0 \/ dia_inicio[7,j]=0) /\ (dia_inicio[10, i]>=dia_inicio[9,j]+duracion_tarea[9,j] \/ dia_inicio[10,i]=0 \/ dia_inicio[9,j]=0)
);

var int: total;

% Buscamos que la última tarea que se acaba, se acabe lo antes posible
constraint total = max([dia_inicio[i,j]+duracion_tarea[i,j]-1 | i in Tareas, j in Trabajadores]);

solve minimize total;
