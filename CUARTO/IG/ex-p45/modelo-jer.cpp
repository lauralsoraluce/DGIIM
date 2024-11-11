// Nombre: Laura, Apellidos: Lázaro Soraluce, Titulación: GIM.
// email: lazarosoraluce@correo.ugr.es, DNI o pasaporte: 45350527R

#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "grafo-escena.h"
#include "ig-aux.h"

using namespace glm;
using namespace std;

Cuco::Cuco()
{   
    ponerIdentificador(1);
    Textura *textura = new Textura("text-madera.jpg");
    Material *material_madera = new Material(textura, 0.5, 0.2, 0.5, 5.0);
    Material *material_bola = new Material(0.5, 0.6, 0.5, 15.0);
    Material *material_fondo = new Material(0.5, 0.6, 0.5, 50.0);

    agregar(new Pendulo(rot_pendulo, material_madera, material_bola));
    agregar(translate(glm::vec3(0.0,0.625,0.0)));
    agregar(new Reloj(rot_horario, rot_minutero, material_madera, material_fondo));
    agregar(translate(glm::vec3(0.0,0.625,0.0)));
    agregar(new Techo(tras_cuco, material_madera));
}

unsigned Cuco::leerNumParametros() const
{
    return 4;
}

void Cuco::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert (iParam < leerNumParametros());
    switch(iParam)
    {
        case 0:
            {
                *rot_pendulo=rotate(float(0.2*sin(2.0*M_PI*t_sec*1.0)), glm::vec3(0.0,0.0,1.0));
            }
        break;
        case 1:
            {   
                //PARA MOVIMIENTO ESPORÁDICO
                /*if (fmod(t_sec, 2) < 0.2) {
                // Solo realiza el movimiento cuando ha pasado aproximadamente un segundo
                *tras_cuco = translate(glm::vec3(0.0, 0.0, 0.25*sin(2.0*M_PI * t_sec*3.0)));*/

                if (fmod(t_sec, 1) < 0.2) {
                // Solo realiza el movimiento cuando ha pasado aproximadamente un segundo
                *tras_cuco = translate(glm::vec3(0.0, 0.0, 0.3*sin(2.0*M_PI * t_sec*1.0)));
                }
                //PARA MOVIMIENTO CONTINUO
                //*tras_cuco=translate(glm::vec3(0.0,0.0, 0.16*sin(3.0 * M_PI * t_sec)));
            }
        break;
        case 2:
            {
                *rot_horario=rotate(float(t_sec*2.0*M_PI/60.0), glm::vec3(0.0,0.0,1.0));
            }
        break;
        case 3:
            {
                *rot_minutero=rotate(float(t_sec*2.0*M_PI*1), glm::vec3(0.0,0.0,1.0));
            }
        break;
    }
}

Pendulo::Pendulo(glm::mat4 *&movimiento, Material *&material1, Material *&material2)
{
    //unsigned identMadera = 1;
    //Textura *textura = new Textura("text-madera.jpg");
    //Material *material_palo = new Material(textura, 0.5, 0.2, 0.5, 5.0);

    ponerIdentificador(2);

    unsigned ind=agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    agregar(translate(glm::vec3(0.0,-2.0,0.0)));
    agregar(scale(glm::vec3(0.20, 0.20, 0.20)));
    agregar(translate(glm::vec3(0.0,1.0,0.0)));
    agregar(scale(glm::vec3(0.2, 9.0, 0.2)));

    NodoGrafoEscena* palo_text = new NodoGrafoEscena();
    Cilindro* palo = new Cilindro(8,40);
    palo_text->agregar(material1);
    palo_text->agregar(palo);
    

    //agregar(new Cilindro(8,40));
    NodoGrafoEscena* resto = new NodoGrafoEscena();
    resto->agregar(scale((glm::vec3(5.0,1.0/9,5.0))));
    resto->agregar(translate(glm::vec3(0.0,-1.0,0.0)));
    Esfera* bola = new Esfera(24,48);
    resto->agregar(material2);
    resto->agregar(bola);
    agregar(resto);
    agregar(palo_text);
    movimiento=leerPtrMatriz(ind);
}

Reloj::Reloj(glm::mat4 *&movimiento1, glm::mat4 *&movimiento2, Material *&material, Material *&material2)
{
    /*Textura *textura = new Textura("text-madera.jpg");
    Material *material = new Material(textura, 0.5, 0.8, 0.2, 100.0);
    agregar(material);*/

    //agregar(translate(glm::vec3(0.0, 2.625, 0.0))); //REVISAR
    agregar(scale(glm::vec3(0.625, 0.625, 0.25))); //REVISAR
    NodoGrafoEscena* caja = new NodoGrafoEscena();
    Cubo24* caja2 = new Cubo24();
    caja->agregar(material);
    caja->agregar(caja2);
    agregar(caja);
    agregar(translate(glm::vec3(0.0,0.0,1.0)));
    agregar(scale(glm::vec3(0.8,0.8,0.2)));
    agregar(translate(glm::vec3(0.0,0.0,-0.5)));
    NodoGrafoEscena* fondo = new NodoGrafoEscena();
    Circulo* fondo2 = new Circulo(40);
    fondo->agregar(material2);
    fondo->agregar(fondo2);
    agregar(fondo);
    agregar(translate(glm::vec3(0.0,0.0,1.0)));
    Aguja* aguja2 = new Aguja(movimiento2);
    aguja2->ponerIdentificador(4);
    agregar(aguja2); //Minutero
    agregar(translate(glm::vec3(0.0,0.0,0.01)));
    
    // PARA QUE SE VEAN BIEN LAS DOS AGUJAS ROTAMOS UNA DE ELLAS
    agregar(rotate(float(3*M_PI/2.0), glm::vec3(0.0,0.0,1.0)));

    agregar(scale(glm::vec3(1.0,0.5,1.0)));    
    Aguja* aguja1 = new Aguja(movimiento1);
    aguja1->ponerIdentificador(5);
    agregar(aguja1); //Horario
    agregar(scale(glm::vec3(1.0,2.0,1.0)));
    agregar(translate(glm::vec3(0.0,0.0,-0.01)));
    agregar(new Circulo(40));
    agregar(translate(glm::vec3(0.0,0.0,-1.0)));
    agregar(rotate(float(M_PI/2.0), glm::vec3(1.0,0.0,0.0)));
    //unsigned ind = agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    //unsigned ind2 = agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    agregar(new Cilindro(8,40));
    //movimiento1=leerPtrMatriz(ind);
    //movimiento2=leerPtrMatriz(ind2);
}

Techo::Techo(glm::mat4 *&movimiento, Material *&material)
{   
    //unsigned identTechoMadera = 1;
    //Textura *textura = new Textura("text-madera.jpg");
    //Material *material_techo = new Material(textura, 0.5, 0.2, 0.5, 5.0);
    

    agregar(translate(glm::vec3(0.0,0.3,0.4)));
    agregar(new Pajaro(movimiento, material));
    agregar(translate(glm::vec3(0.0,-0.3,-0.4)));
    agregar(scale(glm::vec3(0.8,0.6,0.5)));
    agregar(translate(glm::vec3(-0.4,0.0,0.5)));
    agregar(rotate(float(M_PI/2.0), glm::vec3(0.0,1.0,0.0)));
    //unsigned ind=agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    
    CasaXP4* casa = new CasaXP4();
    agregar(material);
    agregar(casa);
    //movimiento=leerPtrMatriz(ind);
}

Aguja::Aguja(glm::mat4 *&movimiento){   
    unsigned ind=agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    ponerColor(glm::vec3(0.0,0.0,0.0));
    agregar(scale(glm::vec3(0.15, 0.3, 0.3)));
    agregar(translate(glm::vec3(0.0,2.0,0.0)));
    agregar(new MallaTriangulo());
    agregar(translate(glm::vec3(0.0,-1.0,0.0)));
    agregar(scale(glm::vec3(0.5,1.0,1.0)));
    agregar(new MallaCuadrado());
    movimiento=leerPtrMatriz(ind);
}

Pajaro::Pajaro(glm::mat4 *&movimiento, Material *&material){

    ponerIdentificador(3);

    unsigned ind=agregar(rotate(0.0f, glm::vec3(0.0,1.0,0.0)));
    ponerColor({1.0,1.0,0.0});
    agregar(translate(glm::vec3(0.0,0.0,0.3)));
    agregar(rotate(float(M_PI/2), glm::vec3(1.0,0.0,0.0)));
    agregar(scale(glm::vec3(0.02,0.02,0.02)));
    agregar(new PrismaTriangular(2));
    //agregar(translate(glm::vec3(0.0,-16.0,0.0)));
    agregar(scale(glm::vec3(4.0,4.0,4.0)));
    agregar(translate(glm::vec3(0.0,-3.0,0.0)));
    agregar(rotate(float(M_PI), glm::vec3(1.0,0.0,0.0)));
    agregar(translate(glm::vec3(0.0,-1.0,-0.5)));
    agregar(scale(glm::vec3(0.2,8.0,0.2)));

    NodoGrafoEscena* palo = new NodoGrafoEscena();
    Cilindro* palito = new Cilindro(16,32);
    palo->agregar(material);
    palo->agregar(palito);

    NodoGrafoEscena* resto = new NodoGrafoEscena();
    resto->agregar(scale(glm::vec3(5.0,0.125,5.0)));
    resto->agregar(translate(glm::vec3(0.0,-1.1,0.5)));
    resto->agregar(rotate(float(3*M_PI/4), glm::vec3(1.0,0.0,0.0)));
    resto->agregar(new MediaEsfera(16,32));
    resto->agregar(rotate(float(M_PI), glm::vec3(1.0,0.0,0.0)));
    resto->agregar(new ConoAltura(16, 32, 3));
    agregar(resto);
    agregar(palo);
    movimiento=leerPtrMatriz(ind);
}