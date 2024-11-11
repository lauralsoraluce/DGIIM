// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

using namespace std;
using namespace glm;

class Cuco : public NodoGrafoEscena
{
    public:
        Cuco();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

    protected:
        glm::mat4 *rot_pendulo = nullptr;
        glm::mat4 *tras_cuco = nullptr;
        glm::mat4 *rot_horario = nullptr;
        glm::mat4 *rot_minutero = nullptr;
};

class Reloj : public NodoGrafoEscena
{
    public:
        Reloj(glm::mat4 *&movimiento1, glm::mat4 *&movimiento2, Material *&material, Material *&material2);
};

class Pendulo : public NodoGrafoEscena
{
    public:
        Pendulo(glm::mat4 *&movimiento, Material *&material, Material *&material2);
};

class Pajaro : public NodoGrafoEscena
{
    public:
        Pajaro(glm::mat4 *&movimiento, Material *&Material);
};

class Techo : public NodoGrafoEscena
{
    public:
        Techo(glm::mat4 *&movimiento, Material *&material);
};

class Aguja : public NodoGrafoEscena
{
    public:
        Aguja(glm::mat4 *&movimiento);
};

#endif