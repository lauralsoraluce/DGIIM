#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct stateN0{
    ubicacion jugador;
    ubicacion sonambulo;

    bool operator==(const stateN0 &st) const{
        return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
        sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
        jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula);
    }

    bool operator<(const stateN0 &st) const
    {
        return (jugador.f < st.jugador.f ||
               (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
               (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula));
    }
};

struct stateN1 : public stateN0{
  /*ubicacion jugador;
  ubicacion sonambulo;

  bool operator==(const stateN1 &st) const{
    return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
        sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
        jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula);
  }*/
  
  bool operator<(const stateN1 &st) const{
    return (jugador.f < st.jugador.f ||
        (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
        (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f < st.sonambulo.f) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c<st.sonambulo.c) || 
        ((jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula<st.sonambulo.brujula)));
  }
};

struct stateN2 : public stateN1 {
  bool zapatillas;
  bool bikini;
  int coste;

  bool operator==(const stateN2 &st) const{
    return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
        sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
        jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula && bikini==st.bikini && zapatillas==st.zapatillas && coste==st.coste);
  }

  bool operator<(const stateN2 &st) const{
    return ((jugador.f < st.jugador.f) ||
        ( jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
        (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f < st.sonambulo.f) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c<st.sonambulo.c) || 
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula<st.sonambulo.brujula) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula==st.sonambulo.brujula && !bikini && st.bikini) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula==st.sonambulo.brujula && bikini==st.bikini && !zapatillas && st.zapatillas));
  }

  /*bool operator>(const stateN2 &st) const {
    return (coste>st.coste);
  }*/
};

struct stateN3 : public stateN2 {
  int heuristica;
  bool bikini_son;
  bool zapatillas_son;

  bool operator==(const stateN3 &st) const{
    return (jugador.f == st.jugador.f && jugador.c == st.jugador.c &&
        sonambulo.f == st.sonambulo.f && sonambulo.c == st.sonambulo.c &&
        jugador.brujula == st.jugador.brujula && sonambulo.brujula == st.sonambulo.brujula 
        && bikini==st.bikini && zapatillas==st.zapatillas && coste==st.coste && heuristica==st.heuristica
        && bikini_son==st.bikini_son && zapatillas_son==st.zapatillas_son);
  }

  bool operator<(const stateN3 &st) const{
    return ((jugador.f < st.jugador.f) ||
        (jugador.f == st.jugador.f && jugador.c < st.jugador.c) ||
        (jugador.f == st.jugador.f && jugador.c == st.jugador.c && jugador.brujula < st.jugador.brujula) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f < st.sonambulo.f) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c<st.sonambulo.c) || 
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula<st.sonambulo.brujula) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula==st.sonambulo.brujula && !bikini && st.bikini) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula==st.sonambulo.brujula && bikini==st.bikini && !zapatillas && st.zapatillas) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula==st.sonambulo.brujula && bikini==st.bikini && zapatillas==st.zapatillas && !bikini_son && st.bikini_son) ||
        (jugador.f == st.jugador.f && jugador.c==st.jugador.c && jugador.brujula==st.jugador.brujula && sonambulo.f==st.sonambulo.f && sonambulo.c==st.sonambulo.c && sonambulo.brujula==st.sonambulo.brujula && bikini==st.bikini && zapatillas==st.zapatillas && bikini_son==st.bikini_son && !zapatillas_son && st.zapatillas_son));
  }

  /*bool operator>(const stateN3 &st) const {
    return ((coste+heuristica)>(st.coste+st.heuristica));
  }*/
};

struct nodeN0{
  stateN0 st;
  list<Action> secuencia;

  bool operator==(const nodeN0 &nd) const{
    return (st == nd.st);
  }

  bool operator<(const nodeN0 &nd) const
    {
        //return (st < nd.st);
        if (st.jugador.f<nd.st.jugador.f)
          return true;
        else if (st.jugador.f==nd.st.jugador.f and st.jugador.c < nd.st.jugador.c)
          return true;
        else if (st.jugador.f == nd.st.jugador.f and st.jugador.c==nd.st.jugador.c and st.jugador.brujula<nd.st.jugador.brujula)
          return true;
        else
          return false;
    }
    
    
};

struct nodeN1: public nodeN0{
  stateN1 st;

  bool operator<(const nodeN1 &nd) const
    {
        //return (st < nd.st);
        if (st.jugador.f<nd.st.jugador.f)
          return true;
        else if (st.jugador.f==nd.st.jugador.f and st.jugador.c < nd.st.jugador.c)
          return true;
        else if (st.jugador.f == nd.st.jugador.f and st.jugador.c==nd.st.jugador.c and st.jugador.brujula<nd.st.jugador.brujula)
          return true;
        else if (st.jugador.f == nd.st.jugador.f and st.jugador.c==nd.st.jugador.c and st.jugador.brujula==nd.st.jugador.brujula and st.sonambulo.f<nd.st.sonambulo.f)
          return true;
        else if (st.jugador.f == nd.st.jugador.f and st.jugador.c==nd.st.jugador.c and st.jugador.brujula==nd.st.jugador.brujula and st.sonambulo.f==nd.st.sonambulo.f and st.sonambulo.c<nd.st.sonambulo.c)
          return true;
        else if (st.jugador.f == nd.st.jugador.f and st.jugador.c==nd.st.jugador.c and st.jugador.brujula==nd.st.jugador.brujula and st.sonambulo.f==nd.st.sonambulo.f and st.sonambulo.c==nd.st.sonambulo.c and st.sonambulo.brujula<nd.st.sonambulo.brujula)
          return true;
        else
          return false;
    }
};

struct nodeN2: public nodeN1{
  stateN2 st;

  /*bool operator<(const nodeN2 &nd) const 
  {
    return (st.coste<nd.st.coste);
  }*/
  
  bool operator>(const nodeN2 &nd) const {
     return (st.coste>nd.st.coste);
  }
    
};

struct nodeN3: public nodeN2{
  stateN3 st;

  /*bool operator<(const nodeN3 &nd) const 
  {
    return ((st.coste+st.heuristica)<(nd.st.coste+nd.st.heuristica));
  }*/
  
  bool operator>(const nodeN3 &nd) const {
     return ((st.coste + st.heuristica)>(nd.st.coste+nd.st.heuristica));
  }

  bool operator<(const nodeN3 &nd) const {
    return (st<nd.st);
  }
    
};

class ComportamientoJugador : public Comportamiento {
  public:
    // PARA EL NIVEL 4
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      hayPlan=false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    
    void VisualizaPlan(const stateN0 &st, const list<Action> &plan);


  private:
    // Declarar Variables de Estado
    list<Action> plan;
    bool hayPlan;

    stateN3 c_state; 
    ubicacion goal;
    //Action last_action;

    int primera_vez=0; // La primera accion del nivel 4
    Action last_action=actIDLE;


};

list<Action> AvanzaASaltosDeCaballo();

void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const stateN3 &st, vector<vector<unsigned char>> &matriz);

void PonerTerrenoEnMatrizS(const vector<unsigned char> &terreno, const stateN3 &st, vector<vector<unsigned char>> &matriz);

bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa);

ubicacion NextCasilla(const ubicacion &pos);

stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> &mapa);

stateN1 apply1(const Action &a, const stateN1 &st, const vector<vector<unsigned char>> &mapa);

stateN2 apply2(const Action &a, const stateN2 &st, const vector<vector<unsigned char>> &mapa);

stateN3 apply3(const Action &a, const stateN3 &st, const vector<vector<unsigned char>> &mapa);

stateN3 apply4(const Action &a, const stateN3 &st, const vector<vector<unsigned char>> &mapa);

bool Find(const stateN0 &item, const list<stateN0> &lista);

bool Find(const stateN0 &item, const list<nodeN0> &lista);

bool AnchuraSoloJugador(const stateN0 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &mapa);

bool AnchuraJugadorYSonambulo(const stateN1 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &mapa);

bool Dijkstra (const stateN2 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &matriz);

bool AEstrella (const stateN3 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &matriz);

bool AEstrella2 (const stateN3 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &matriz);

int DistanciaChebyshev (const ubicacion &inicio, const ubicacion &fin);

int DistanciaManhattan (const ubicacion &inicio, const ubicacion &fin);

int CosteAccionN2 (const Action &accion, const unsigned char &terreno, const stateN2 &estado);

int CosteAccionN3 (const Action &accion, const unsigned char &terreno, const stateN3 &estado);

void AnularMatriz(vector<vector<unsigned char>> &matriz);

bool SonambuloALaVista(const stateN0 &st, const vector<vector<unsigned char>> &mapa);

void PintarPrecipiciosBordes(const stateN3 &st, vector<vector<unsigned char>> &matriz);

#endif