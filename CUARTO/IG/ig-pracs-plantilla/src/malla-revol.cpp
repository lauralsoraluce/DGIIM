// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   using namespace std;

   // COMPLETAR: práctica 4: creación de las normales y materiales/texturas
   vector<vec3> normales_m;

   //Aristas
   for (int i = 0; i < perfil.size()-1; i++) {
      float v_1 = (perfil[i+1] - perfil[i])[0];
      float v_2 = (perfil[i+1] - perfil[i])[1];
      vec3 m_i(vec3(v_2, -v_1, 0.0f));

      if (length(m_i) != 0.0)
         m_i = normalize(m_i);
      
      normales_m.push_back(m_i);
   }

   //Vértices
   vector<vec3> normales_n;

   normales_n.push_back(normales_m[0]);
   for (int i = 1; i < perfil.size()-1; i++) {
      normales_n.push_back(normalize(normales_m[i-1] + normales_m[i]));
   }

   normales_n.push_back(normales_m[perfil.size() - 2]);

   //Vectores d y t
   vector<float> d, t, sumas_parciales;
   float suma_total;

   for (int i = 0; i < perfil.size()-1; i++) {
      d.push_back(sqrt(length(perfil[i+1] - perfil[i])));
   }

   sumas_parciales.push_back(0.0f);
   for (int i = 1; i < perfil.size(); i++) {
      sumas_parciales.push_back(sumas_parciales[i-1] + d[i-1]);
   }

   suma_total = sumas_parciales[perfil.size()-1];
   t.push_back(0.0f);
   for (int i = 1; i < perfil.size(); i++)
      t.push_back(sumas_parciales[i] / suma_total);
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 

   //Rellenamos la tabla de vertices
   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < perfil.size(); j++) {
         float tita = (2*M_PI*i)/(num_copias - 1);

         std::vector<std::vector<float>> matriz_giro = 
         {  {cos(tita), 0.0, sin(tita)},
            {0 ,1, 0},
            {-sin(tita), 0, cos(tita)},
         };

         glm::vec3 nuevo_vertice = {
            matriz_giro[0][0]*perfil[j][0] + matriz_giro[0][1]*perfil[j][1] + matriz_giro[0][2]*perfil[j][2],
            matriz_giro[1][0]*perfil[j][0] + matriz_giro[1][1]*perfil[j][1] + matriz_giro[1][2]*perfil[j][2],
            matriz_giro[2][0]*perfil[j][0] + matriz_giro[2][1]*perfil[j][1] + matriz_giro[2][2]*perfil[j][2],
         };

         vertices.push_back(nuevo_vertice);

         // PRACTICA 4
         vec3 aux = vec3(normales_n[j][0] * cos(tita), normales_n[j][1], -normales_n[j][0] * sin(tita));
         if (length(aux) != 0.0)
            normalize(aux);
         nor_ver.push_back(aux);
         
         cc_tt_ver.push_back({float(i) / (num_copias-1), 1-t[j]});
      }
   }
   // Rellenamos la tabla de triangulos
   for (int i = 0; i < num_copias-1; i++) {
      for (int j = 0; j < perfil.size() - 1; j++) {
         int k = i * perfil.size() + j;

         triangulos.push_back({k, k + perfil.size(), k + perfil.size() + 1});
         triangulos.push_back({k, k + perfil.size() + 1, k + 1});
      }
   }

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

Cilindro::Cilindro
(
   const int num_verts_per,
   const unsigned nperfiles
)
{
   ponerNombre(std::string("Cilindro"));

   std::vector<glm::vec3> perfil;
   for(int i=0; i<num_verts_per; i++){
      float altura = i*(1.0/(num_verts_per-1));
      perfil.push_back({1.0, altura, 0.0});
   }

   inicializar(perfil, nperfiles);

   /*for (int i=0; i<vertices.size(); i++){
      col_ver.push_back(vertices[i]);
   }*/

   // CAMBIO COLOR PARA LA PRÁCTICA 3
   for (int i=0; i<vertices.size();i++){
      col_ver.push_back({0.3,0.23,0.16});
   }

}

Cono::Cono
(
   const int num_verts_per,
   const unsigned nperfiles
)
{
   ponerNombre(std::string("Cono"));

   std::vector<glm::vec3> perfil;
   for (int i=0; i<num_verts_per; i++){
      float altura = i*(1.0/(num_verts_per-1));
      perfil.push_back({1.0-altura, altura, 0.0});
   }

   inicializar(perfil, nperfiles);

   for (int i=0; i<vertices.size(); i++){
      col_ver.push_back(vertices[i]);
   }
}

Esfera::Esfera
(
   const int num_verts_per,
   const unsigned nperfiles
)
{
   ponerNombre(std::string("Esfera"));

   std::vector<glm::vec3> perfil;
   for (int i=0; i<num_verts_per; i++){
      perfil.push_back({cos(i*(M_PI*2.0/(num_verts_per-1))), sin(i*(M_PI*2.0/(num_verts_per-1))), 0.0});
   }

   inicializar(perfil, nperfiles);

   /*for (int i=0; i<vertices.size(); i++){
      col_ver.push_back(vertices[i]);
   }*/

   //CAMBIO EL COLOR PARA LA PRÁCTICA 3
   for (int i=0; i<vertices.size(); i++){
      col_ver.push_back({0.93, 0.72, 0.06});
   }

}

MediaEsfera::MediaEsfera
(
   const int num_verts_per,
   const unsigned nperfiles
)
{
   ponerNombre(std::string("Media Esfera"));

   std::vector<glm::vec3> perfil;
   for (int i = 0; i <= num_verts_per / 2; i++) {
      perfil.push_back({cos(i * (M_PI / num_verts_per)), sin(i * (M_PI / num_verts_per)), 0.0});
   }

   inicializar(perfil, nperfiles);
}

ConoAltura::ConoAltura
(
   const int num_verts_per,
   const unsigned nperfiles,
   const int altura_pico
)
{
   ponerNombre(std::string("Cono Altura"));

   std::vector<glm::vec3> perfil;
   for (int i=0; i<num_verts_per; i++){
      float altura = i*(float(altura_pico)/(num_verts_per-1));
      float anchura = i*(1.0/(num_verts_per-1));
      perfil.push_back({1.0-anchura, altura, 0.0});
   }

   inicializar(perfil, nperfiles);
}

