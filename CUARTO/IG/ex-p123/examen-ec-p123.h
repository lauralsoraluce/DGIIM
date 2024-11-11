// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"
#include "malla-revol.h"

class P1MallaCubo: public MallaInd
{
    public:
        P1MallaCubo();
};

/******************************************************/

class P2Rejilla : public MallaInd
{
    public:
        P2Rejilla(unsigned n, unsigned m);
};

/******************************************************/

class P3Cuadrado : public MallaInd
{
    public:
        P3Cuadrado();
};

/******************************************************/

class P3Caja : public NodoGrafoEscena
{
    public:
        P3Caja();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

    protected:
        glm::mat4 *rot_hoja1=nullptr;
        glm::mat4 *rot_hoja2=nullptr;
        glm::mat4 *tras_esfera=nullptr;

};

/******************************************************/

class P3Abatible : public NodoGrafoEscena
{
    public:
        P3Abatible(glm::mat4 *movimiento);
};

/******************************************************/

class P3Cubo : public NodoGrafoEscena
{
    public:
        P3Cubo();
};

/******************************************************/

class P3Tapa : public NodoGrafoEscena
{
    public:
        P3Tapa(glm::mat4 *movimiento1, glm::mat4 *movimiento2);
};

#endif