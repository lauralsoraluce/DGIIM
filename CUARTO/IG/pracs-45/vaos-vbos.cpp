// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

#include "vaos-vbos.h"
    
constexpr GLsizei stride = 0 ;
constexpr void *  offset = 0 ;
constexpr GLint   first  = 0 ;

// ------------------------------------------------------------------------------------------------------
// devuelve el tamaño en bytes de un valor a partir de entero asociado con el tipo del valor en OpenGL

constexpr inline GLsizeiptr size_in_bytes( const GLenum type )
{
   switch( type )
   {
      case GL_FLOAT          : return sizeof( float );          break ;
      case GL_DOUBLE         : return sizeof( double );         break ;
      case GL_UNSIGNED_BYTE  : return sizeof( unsigned char );  break ;
      case GL_UNSIGNED_SHORT : return sizeof( unsigned short ); break ;
      case GL_UNSIGNED_INT   : return sizeof( unsigned int );   break ;
      default                : assert( false ); return 0 ;      break ;
   }
}

// ----------------------------------------------------------------------------
// 
constexpr inline void comprobar_tipo_atrib( const GLenum type )
{
   assert( type == GL_FLOAT  || 
           type == GL_DOUBLE );
}

// ----------------------------------------------------------------------------
// 
constexpr inline void check_indices_type( const GLenum type )
{
   assert( type == GL_UNSIGNED_BYTE  || 
           type == GL_UNSIGNED_SHORT || 
           type == GL_UNSIGNED_INT   );
}

// ------------------------------------------------------------------------------------------------------
// comprueba que el modo es válido para las llamadas glDrawArrays y glDrawElements

constexpr void check_mode( const GLenum mode )
{
   assert( mode == GL_TRIANGLES  || mode == GL_LINES || mode == GL_POINTS || 
           mode == GL_LINE_STRIP || mode == GL_LINE_LOOP  );  
}

// ******************************************************************************************************
// Clase DescrVBOAtribs
// ------------------------------------------------------------------------------------------------------

DescrVBOAtribs::DescrVBOAtribs( const unsigned p_index, const GLenum p_type, const unsigned p_size, 
                                const unsigned long p_count, const void *p_data )
{
   // copiar valores de entrada y comprobar que son correctos
   index    = p_index ;
   type     = p_type ;
   size     = p_size ;
   count    = p_count ;
   data     = p_data ;
   tot_size = size*count*size_in_bytes( type );

   copiarDatos();
   comprobar() ; 
}  

// ------------------------------------------------------------------------------------------------------
 
DescrVBOAtribs::DescrVBOAtribs( const unsigned p_index, const std::vector<glm::vec3> & src_vec )
{
   index    = p_index ;
   type     = GL_FLOAT ;
   size     = 3 ;
   count    = src_vec.size();
   data     = src_vec.data();
   tot_size = size*count*size_in_bytes( type );
   
   copiarDatos() ;
   comprobar();
}

// ----------------------------------------------------------------------------

DescrVBOAtribs::DescrVBOAtribs( const unsigned p_index, const std::vector<glm::vec2> & src_vec )
{
   index    = p_index ;
   type     = GL_FLOAT ;
   size     = 2 ;
   count    = src_vec.size();
   data     = src_vec.data();
   tot_size = size*count*size_in_bytes( type );
   
   copiarDatos();
   comprobar();
}

// --------------------------------------------------------------------------------------

void DescrVBOAtribs::copiarDatos()
{
   assert( data != nullptr );     // 'data' debe apuntar a los datos originales
   assert( 0 < tot_size );        // 'tot_size' debe tener el tamaño total de los datos
   assert( own_data == nullptr ); // impide copiar los datos dos veces 

   own_data = new unsigned char [tot_size] ; // reservar memoria
   assert( own_data != nullptr );            // comprobar que se ha podido reservar la memoria
   std::memcpy( own_data, data, tot_size );  // copiar bytes
   data = own_data ;                         // apuntar a los datos propios
}

// --------------------------------------------------------------------------------------

void DescrVBOAtribs::comprobar() const 
{
   comprobar_tipo_atrib( type );

   assert( data != nullptr );
   assert( 0 < count );
   assert( own_data == nullptr || own_data == data );
   assert( 1 <= size && size <= 4 ); 
   assert( type == GL_FLOAT || type == GL_DOUBLE );
   assert( tot_size == size*count*size_in_bytes( type ));
}

// ------------------------------------------------------------------------------------------------------

void DescrVBOAtribs::crearVBO() 
{
   // comprobar precondiciones
   CError();
   assert( buffer == 0 );  
   comprobar();

   // COMPLETAR: práctica 1: crear el VBO de atributos en la GPU
   //
   // añadir el código para crear el VBO (transferir datos y registrar metadatos), se 
   // deben de dar estos pasos:
   //
   // 1. generar un nuevo identificador o nombre de VBO 
   // 2. fija este buffer como buffer 'activo' actualmente en el 'target' GL_ARRAY_BUFFER
   // 3. transferir los datos desde la memoria de la aplicación al VBO en GPU
   // 4. registrar para este índice de atributo, la localización y el formato de la tabla en el buffer 
   // 5. desactivar el buffer
   // 6. habilitar el uso de esta tabla de atributos
   //

   glGenBuffers( 1,  &buffer);
   assert (0<buffer);
   glBindBuffer( GL_ARRAY_BUFFER, buffer);

   glBufferData( GL_ARRAY_BUFFER, tot_size, data, GL_STATIC_DRAW );

   glVertexAttribPointer( index, size, type, GL_FALSE, stride, offset );

   glBindBuffer( GL_ARRAY_BUFFER,  0 );
   glEnableVertexAttribArray( index );

   // comprobar que no ha habido error durante la creación del VBO
   CError();
}
// ------------------------------------------------------------------------------------------------------

DescrVBOAtribs::~DescrVBOAtribs()
{
   delete [] (unsigned char *) own_data ;
   own_data = nullptr ; // probablemente innecesario
   
   if ( buffer != 0 )
   {
      CError();
      glDeleteBuffers( 1, &buffer );
      CError();
      buffer = 0 ; // probablemente innecesario
   }

}

// ******************************************************************************************************
// Clase DescrVBOInds
//
// descriptor de VBOs de índices
// ------------------------------------------------------------------------------------------------------

 
DescrVBOInds::DescrVBOInds( const GLenum p_type, const GLsizei p_count, const void * p_indices )
{
   type     = p_type ;
   count    = p_count ;
   indices  = p_indices ;
   tot_size = count*size_in_bytes( type ) ;
   
   copyIndices();
   comprobar();
}
// ------------------------------------------------------------------------------------------------------

DescrVBOInds::DescrVBOInds( const std::vector<unsigned> & src_vec )
{
   type     = GL_UNSIGNED_INT ;
   count    = src_vec.size() ;
   indices  = src_vec.data() ;
   tot_size = count*size_in_bytes( type ) ;
   
   copyIndices();
   comprobar();
}
// ------------------------------------------------------------------------------------------------------

DescrVBOInds::DescrVBOInds( const std::vector<glm::uvec3> & src_vec )
{
   type     = GL_UNSIGNED_INT ;
   count    = 3*src_vec.size() ;
   indices  = src_vec.data() ;
   tot_size = count*size_in_bytes( type ) ;

   copyIndices();
   comprobar();
}
// ------------------------------------------------------------------------------------------------------

void DescrVBOInds::copyIndices()
{
   assert( indices != nullptr );     // 'indices' debe apuntar a los indices originales
   assert( 0 < tot_size );           // 'tot_size' debe tener el tamaño total de los datos
   assert( own_indices == nullptr ); // impide copiar los datos dos veces 

   own_indices = new unsigned char [tot_size] ;    // reservar memoria
   assert( own_indices != nullptr );               // comprobar que se ha podido reservar
   std::memcpy( own_indices, indices, tot_size );  // copiar bytes
   indices = own_indices ;                         // apuntar a los índices propios
}

// ------------------------------------------------------------------------------------------------------

void DescrVBOInds::comprobar() const 
{
   assert( indices != nullptr ); 
   check_indices_type( type );
   assert( 0 < count );
   assert( type == GL_UNSIGNED_BYTE || type == GL_UNSIGNED_SHORT || type == GL_UNSIGNED_INT  );
   assert( tot_size == count*size_in_bytes( type ));
}
// ------------------------------------------------------------------------------------------------------

void DescrVBOInds::crearVBO( )
{
   // comprobar precondiciones:
   CError(); // comprobar y limpiar errores previos de OpenGL
   assert( buffer == 0 );                 // impedir que se llame más de una vez para este objeto
   comprobar();                           // comprobar que este objeto está en un estado correcto

   // COMPLETAR: práctica 1: crear el VBO de índices en la GPU
   //
   // Añadir el código para crear el VBO en la GPU y transferir los datos, se deben 
   // de dar estos pasos:
   //
   // 1. crear un nuevo nombre o identificador de VBO 
   // 2. activar ('bind') el buffer en el 'target' GL_ELEMENT_ARRAY_BUFFER
   // 3. transferir los datos desde la memoria de la aplicación al VBO en GPU
   //

   glGenBuffers( 1, &buffer );
   assert(0<buffer);
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffer );
      
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, tot_size, indices, GL_STATIC_DRAW );

   // comprueba que no ha habido error al crear el VBO 
   CError();
}
// ---------------------------------------------------------------------------------------------

DescrVBOInds::~DescrVBOInds()
{
   delete [] (unsigned char *) own_indices ;
   own_indices = nullptr ; // probablemente innecesario

   if ( buffer != 0 )
   {
      CError();
      glDeleteBuffers( 1, &buffer );
      CError();
      buffer = 0 ; // probablemente innecesario
   }
}

// ******************************************************************************************************
// Clase DescrVAO
// ------------------------------------------------------------------------------------------------------



DescrVAO::DescrVAO( const unsigned p_num_atribs, DescrVBOAtribs * p_dvbo_posiciones ) 
{
   // comprobar precondiciones 
   assert( 0 < p_num_atribs );
   assert( p_dvbo_posiciones != nullptr ); // no se permite puntero nulo, debe apuntar a algún objeto
   assert( p_dvbo_posiciones->leerIndex() == 0 ); // solo se permite el atributo de posiciones (con índice 0)
   p_dvbo_posiciones->comprobar() ; // comprobar que el vbo está en un estado correcto.
   
   // registrar el número de atributos
   num_atribs = p_num_atribs ;

   // crear el vector con punteros a los descriptores de VBOs (todos a null)
   dvbo_atributo.resize( num_atribs, nullptr ); 

   // crear el vector con los flags de habilitado/deshabilitado (todos a 'true', por defecto están habilitados)
   atrib_habilitado.resize( num_atribs, true );

   // registrar el número de vértices en la tabla de posiciones
   count = p_dvbo_posiciones->leerCount() ;

   // clonar el descriptor de VBO de posiciones y apuntarlo desde este objeto
   dvbo_atributo[0] = p_dvbo_posiciones ;  
}
// ------------------------------------------------------------------------------------------------------

// Comprueba que el estado del VAO es correcto justo antes de añadir una tabla de atributos con índice 'index' 
// (aborta si no)
//
void DescrVAO::check( const unsigned index )
{
   assert( dvbo_atributo[0] != nullptr ); // el VAO ya debe tener el VBO de posiciones.
   assert( 0 < index );  // no permite el índice 0, son las posiciones y se dan al construir el VAO
   assert( index < num_atribs ); // no permite índices fuera de rango
   assert( dvbo_atributo[index] == nullptr ); // no permite añadir un atributo dos veces 
   assert( array == 0 ); // no permite añadir atributos si el VAO ya esá alojado en la GPU
}
// ----------------------------------------------------------------------------

void DescrVAO::agregar( DescrVBOAtribs * p_dvbo_atributo )
{
   // comprobar precondiciones
   assert( p_dvbo_atributo != nullptr );
   const unsigned index = p_dvbo_atributo->leerIndex();
   check( index );
   p_dvbo_atributo->comprobar();
   assert( count == p_dvbo_atributo->leerCount() ); // debe tener el mismo núm de items que el VBO posiciones

   // registrar el descriptor de VBO en la tabla de descriptores de VBOs de atributos
   dvbo_atributo[index] = p_dvbo_atributo ;
}
// ----------------------------------------------------------------------------

void DescrVAO::agregar( DescrVBOInds * p_dvbo_indices )
{
   // comprobar precondiciones:
   assert( p_dvbo_indices != nullptr ); // no permite añadir atributos si el VAO ya esá alojado en la GPU
   p_dvbo_indices->comprobar();

   // registrar el número de índices (3 por tupla) y el tipo
   idxs_count = p_dvbo_indices->leerCount() ;
   idxs_type  = p_dvbo_indices->leerType() ;

   // crear el descriptor VBO y referenciarlo desde este objeto 
   dvbo_indices = p_dvbo_indices ;
}
// ------------------------------------------------------------------------------------------------------

// Crea el VAO en la GPU (solo se puede llamar una vez), deja el VAO activado como VAO actual.
// Crea y activa el VBO de posiciones y todos los VBOs de atributos que se hayan añadido.
// Si se ha añadido una tabla de índices, crea y activa el VBO de índices.
//
void DescrVAO::crearVAO()
{
   CError();
   assert( array == 0 ); // asegurarnos que únicamente se invoca una vez para este descriptor

   // COMPLETAR: práctica 1: crear el VAO y enviar datos de VBOs
   //
   // Escribir el código que crea el VAO en la GPU y registra (asocia) 
   // los VBOs en este VAO. Se deben dar estos pasos:
   //
   // 1. Crear el nombre de VAO y activarlo como VAO actual (hacer 'bind')
   // 2. Para cada VBO de atributos adjunto al VAO (puntero en 'dvbo_atributo' no nulo):
   //       Crear el VBO de atributos en la GPU (usar 'crearVBO')  
   // 3. Si hay índices (puntero dvbo_indices no nulo) entonces, 
   //       Crear el VBO de índices (usar método 'crearVBO')
   // 4. Para cada VBO de atributos adjunto al VAO (puntero en 'dvbo_atributo' no nulo):
   //       Si la tabla está deshabilitada en el vector 'atrib_habilitado':
   //           Deshabilitarla en la GPU con 'glDisableVertexAttribArray'
   //

   glGenVertexArrays( 1, &array );
   assert(array>0);
   glBindVertexArray( array );

   dvbo_atributo[0]->crearVBO();
   for (long unsigned int i=1; i<num_atribs; i++){
      if (dvbo_atributo[i]!=nullptr)
         dvbo_atributo[i]->crearVBO();
   }

   if (dvbo_indices!=nullptr){
      dvbo_indices->crearVBO();
   }

   for (long unsigned int i=1; i<num_atribs; i++){
      if (dvbo_atributo[i]!=nullptr){
         if (!atrib_habilitado[i]){
            glDisableVertexAttribArray( i );
         }
      }
   }


   CError();
}
// ------------------------------------------------------------------------------------------------------

// Habilita o deshabilita una tabla de atributos en este VAO 
//
// @param index (unsigned) índice del atributo a habilitar o deshabilitar (no puede ser 0)
// @param habilitar (boolean) 'true' para habilitar y 'false' para deshabilitar
//
void DescrVAO::habilitarAtrib( const unsigned index, const bool habilitar )
{
   // comprobar precondiciones
   assert( 0 < index ); // el atributo 0 siempre está habilitado, no puede deshabilitarse
   assert( index < num_atribs ); // al índice debe estar en su rango
   assert( dvbo_atributo[index] != nullptr ); // no tiene sentido usarlo para un atributo para el cual no hay tabla

   // registrar el nuevo valor del flag
   atrib_habilitado[index] = habilitar ;
   
   // si el VAO ya se ha enviado a la GPU, actualizar estado del VAO en OpenGL
   if ( array != 0 )
   {
      CError();
      glBindVertexArray( array );
      
      if ( habilitar ) 
         glEnableVertexAttribArray( index );
      else 
         glDisableVertexAttribArray( index );

      glBindVertexArray( 0 );
      CError();
   }

}
// ------------------------------------------------------------------------------------------------------

// Visualiza los vértices de este VAO, usando un modo determinado
//
// @param mode (GLenum) modo de visualización (GL_TRIANGLES, GL_LINES, GL_POINTS,  GL_LINE_STRIP o GL_LINE_LOOP)
//
void DescrVAO::draw( const GLenum mode )
{

   CError();
   assert( dvbo_atributo[0] != nullptr ); // asegurarnos que hay una tabla de coordenadas de posición.
   check_mode( mode );                // comprobar que el modo es el correcto.
   
   // COMPLETAR: práctica 1: visualizar el VAO
   //
   // se debe de escribir código que da estos pasos:
   //
   // 1. Comprobar si el array se ha creado o no (antes de crearse, 'array' vale 0, después es >0). 
   //    Si el array no se ha creado todavía:
   //     - crear el VAO en la GPU (método 'crearVAO'), el VAO queda activado 
   //    Si el array ya se ha creado:
   //     - activar el VAO (con 'glBindVertexArray')
   // 
   // 2. Comprobar si la secuencia es indexada o no lo es (si no es indexada 'dvbo_indices' es nulo)
   //    Si la secuencia es indexada
   //     - visualizar con 'glDrawElements'
   //    Si la secuencia no es indexada 
   //     - visualizar con 'glDrawArrays'
   //
   // 3. Desactivar el VAO (activar el VAO 0 con 'glBindVertexArray')

   if (array != 0){
      glBindVertexArray( array );
   }
   else {
      crearVAO();
   }

   if (dvbo_indices!=nullptr){
      glDrawElements(mode, idxs_count, idxs_type, offset);
   }
   else {
      glDrawArrays(mode, first, count);
   }

   glBindVertexArray( 0 );

   CError();
}
// ------------------------------------------------------------------------------------------------------

// Libera toda la memoria ocupada por el VAO y los VBOs en la memoria de 
// la aplicación y en la GPU. Invalida los identificadores de VBOs y el del VAO
//
DescrVAO::~DescrVAO()
{
   for( unsigned i = 1 ; i < num_atribs ; i++ )
   {  
      delete dvbo_atributo[i] ;
      dvbo_atributo[i] = nullptr ; 
   }
   
   delete dvbo_indices ;
   dvbo_indices = nullptr ; 
   
   if ( array != 0 )
   {
      CError();
      glDeleteVertexArrays( 1, &array );
      CError();
      array = 0 ; // probablemente innecesario
   }
}
// ------------------------------------------------------------------------------------------------------

/* EJERCICIO 1.1 TEORÍA
   std::vector<glm::dvec2> generarPoligono(unsigned int n) {
      std::vector<glm::dvec2> vertices;

      for (unsigned int i = 0; i < n; ++i) {
         double theta = 2.0 * M_PI * i / n;
         double x = cos(theta);
         double y = sin(theta);
         vertices.push_back(glm::dvec2(x, y));
      }

      return vertices;
   }

   void funcion(int lados){
      std::vector<glm::dvec2> vertices = generarPoligono(lados);

      crearVAO(vertices, GL_LINE_LOOP);
      crearVAO(vertices, GL_LINES);
   }
*/

/* EJERCICIO 1.2 TEORÍA
   std::vector<glm::vec3> generarPoligono(unsigned int n, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices){
      for (unsigned int i=0; i<n; i++){
         float angle = (2.0f * M_PI * i) / sides;
         float x = cos(angle);
         float y = sin(angle);
         vertices.push_back({x, y, 0.0f});
      }

      vertices.push_back({0.0f, 0.0f, 0.0f});

      // Crear índices para el tipo de primitiva GL_TRIANGLES (variante a)
      if (primitiveType == GL_TRIANGLES) {
         for (unsigned int i = 0; i < sides; ++i) {
               indices.push_back(i);
               indices.push_back((i + 1) % sides);
               indices.push_back(sides);
         }
      }
      // Crear índices para el tipo de primitiva GL_TRIANGLES (variante b)
      else if (primitiveType == GL_TRIANGLES_ADJACENCY) {
         for (unsigned int i = 0; i < sides; ++i) {
               indices.push_back(i);
               indices.push_back((i + 1) % sides);
               indices.push_back(sides);
               indices.push_back(sides);
               indices.push_back((i + 1) % sides);
               indices.push_back((i + 2) % sides);
         }
      }

      // Crear el descriptor de VBOAtribs para posiciones
      DescrVBOAtribs* dvbo_posiciones = new DescrVBOAtribs(vertices.data(), vertices.size() * 3, 3, 0);
      dvbo_posiciones->comprobar();

      // Crear el descriptor de VAO
      DescrVAO vao(2, dvbo_posiciones);
      vao.crearVAO();

      // Limpiar recursos
      delete dvbo_posiciones;
   }
*/

/* EJERCICIO 1.3 TEORÍA
   void drawFilledPolygonWithEdges(const unsigned int sides) {
      // Crear VAO para las aristas (GL_LINE_LOOP)
      static DescrVBOAtribs* dvbo_posiciones_aristas = nullptr;
      static DescrVAO vao_aristas(1, dvbo_posiciones_aristas);

      if (!dvbo_posiciones_aristas) {
         // Generar vértices para las aristas
         std::vector<glm::dvec2> vertices_aristas;
         for (unsigned int i = 0; i < sides; ++i) {
               float angle = (2.0f * M_PI * i) / sides;
               float x = cos(angle);
               float y = sin(angle);
               vertices_aristas.push_back({x, y});
         }

         // Crear el descriptor de VBOAtribs para posiciones de aristas
         dvbo_posiciones_aristas = new DescrVBOAtribs(vertices_aristas.data(), vertices_aristas.size() * sizeof(Vertex3D), 3, 0);

         // Crear el VAO para las aristas
         vao_aristas.crearVAO();
      }

      // Crear VAO para el relleno (GL_TRIANGLES)
      static DescrVBOAtribs* dvbo_posiciones_relleno = nullptr;
      static DescrVAO vao_relleno(1, dvbo_posiciones_relleno);

      if (!dvbo_posiciones_relleno) {
         // Generar vértices para el relleno (centro + vértices del polígono)
         std::vector<glm::vec3> vertices_relleno;
         vertices_relleno.push_back({0.0f, 0.0f, 0.0f});
         for (unsigned int i = 0; i < sides; ++i) {
               float angle = (2.0f * M_PI * i) / sides;
               float x = cos(angle);
               float y = sin(angle);
               vertices_relleno.push_back({x, y, 0.0f});
         }

         // Crear el descriptor de VBOAtribs para posiciones de relleno
         dvbo_posiciones_relleno = new DescrVBOAtribs(vertices_relleno.data(), vertices_relleno.size() * sizeof(Vertex3D), 3, 0);

         // Crear el VAO para el relleno
         vao_relleno.crearVAO();
      }

      glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f); // Color rojo
      // Visualizar aristas
      vao_aristas.draw(GL_LINE_LOOP);

      glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f); // Color azul
      // Visualizar relleno
      vao_relleno.draw(GL_TRIANGLE_FAN);
   }
*/

/* EJERCICIO 1.4 TEORÍA
   void drawPolygonWithEdgesAndFill(const unsigned int sides) {
      // Crear VAO para aristas y relleno (GL_LINE_LOOP y GL_TRIANGLE_FAN)
      static DescrVBOAtribs* dvbo_posiciones = nullptr;
      static DescrVBOIndices* dvbo_indices = nullptr;
      static DescrVAO vao(1, dvbo_posiciones, dvbo_indices);

      if (!dvbo_posiciones) {
         // Generar vértices para el polígono
         std::vector<glm::dvec2> vertices;
         vertices.push_back({0.0f, 0.0f}); // Vértice central para el relleno
         for (unsigned int i = 0; i < sides; ++i) {
               float angle = (2.0f * M_PI * i) / sides;
               float x = cos(angle);
               float y = sin(angle);
               vertices.push_back({x, y});
         }

         // Crear el descriptor de VBOAtribs para posiciones
         dvbo_posiciones = new DescrVBOAtribs(vertices.data(), vertices.size() * sizeof(Vertex3D), 3, 0);

         // Generar índices para aristas (GL_LINE_LOOP)
         std::vector<unsigned int> indicesAristas;
         for (unsigned int i = 1; i <= sides; ++i) {
               indicesAristas.push_back(i);
         }
         dvbo_indices = new DescrVBOIndices(indicesAristas.data(), indicesAristas.size(), GL_LINE_LOOP);

         // Crear el VAO para aristas y relleno
         vao.crearVAO();
      }

      // Cambiar el color para aristas antes de visualizarlas
      glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f); // Color rojo
      // Visualizar aristas
      vao.draw(GL_LINE_LOOP);

      // Cambiar el color para el relleno antes de visualizarlo
      glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f); // Color azul
      // Visualizar relleno
      vao.draw(GL_TRIANGLE_FAN);
   }
*/

/* EJERCICIO 1.5 TEORÍA

   void drawPolygonWithEdgesAndFilledInterpolated(const unsigned int sides) {
      // Crear VAO para aristas y relleno (GL_LINE_LOOP y GL_TRIANGLE_FAN)
      static DescrVBOAtribs* dvbo_posiciones = nullptr;
      static DescrVBOAtribs* dvbo_colores = nullptr;
      static DescrVBOIndices* dvbo_indices = nullptr;
      static DescrVAO vao(2, dvbo_posiciones, dvbo_colores, dvbo_indices);

      if (!dvbo_posiciones) {
         // Generar vértices para el polígono
         std::vector<glm::dvec3> vertices;
         std::vector<glm::vec3> colores;

         // Vértice central para el relleno
         vertices.push_back({0.0f, 0.0f, 0.0f});
         colores.push_back({1.0f, 1.0f, 1.0f}); // Color blanco para el vértice central

         // Generar colores aleatorios para los vértices
         srand(time(nullptr));
         for (unsigned int i = 0; i < sides; ++i) {
               float angle = (2.0f * M_PI * i) / sides;
               float x = cos(angle);
               float y = sin(angle);
               vertices.push_back({x, y, 0.0f});
               colores.push_back({static_cast<float>(rand()) / RAND_MAX,
                                 static_cast<float>(rand()) / RAND_MAX,
                                 static_cast<float>(rand()) / RAND_MAX});
         }

         // Crear el descriptor de VBOAtribs para posiciones
         dvbo_posiciones = new DescrVBOAtribs(vertices.data(), vertices.size() * sizeof(Vertex3D), 3, 0);

         // Crear el descriptor de VBOAtribs para colores
         dvbo_colores = new DescrVBOAtribs(colores.data(), colores.size() * sizeof(glm::vec3), 3, 1);

         // Generar índices para aristas (GL_LINE_LOOP)
         std::vector<unsigned int> indicesAristas;
         for (unsigned int i = 1; i <= sides; ++i) {
               indicesAristas.push_back(i);
         }
         dvbo_indices = new DescrVBOIndices(indicesAristas.data(), indicesAristas.size(), GL_LINE_LOOP);

         // Crear el VAO para aristas y relleno
         vao.crearVAO();
      }

      // Deshabilitar el uso de la tabla de colores para visualizar aristas
      vao.deshabilitarAtributo(1);

      // Visualizar aristas
      vao.draw(GL_LINE_LOOP);

      // Habilitar el uso de la tabla de colores para el relleno
      vao.habilitarAtributo(1);

      // Visualizar relleno
      vao.draw(GL_TRIANGLE_FAN);
   }

*/