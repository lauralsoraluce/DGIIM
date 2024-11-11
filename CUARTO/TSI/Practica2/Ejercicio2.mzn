array [1..4] of var 1..4: letras;

% La posición del array representa cada letra del primer grupo.
% El contenido en dicha posición del array representa la letra del segundo grupo. 
% Así la relación entre ambas está implícita en la representación.

constraint letras[1] != 2 -> letras[3] != 3;
constraint (letras[2] == 3 \/ letras[2] == 4) -> letras[1] = 2;
constraint letras[3] != 1 -> letras[2] = 4;
constraint letras[4] == 3 -> letras[2] != 2;
constraint letras[4] != 2 -> letras[2] = 2;


% Esta constraint es para el caso en el que haya que suponer que cada letra del primer grupo esta relacionada con una Y SÓLO una letra del segundo grupo.

%constraint forall(i in 1..4, j in i+1..4)(
%    letras[i]!=letras[j]
%);

enum Simbolo = {w, x, y, z};

solve satisfy;

output ["a<=>\(Simbolo[letras[1]])\t\tb<=>\(Simbolo[letras[2]])\t\tc<=>\(Simbolo[letras[3]])\t\td<=>\(Simbolo[letras[4]])"];
