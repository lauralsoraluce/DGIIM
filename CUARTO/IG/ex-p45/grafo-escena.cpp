// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
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
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 
//#include "malla-revol.h"

using namespace glm;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( apl != nullptr );

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = apl->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = apl->pila_materiales ; assert( pila_materiales != nullptr );

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')

   if (tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   if (apl->iluminacion) {
      apl->pila_materiales->push();
   }

   cauce->pushMM();

   for (int i = 0; i < entradas.size(); i++) {
      if (entradas[i].tipo == TipoEntNGE::objeto)
         entradas[i].objeto->visualizarGL();
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
         cauce->compMM(*entradas[i].matriz);
      else if (entradas[i].tipo == TipoEntNGE::material)
         apl->pila_materiales->activar(entradas[i].material);
   }

   cauce->popMM();

   if (tieneColor()){
      cauce->popColor();
   }

   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   // ......

   if (apl->iluminacion){
      pila_materiales->pop();
   }

}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')

   // .......

   cauce->pushMM();

   for (int i=0; i<entradas.size(); i++){
      if (entradas[i].tipo==TipoEntNGE::objeto){
         entradas[i].objeto->visualizarGeomGL();
      }
      else if (entradas[i].tipo==TipoEntNGE::transformacion){
         cauce->compMM(*(entradas[i].matriz));
      }
   }

   cauce->popMM();

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......
   cauce->pushMM();

   for (int i=0; i<entradas.size();i++){
      if (entradas[i].tipo==TipoEntNGE::objeto)
         entradas[i].objeto->visualizarNormalesGL();
      else if (entradas[i].tipo==TipoEntNGE::transformacion)
         cauce->compMM(*entradas[i].matriz);
   }

   cauce->popMM();

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........

   int ident = leerIdentificador();
   if (ident != -1) {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(ident));
   }

   cauce->pushMM();

   for (int i = 0; i < entradas.size(); i++) {
      if (entradas[i].tipo == TipoEntNGE::objeto)
         entradas[i].objeto->visualizarModoSeleccionGL();
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
         cauce->compMM(*entradas[i].matriz);
   }

   cauce->popMM();

   if (ident != -1)
      cauce->popColor();


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........

   entradas.push_back(entrada);

   return (entradas.size()-1) ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //

   if (indice>=entradas.size() || indice <0){
      std::cout << "Error: el indice está fuera de rango " << std::endl;
      exit(0);
   }
   else if (entradas[indice].tipo!=TipoEntNGE::transformacion){
      std::cout << "Error: la entrada no es de tipo transformacion " << std::endl;
      exit(0);
   }
   else if (entradas[indice].matriz == nullptr){
      std::cout << "Error: el puntero a la matriz es nulo "<< std::endl;
      exit(0);
   }

   return entradas[indice].matriz;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

   if (centro_calculado)
      return;
   
   int contadorCentros = 0;
   mat4 matrizModelado(1.0f);
   vec3 centroAcumulado = vec3(0.0, 0.0, 0.0);

   for (unsigned int i = 0; i < entradas.size(); i++){
      if (entradas[i].tipo == TipoEntNGE::transformacion){
         matrizModelado = matrizModelado * (*entradas[i].matriz);
      }
      else if (entradas[i].tipo == TipoEntNGE::objeto){
         entradas[i].objeto->calcularCentroOC();
         centroAcumulado = centroAcumulado + vec3(matrizModelado * vec4(entradas[i].objeto->leerCentroOC(),1.0f));
         contadorCentros++;
      }
   }

   for (int i = 0; i < 3; i++) {
      centroAcumulado[i] /= contadorCentros;
   }
   ponerCentroOC( centroAcumulado);
   centro_calculado = true;

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........

   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........

   if (ident_busc == leerIdentificador()) {
      *objeto = this;
      centro_wc = leerCentroOC();
      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........

   mat4 matrizmod = mmodelado;

   for(int i=0; i<entradas.size(); i++){
        if(entradas[i].tipo == TipoEntNGE::objeto){
            if(entradas[i].objeto->buscarObjeto(ident_busc, matrizmod, objeto, centro_wc)) return true;
        }
        else if(entradas[i].tipo == TipoEntNGE::transformacion) matrizmod = matrizmod*(*entradas[i].matriz);
   }


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

GrafoEstrellaX::GrafoEstrellaX(unsigned n)
{
   assert(n>1);
   ponerNombre("Grafo Estrella X");

   unsigned ind=agregar(rotate(float(M_PI), glm::vec3(1.0,0.0,0.0)));
   NodoGrafoEscena *puntas = new NodoGrafoEscena();
   puntas->agregar(translate(glm::vec3(0.5, 0.0, 0.0)));
   puntas->agregar(rotate(float(3*M_PI/2), glm::vec3(0.0,0.0,1.0)));
   puntas->agregar(scale(glm::vec3(7.0/130, 3.0/52 ,7.0/130)));
   puntas->agregar(new Cono(16,32));
   
   agregar(scale(glm::vec3(2.6,2.6,2.6)));
   agregar(translate(glm::vec3(-0.5,-0.5,0.0)));

   agregar(new EstrellaZ(n));

   agregar(translate(glm::vec3(0.5,0.5,0)));

   for(int i=0;i<n;i++){
      agregar(rotate(float(2*M_PI/n),glm::vec3(0,0,1)));
      agregar(puntas);
   }

   rot_estrella = leerPtrMatriz(ind);

}

unsigned GrafoEstrellaX::leerNumParametros() const
{
   return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
   assert(iParam < leerNumParametros());
   float v;
   switch(iParam)
   {
      case 0:
         {
            v = 0 + 2*M_PI*2.5*t_sec;
            *rot_estrella = rotate( v, glm::vec3( 1.0, 0.0, 0.0));
         }
         break;
   }
}

GrafoCubos::GrafoCubos()
{
   ponerNombre("GrafoCubos");
   agregar(new CaraCubos(rot_cubos[0]));
   agregar(scale(glm::vec3(-1,-1,-1)));
   agregar(new CaraCubos(rot_cubos[1]));
   agregar(rotate(float(M_PI/2),glm::vec3(0,0,1)));
   agregar(new CaraCubos(rot_cubos[2]));
   for (int i=0; i<3; i++){
      agregar(rotate(float(M_PI/2),glm::vec3(1,0,0)));
      agregar(new CaraCubos(rot_cubos[i+3]));
   }
}

unsigned GrafoCubos::leerNumParametros() const
{
   return 1;
}

void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
   assert(iParam < leerNumParametros());
   float v;
   switch(iParam)
   {
      case 0:
         {
            v = 0 + 2*M_PI*2.5*t_sec;
            for (int i=0; i<6; i++){
               *rot_cubos[i]=rotate( v, glm::vec3( 0.0, 1.0, 0.0));
            }
         }
         break;
   }
}

CaraCubos::CaraCubos(glm::mat4 *&movimiento)
{
   agregar(translate(glm::vec3(-0.5,0.5,-0.5)));
   agregar(new RejillaY(6,6));
   
   agregar(translate(glm::vec3(0.5,0.25,0.5)));
   agregar(scale(glm::vec3(0.125,0.25,0.125)));
   unsigned ind = agregar(rotate(0.0f,glm::vec3(0,1,0)));
   agregar(new Cubo());
   movimiento = leerPtrMatriz(ind);
}

// ****************************************************************************************************


NodoCubo24::NodoCubo24(){
   agregar( new Material( new Textura("window-icon.jpg") , 0.5, 0.3, 0.7, 100.0) );
   agregar( new Cubo24() );
}

// ****************************************************************************************************

NodoDiscoP4::NodoDiscoP4(){
   Textura *textura = new Textura("cuadricula.jpg");
   Material *material = new Material(textura, 0.5, 0.8, 0.2, 100.0);
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   agregar(material);
   agregar( new MallaDiscoP4() );
}

// ****************************************************************************************************

MiEsferaE1::MiEsferaE1(unsigned i, unsigned j){
   fila = i;
   columna = j;
   agregar(new Esfera(20,20));
}

bool MiEsferaE1::cuandoClick(const glm::vec3 & centro_wc) {
   std::cout << "Se ha seleccionado la esfera numero " << columna+1 << " de la fila numero " << fila+1 << std::endl;
}

// ****************************************************************************************************

GrafoEsferasP5::GrafoEsferasP5(){
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5;
   const float
      e = 0.4/n_esferas_x_fila;
   
   agregar(glm::scale(glm::vec3(e,e,e)));

   for(unsigned i=0; i<n_filas_esferas; i++){
      NodoGrafoEscena *fila_esferas = new NodoGrafoEscena();
      for(unsigned j=0; j<n_esferas_x_fila; j++){
         MiEsferaE1 *esfera = new MiEsferaE1(i,j);
         esfera->ponerIdentificador(i*n_esferas_x_fila+j+1);
         fila_esferas->agregar(glm::translate(glm::vec3(2.2,0.0,0.0)));
         fila_esferas->agregar(esfera);
      }
      agregar(fila_esferas);
      agregar(glm::translate(glm::vec3(0.0,0.0,5.0)));
   }
   
}

// ****************************************************************************************************

MiEsferaE2::MiEsferaE2(){
   ponerColor(glm::vec3(1.0,1.0,1.0));
   agregar(new Esfera(20,20));
}

bool MiEsferaE2::cuandoClick(const glm::vec3 & centro_wc) {
   if(leerColor() == glm::vec3(1.0,1.0,1.0)){
      ponerColor(glm::vec3(1.0,0.0,0.0));
   }else{
      ponerColor(glm::vec3(1.0,1.0,1.0));
   }
}

// ****************************************************************************************************

GrafoEsferasP5_2::GrafoEsferasP5_2(){
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5;
   const float
      e = 0.5/n_esferas_x_fila;

   agregar(glm::scale(glm::vec3(e,e,e)));

   for(int i=0; i<n_filas_esferas; i++){
      NodoGrafoEscena *fila_esferas = new NodoGrafoEscena();
      fila_esferas->agregar(glm::translate(glm::vec3(3.0,0.0,0.0)));
      for(int j=0; j<n_esferas_x_fila; j++){
         MiEsferaE2 *esfera = new MiEsferaE2();
         esfera -> ponerIdentificador(i*n_esferas_x_fila+j+1);
         fila_esferas->agregar(glm::translate(glm::vec3(2.5,0.0,0.0)));
         fila_esferas->agregar(esfera);
      }
      agregar(fila_esferas);
      float angulo = (2*M_PI)/n_filas_esferas;
      agregar(glm::rotate(angulo,glm::vec3(0.0,1.0,0.0)));
   }
}