// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP
#include "malla-ind.h"
#include "grafo-escena.h"

class MallaP4: public MallaInd
{
    public:
        MallaP4();
};

class NodoP4: public NodoGrafoEscena {
   public:
      NodoP4();
};

class NodoUrbaP5: public NodoGrafoEscena {
    public:
        NodoUrbaP5(int n);
};

class MiCasa : public NodoGrafoEscena {
   public:
      MiCasa(unsigned i);
      bool cuandoClick(const glm::vec3 & centro_wc) override;
   protected:
      unsigned pos = 0;
      glm::mat4* pm_rot = nullptr;
};


#endif 