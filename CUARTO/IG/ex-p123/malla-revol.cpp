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
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 

   for (int i=0; i<num_copias; i++){
      for (int j=0; j<perfil.size();j++){
         glm::vec3 insertar = {cos(2*M_PI*i/(num_copias-1))*perfil[j].x + sin(2*M_PI*i/(num_copias-1))*perfil[j].z, perfil[j].y, -sin(2*M_PI*i/(num_copias-1))*perfil[j].x + cos(2*M_PI*i/(num_copias-1))*perfil[j].z};
         vertices.push_back(insertar);
      }
   }

   for (int i=0; i<num_copias-1; i++){
      for (int j=0; j<perfil.size()-1; j++){
         int k=i*perfil.size()+j;
         triangulos.push_back({k, k+perfil.size(), k+perfil.size()+1});
         triangulos.push_back({k, k+perfil.size()+1, k+1});
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

