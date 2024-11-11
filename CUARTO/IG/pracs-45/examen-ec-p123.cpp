// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

#include "examen-ec-p123.h"

P1MallaCubo::P1MallaCubo():MallaInd("P1MallaCubo")
{
    vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         { 0.0, +1.0, 0.0 }, // 8 NUEVO VÉRTICE SUPERIOR
         { 0.0, -1.0, 0.0 } // 9 NUEVO VÉRTICE INFERIOR
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         //{0,5,1}, {0,4,5}, // Y- CAMBIAR!
         //{2,3,7}, {2,7,6}, // Y+ (+2) CAMBIAR!
         {0,1,9}, {0,9,4}, {4,9,5}, {5,9,1}, //NUEVOS TRIÁNGULOS UNIDOS AL VÉRTICE INFERIOR
         {2,8,3}, {2,8,6}, {6,8,7}, {7,8,3}, //NUEVOS TRIÁNGULOS UNIDOS AL VÉRTICE SUPERIOR

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)

      } ;

   col_ver =
   {
      {0,0,0}, {0,0,1}, {0,1,0},
      {0,1,1}, {1,0,0}, {1,0,1},
      {1,1,0}, {1,1,1}, {1,0,0}, {0,1,1}
   };
}

P2Rejilla::P2Rejilla(unsigned n, unsigned m):MallaInd("P2Rejilla")
{
    assert(n>2);
    assert(m>2);

    for (int i=0; i<m; i++){
      for (int j=0; j<n; j++){
         vertices.push_back({(3/(n-j))*i/(m-1), 0, 1.4*j/(n-1)});
      }
   }

   for (int i=0; i<m-1; i++){
      for (int j=0; j<n-1; j++){
         triangulos.push_back({n*i+j, n*i+j+1, n*(i+1)+j+1});
         triangulos.push_back({n*i+j, n*(i+1)+j, n*(i+1)+j+1});
      }
   }

   for (int i=0; i<vertices.size(); i++){
      col_ver.push_back(vertices[i]);
   }
}

P3Cuadrado::P3Cuadrado():MallaInd("P3Cuadrado")
{
    vertices={
        {-1.0, 0.0, -1.0}, {-1.0, 0.0, +1.0}, {+1.0, 0.0, -1.0}, {+1.0, 0.0, +1.0}
    };

    triangulos={
        {0,1,3}, {0,3,2}
    };
}

P3Caja::P3Caja()
{
    
    unsigned ind=agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    agregar(new Esfera(16,32));
    tras_esfera=leerPtrMatriz(ind);

    agregar(translate(glm::vec3(0.0,1.0,0.0)));
    agregar(new P3Tapa(rot_hoja1, rot_hoja2));
    agregar(translate(glm::vec3(0.0,-2.0,0.0)));
    agregar(new P3Cuadrado());
    agregar(translate(glm::vec3(0.0,+1.0,0.0)));
    for (int i=0; i<4; i++){
        agregar(rotate(float(M_PI/2), glm::vec3(0.0,1.0,0.0)));
        agregar(new P3Cubo());
    }
}

P3Tapa::P3Tapa(glm::mat4 *mov1, glm::mat4 *mov2){
    
    agregar(translate(glm::vec3(-0.5,0.0,0.0)));
    agregar(new P3Abatible(mov1));
    agregar(translate(glm::vec3(1.0,0.0,0.0)));
    agregar(new P3Abatible(mov1));
}

P3Abatible::P3Abatible(glm::mat4 *rot_hoja)
{
    unsigned ind=agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    agregar(scale(glm::vec3(0.5,1.0,1.0)));
    agregar(new P3Cuadrado());
    rot_hoja=leerPtrMatriz(ind);
}

P3Cubo::P3Cubo()
{
    
    agregar(translate(glm::vec3(0.0,0.0,1.0)));
    agregar(rotate(float(M_PI/2), glm::vec3(1.0,0.0,0.0)));
    agregar(new P3Cuadrado());
}

void P3Caja::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    //NO ME DA TIEMPO A ACABARLO
    assert (iParam < leerNumParametros());
    float v;
    switch(iParam)
    {
        case 0:
            v=0.5+0.5*sin(2.0*M_PI*1.0*t_sec);
            *rot_hoja1=rotate(float(v), glm::vec3(0.0,0.0,1.0));
        break;
        case 1:
            v=0.5+0.5*sin(2.0*M_PI*1.0*t_sec);
            *tras_esfera=translate(glm::vec3(0.0, v, 0.0));
        break;
        case 2:

        break;
    }
}

unsigned P3Caja::leerNumParametros() const
{
    return 3;
}