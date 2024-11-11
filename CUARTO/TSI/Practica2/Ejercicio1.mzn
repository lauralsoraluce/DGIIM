set of int: POS = 0..12;
set of int: VALUES = 1..4;
enum Color = {Verde, Rojo, Naranja, Azul};
array [POS] of var Color: regiones;
array [Color] of var int: precios = [100, 250, 350, 450];

constraint regiones[0] != regiones[1] /\ regiones[0] != regiones [2] /\ regiones[0] != regiones[8] /\ regiones[0] != regiones[11];
constraint regiones[1] != regiones[2] /\ regiones[1] != regiones[3] /\ regiones[1] != regiones[8] /\ regiones[1] != regiones[9];
constraint regiones[2] != regiones[4] /\ regiones[2] != regiones[6] /\ regiones[2] != regiones[7] /\ regiones[2] != regiones[8] /\ regiones[2] != regiones[9] /\ regiones[2] != regiones[10] /\ regiones[2] != regiones[11] /\ regiones[2] != regiones[12];
constraint regiones[3] != regiones[9];
constraint regiones[4] != regiones[5] /\ regiones[4] != regiones[9] /\ regiones[4] != regiones[12];
constraint regiones[5] != regiones[9];
constraint regiones[6] != regiones[10];
constraint regiones[7] != regiones[10] /\ regiones[7] != regiones[12];
constraint regiones[8] != regiones[11];

var int: total = sum(i in POS)(precios[regiones[i]]);
%constraint sum(i in POS)(precios[regiones[i]]) = 2900; % Para CSP

solve minimize total;
%solve satisfy; % Para CSP

% Cuantos colores como mínimo hacen falta?
%var int: usados = card({regiones[i] | i in POS});
%solve minimize usados;

output ["total: \(total)\n"];
output ["\"Argentina\t \": \(regiones[0])\t\(precios[regiones[0]] )\n"] ++
["\"Bolivia\t \": \(regiones[1])\t\(precios[regiones[1]] )\n"] ++
["\"Brasil\t\t \": \(regiones[2])\t\(precios[regiones[2]] )\n"] ++
["\"Chile\t\t \": \(regiones[3])\t\(precios[regiones[3]] )\n"] ++
["\"Colombia\t \": \(regiones[4])\t\(precios[regiones[4]] )\n"] ++
["\"Ecuador\t \": \(regiones[5])\t\(precios[regiones[5]] )\n"] ++
["\"Guyana Francesa \": \(regiones[6])\t\(precios[regiones[6]] )\n"] ++
["\"Guyana\t\t \": \(regiones[7])\t\(precios[regiones[7]] )\n"] ++
["\"Paraguay\t \": \(regiones[8])\t\(precios[regiones[8]] )\n"] ++
["\"Peru\t\t \": \(regiones[9])\t\(precios[regiones[9]] )\n"] ++
["\"Surinam\t \": \(regiones[10])\t\(precios[regiones[10]] )\n"] ++
["\"Uruguay\t \": \(regiones[11])\t\(precios[regiones[11]] )\n"] ++
["\"Venezuela\t \": \(regiones[12])\t\(precios[regiones[12]] )\n"];
