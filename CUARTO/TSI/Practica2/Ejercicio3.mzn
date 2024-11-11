% Restricción a
set of int: DIAS = 1..5; % Lunes = 1, Martes = 2, Miércoles = 3, Jueves = 4, Viernes = 5
set of int: HORAS = 8..14;


% Restricción b y e
set of int: ASIGNATURAS = 1..11; % 1: A1 impartida por Prof1, 2: A2 impartida por Prof4, 3: A3 impartida por Prof1, 4: A4 impartida por Prof2, 5: A5 impartida por Prof2, 6: A6 impartida por Prof3, 7: A7 impartida por Prof4, 8: A8 impartida por Prof4, 9: A9 impartida por Prof3, 10: A10 impartida por Prof5, 11: Tutoría.
array[ASIGNATURAS] of int: horas_semanales = [4, 2, 4, 4, 4, 2, 2, 2, 1, 5, 5]; % Total de horas que se imparte la asignatura a la semana
array[DIAS, HORAS] of var ASIGNATURAS: horario;

constraint forall(a in ASIGNATURAS) (
    sum(i in DIAS, j in HORAS)(horario[i, j] = a) = horas_semanales[a]
);


% Restricción c
array[ASIGNATURAS] of 1..2: bloque = [2, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1]; % Duración de los bloques de cada asignatura

% Para asegurar que son 2 horas consecutivas 
constraint forall(i in DIAS, a in {1, 3, 4, 5, 8}) (
    (sum(j in {8, 9, 10, 11, 12, 13})(horario[i, j] = a /\ horario[i, j+1] = a) = 1) \/ (sum(j in HORAS)(horario[i,j] = a) = 0)
);


% Restricción d
% En un día, una asignatura se imparte un sólo bloque completo, o bien no se imparte
constraint forall(i in DIAS, a in ASIGNATURAS) (
    sum(j in HORAS)(horario[i, j] = a) in {bloque[a], 0}
);


% Restricción f
% Dos asignaturas del Prof1 no se pueden impartir el mismo día
constraint forall(i in DIAS) (
    sum(a in {1, 3}, j in HORAS)(horario[i, j] = a) in {bloque[1], bloque[3], 0}
);

% Dos asignaturas del Prof2 no se pueden impartir el mismo día
constraint forall(i in DIAS) (
    sum(a in {4, 5}, j in HORAS)(horario[i, j] = a) in {bloque[4], bloque[5], 0}
);

% Dos asignaturas del Prof3 no se pueden impartir el mismo día
constraint forall(i in DIAS) (
    sum(a in {6, 9}, j in HORAS)(horario[i, j] = a) in {bloque[6], bloque[9], 0}
);


% Restricción h
% El número de horas que imparte el Prof1 fuera de la 5ª y 6ª hora es cero
constraint forall(i in DIAS) (
    sum(a in {1, 3}, j in {8, 9, 10, 11, 14})(horario[i, j] = a) = 0
);

% El número de horas que imparte el Prof2 fuera de la 1ª y 2ª hora es cero
constraint forall(i in DIAS) (
    sum(a in {4, 5}, j in {10, 11, 12, 13, 14})(horario[i, j] = a) = 0
);

% La asignatura 10 del Prof5 se imparte cada día a 4ª hora
constraint forall(i in DIAS) (
    horario[i, 11] = 10
);


% Restriccion g
constraint forall(i in DIAS) (
    horario[i, 10]=11
);


% Restricción i
% Sigo la misma técnica que en la restricción h
constraint forall(i in {3, 4, 5}) (
    sum(a in {1, 4}, j in HORAS)(horario[i, j] = a) = 0
);

constraint forall(i in {1, 2, 5}) (
    sum(j in HORAS)(horario[i, j] = 3) = 0
);

constraint forall(i in {1, 2, 3}) (
    sum(j in HORAS)(horario[i, j] = 5) = 0
);

constraint forall(i in {1, 2, 4}) (
    sum(j in HORAS)(horario[i, j] = 6) = 0
);

constraint forall(i in {1, 3, 4}) (
    sum(j in HORAS)(horario[i, j] = 7) = 0
);

constraint forall(i in {1, 2, 4, 5}) (
    sum(j in HORAS)(horario[i, j] = 8) = 0
);

constraint forall(i in {2, 3, 4, 5}) (
    sum(j in HORAS)(horario[i, j] = 9) = 0
);

% En un día, o bien se imparte la asignatura 6 directamente seguida de la 7, o bien no se imparten las dos en ese día. 
constraint forall(i in DIAS) (
    (sum(j in {8, 9, 10, 11, 12, 13})(horario[i, j] = 6 /\ horario[i, j+1] = 7) = 1) \/ (sum(k in HORAS, j in HORAS)(horario[i,j] = 6 /\ horario[i,k] = 7) = 0)
);

solve satisfy;
