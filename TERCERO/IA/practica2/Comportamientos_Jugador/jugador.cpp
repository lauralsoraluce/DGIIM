#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;
	// Incluir aquí el comportamiento del agente jugador
	if (sensores.nivel!=4)
	{
		if (!hayPlan){
			// Invocar al método de búsqueda
			cout << "Calculando plan..." << endl;
			goal.f 						= sensores.destinoF;
			goal.c 						= sensores.destinoC;
			c_state.jugador.f 			= sensores.posF;
			c_state.jugador.c 			= sensores.posC;
			c_state.jugador.brujula 	= sensores.sentido;
			c_state.sonambulo.f 		= sensores.SONposF;
			c_state.sonambulo.c 		= sensores.SONposC;
			c_state.sonambulo.brujula 	= sensores.SONsentido;

			// Inicializamos las variables bikini y zapatillas
			if (mapaResultado[c_state.jugador.f][c_state.jugador.c]=='K'){
				c_state.bikini=true;
				c_state.zapatillas=false;
			}
			else if (mapaResultado[c_state.jugador.f][c_state.jugador.c]=='D'){
				c_state.zapatillas=true;
				c_state.bikini=false;
			}
			else {
				c_state.bikini=false;
				c_state.zapatillas=false;
			}

			if (mapaResultado[c_state.sonambulo.f][c_state.sonambulo.c]=='K'){
				c_state.bikini_son=true;
				c_state.zapatillas_son=false;
			}
			else if (mapaResultado[c_state.sonambulo.f][c_state.sonambulo.c]=='D'){
				c_state.zapatillas_son=true;
				c_state.bikini_son=false;
			}
			else {
				c_state.bikini_son=false;
				c_state.zapatillas_son=false;
			}
			
			switch (sensores.nivel){
				case 0:
					hayPlan = AnchuraSoloJugador(c_state, goal, plan, mapaResultado);
					break;
				case 1:
					hayPlan = AnchuraJugadorYSonambulo(c_state, goal, plan, mapaResultado);
					break;
				case 2: // Incluir aqui la llamada al algoritmo de búsqueda para el nivel 2
					hayPlan = Dijkstra(c_state, goal, plan, mapaResultado);
					break;
				case 3: // Incluir aqui la llamada al algoritmo de búsqueda para el nivel 3
					hayPlan = AEstrella(c_state, goal, plan, mapaResultado);
					break;
			}		
			if (plan.size()>0) {
				VisualizaPlan(c_state, plan);
				hayPlan=true;
			}
		}
		if (hayPlan and plan.size()>0){
			cout << "Ejecutando siguiente acción del plan" << endl;
			accion = plan.front();
			plan.pop_front();
		}
		if (plan.size()== 0){
			cout << "Se completó el plan" << endl;
			hayPlan = false;
		}
	}
	else {
		
		if (!hayPlan){

			if (sensores.posF==-1 and primera_vez==0){
				PintarPrecipiciosBordes(c_state, mapaResultado);
				primera_vez++;
				last_action=actWHEREIS;
				return actWHEREIS;
			}
			else {
				goal.f=sensores.destinoF;
				goal.c=sensores.destinoC;
				c_state.jugador.f=sensores.posF;
				c_state.jugador.c=sensores.posC;
				c_state.jugador.brujula=sensores.sentido;
				c_state.sonambulo.f=sensores.SONposF;
				c_state.sonambulo.c=sensores.SONposC;
				c_state.sonambulo.brujula=sensores.SONsentido;
			}
			
			hayPlan=AEstrella2(c_state, goal, plan, mapaResultado);
		}
		if (hayPlan and plan.size()>0){
			if (!sensores.colision){
				c_state=apply4(last_action, c_state, mapaResultado);
			}
			cout << "Ejecutando siguiente acción del plan" << endl;
			accion = plan.front();
			last_action=accion;
			if (accion==actFORWARD or accion==actTURN_L or accion==actTURN_R){
				PonerTerrenoEnMatriz(sensores.terreno, c_state, mapaResultado);
			}
			plan.pop_front();
		}
		if (plan.size()==0){
			cout << "Se completó el plan" << endl;
			hayPlan = false;
			primera_vez=0;
		}
	}

	return accion;
}

void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const stateN3 &st, vector<vector<unsigned char>> &matriz)
{
    int count=0;

    switch(st.jugador.brujula){ 
      case norte:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.jugador.f-i][st.jugador.c-i+j]=terreno[count];
              count++;
            }
          }
        break; //Si estaba mirando al norte
      case este:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.jugador.f-i+j][st.jugador.c+i]=terreno[count];
              count++;
            }
          }
        break;
      case sur:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.jugador.f+i][st.jugador.c-j+i]=terreno[count];
              count++;
            }
          }
        break;
      case oeste:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.jugador.f+i-j][st.jugador.c-i]=terreno[count];
              count++;
            }
          }
        break;
      case noroeste:
        matriz[st.jugador.f][st.jugador.c]=terreno[0];
        matriz[st.jugador.f][st.jugador.c-1]=terreno[1];
        matriz[st.jugador.f-1][st.jugador.c-1]=terreno[2];
        matriz[st.jugador.f-1][st.jugador.c]=terreno[3];
        matriz[st.jugador.f][st.jugador.c-2]=terreno[4];
        matriz[st.jugador.f-1][st.jugador.c-2]=terreno[5];
        matriz[st.jugador.f-2][st.jugador.c-2]=terreno[6];
        matriz[st.jugador.f-2][st.jugador.c-1]=terreno[7];
        matriz[st.jugador.f-2][st.jugador.c]=terreno[8];
        matriz[st.jugador.f][st.jugador.c-3]=terreno[9];
        matriz[st.jugador.f-1][st.jugador.c-3]=terreno[10];
        matriz[st.jugador.f-2][st.jugador.c-3]=terreno[11];
        matriz[st.jugador.f-3][st.jugador.c-3]=terreno[12];
        matriz[st.jugador.f-3][st.jugador.c-2]=terreno[13];
        matriz[st.jugador.f-3][st.jugador.c-1]=terreno[14];
        matriz[st.jugador.f-3][st.jugador.c]=terreno[15];
        break;
      case noreste:
        matriz[st.jugador.f][st.jugador.c]=terreno[0];
        matriz[st.jugador.f-1][st.jugador.c]=terreno[1];
        matriz[st.jugador.f-1][st.jugador.c+1]=terreno[2];
        matriz[st.jugador.f][st.jugador.c+1]=terreno[3];
        matriz[st.jugador.f-2][st.jugador.c]=terreno[4];
        matriz[st.jugador.f-2][st.jugador.c+1]=terreno[5];
        matriz[st.jugador.f-2][st.jugador.c+2]=terreno[6];
        matriz[st.jugador.f-1][st.jugador.c+2]=terreno[7];
        matriz[st.jugador.f][st.jugador.c+2]=terreno[8];
        matriz[st.jugador.f-3][st.jugador.c]=terreno[9];
        matriz[st.jugador.f-3][st.jugador.c+1]=terreno[10];
        matriz[st.jugador.f-3][st.jugador.c+2]=terreno[11];
        matriz[st.jugador.f-3][st.jugador.c+3]=terreno[12];
        matriz[st.jugador.f-2][st.jugador.c+3]=terreno[13];
        matriz[st.jugador.f-1][st.jugador.c+3]=terreno[14];
        matriz[st.jugador.f][st.jugador.c+3]=terreno[15];
        break;
      case suroeste:
        matriz[st.jugador.f][st.jugador.c]=terreno[0];
        matriz[st.jugador.f+1][st.jugador.c]=terreno[1];
        matriz[st.jugador.f+1][st.jugador.c-1]=terreno[2];
        matriz[st.jugador.f][st.jugador.c-1]=terreno[3];
        matriz[st.jugador.f+2][st.jugador.c]=terreno[4];
        matriz[st.jugador.f+2][st.jugador.c-1]=terreno[5];
        matriz[st.jugador.f+2][st.jugador.c-2]=terreno[6];
        matriz[st.jugador.f+1][st.jugador.c-2]=terreno[7];
        matriz[st.jugador.f][st.jugador.c-2]=terreno[8];
        matriz[st.jugador.f+3][st.jugador.c]=terreno[9];
        matriz[st.jugador.f+3][st.jugador.c-1]=terreno[10];
        matriz[st.jugador.f+3][st.jugador.c-2]=terreno[11];
        matriz[st.jugador.f+3][st.jugador.c-3]=terreno[12];
        matriz[st.jugador.f+2][st.jugador.c-3]=terreno[13];
        matriz[st.jugador.f+1][st.jugador.c-3]=terreno[14];
        matriz[st.jugador.f][st.jugador.c-3]=terreno[15];
      break;
      case sureste:
        matriz[st.jugador.f][st.jugador.c]=terreno[0];
        matriz[st.jugador.f][st.jugador.c+1]=terreno[1];
        matriz[st.jugador.f+1][st.jugador.c+1]=terreno[2];
        matriz[st.jugador.f+1][st.jugador.c]=terreno[3];
        matriz[st.jugador.f][st.jugador.c+2]=terreno[4];
        matriz[st.jugador.f+1][st.jugador.c+2]=terreno[5];
        matriz[st.jugador.f+2][st.jugador.c+2]=terreno[6];
        matriz[st.jugador.f+2][st.jugador.c+1]=terreno[7];
        matriz[st.jugador.f+2][st.jugador.c]=terreno[8];
        matriz[st.jugador.f][st.jugador.c+3]=terreno[9];
        matriz[st.jugador.f+1][st.jugador.c+3]=terreno[10];
        matriz[st.jugador.f+2][st.jugador.c+3]=terreno[11];
        matriz[st.jugador.f+3][st.jugador.c+3]=terreno[12];
        matriz[st.jugador.f+3][st.jugador.c+2]=terreno[13];
        matriz[st.jugador.f+3][st.jugador.c+1]=terreno[14];
        matriz[st.jugador.f+3][st.jugador.c]=terreno[15];
        break;
	}
}

void PonerTerrenoEnMatrizS(const vector<unsigned char> &terreno, const stateN3 &st, vector<vector<unsigned char>> &matriz)
{
    int count=0;

    switch(st.sonambulo.brujula){ 
      case norte:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.sonambulo.f-i][st.sonambulo.c-i+j]=terreno[count];
              count++;
            }
          }
        break; //Si estaba mirando al norte
      case este:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.sonambulo.f-i+j][st.sonambulo.c+i]=terreno[count];
              count++;
            }
          }
        break;
      case sur:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.sonambulo.f+i][st.sonambulo.c-j+i]=terreno[count];
              count++;
            }
          }
        break;
      case oeste:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.sonambulo.f+i-j][st.sonambulo.c-i]=terreno[count];
              count++;
            }
          }
        break;
      case noroeste:
        matriz[st.sonambulo.f][st.sonambulo.c]=terreno[0];
        matriz[st.sonambulo.f][st.sonambulo.c-1]=terreno[1];
        matriz[st.sonambulo.f-1][st.sonambulo.c-1]=terreno[2];
        matriz[st.sonambulo.f-1][st.sonambulo.c]=terreno[3];
        matriz[st.sonambulo.f][st.sonambulo.c-2]=terreno[4];
        matriz[st.sonambulo.f-1][st.sonambulo.c-2]=terreno[5];
        matriz[st.sonambulo.f-2][st.sonambulo.c-2]=terreno[6];
        matriz[st.sonambulo.f-2][st.sonambulo.c-1]=terreno[7];
        matriz[st.sonambulo.f-2][st.sonambulo.c]=terreno[8];
        matriz[st.sonambulo.f][st.sonambulo.c-3]=terreno[9];
        matriz[st.sonambulo.f-1][st.sonambulo.c-3]=terreno[10];
        matriz[st.sonambulo.f-2][st.sonambulo.c-3]=terreno[11];
        matriz[st.sonambulo.f-3][st.sonambulo.c-3]=terreno[12];
        matriz[st.sonambulo.f-3][st.sonambulo.c-2]=terreno[13];
        matriz[st.sonambulo.f-3][st.sonambulo.c-1]=terreno[14];
        matriz[st.sonambulo.f-3][st.sonambulo.c]=terreno[15];
        break;
      case noreste:
        matriz[st.sonambulo.f][st.sonambulo.c]=terreno[0];
        matriz[st.sonambulo.f-1][st.sonambulo.c]=terreno[1];
        matriz[st.sonambulo.f-1][st.sonambulo.c+1]=terreno[2];
        matriz[st.sonambulo.f][st.sonambulo.c+1]=terreno[3];
        matriz[st.sonambulo.f-2][st.sonambulo.c]=terreno[4];
        matriz[st.sonambulo.f-2][st.sonambulo.c+1]=terreno[5];
        matriz[st.sonambulo.f-2][st.sonambulo.c+2]=terreno[6];
        matriz[st.sonambulo.f-1][st.sonambulo.c+2]=terreno[7];
        matriz[st.sonambulo.f][st.sonambulo.c+2]=terreno[8];
        matriz[st.sonambulo.f-3][st.sonambulo.c]=terreno[9];
        matriz[st.sonambulo.f-3][st.sonambulo.c+1]=terreno[10];
        matriz[st.sonambulo.f-3][st.sonambulo.c+2]=terreno[11];
        matriz[st.sonambulo.f-3][st.sonambulo.c+3]=terreno[12];
        matriz[st.sonambulo.f-2][st.sonambulo.c+3]=terreno[13];
        matriz[st.sonambulo.f-1][st.sonambulo.c+3]=terreno[14];
        matriz[st.sonambulo.f][st.sonambulo.c+3]=terreno[15];
        break;
      case suroeste:
        matriz[st.sonambulo.f][st.sonambulo.c]=terreno[0];
        matriz[st.sonambulo.f+1][st.sonambulo.c]=terreno[1];
        matriz[st.sonambulo.f+1][st.sonambulo.c-1]=terreno[2];
        matriz[st.sonambulo.f][st.sonambulo.c-1]=terreno[3];
        matriz[st.sonambulo.f+2][st.sonambulo.c]=terreno[4];
        matriz[st.sonambulo.f+2][st.sonambulo.c-1]=terreno[5];
        matriz[st.sonambulo.f+2][st.sonambulo.c-2]=terreno[6];
        matriz[st.sonambulo.f+1][st.sonambulo.c-2]=terreno[7];
        matriz[st.sonambulo.f][st.sonambulo.c-2]=terreno[8];
        matriz[st.sonambulo.f+3][st.sonambulo.c]=terreno[9];
        matriz[st.sonambulo.f+3][st.sonambulo.c-1]=terreno[10];
        matriz[st.sonambulo.f+3][st.sonambulo.c-2]=terreno[11];
        matriz[st.sonambulo.f+3][st.sonambulo.c-3]=terreno[12];
        matriz[st.sonambulo.f+2][st.sonambulo.c-3]=terreno[13];
        matriz[st.sonambulo.f+1][st.sonambulo.c-3]=terreno[14];
        matriz[st.sonambulo.f][st.sonambulo.c-3]=terreno[15];
      break;
      case sureste:
        matriz[st.sonambulo.f][st.sonambulo.c]=terreno[0];
        matriz[st.sonambulo.f][st.sonambulo.c+1]=terreno[1];
        matriz[st.sonambulo.f+1][st.sonambulo.c+1]=terreno[2];
        matriz[st.sonambulo.f+1][st.sonambulo.c]=terreno[3];
        matriz[st.sonambulo.f][st.sonambulo.c+2]=terreno[4];
        matriz[st.sonambulo.f+1][st.sonambulo.c+2]=terreno[5];
        matriz[st.sonambulo.f+2][st.sonambulo.c+2]=terreno[6];
        matriz[st.sonambulo.f+2][st.sonambulo.c+1]=terreno[7];
        matriz[st.sonambulo.f+2][st.sonambulo.c]=terreno[8];
        matriz[st.sonambulo.f][st.sonambulo.c+3]=terreno[9];
        matriz[st.sonambulo.f+1][st.sonambulo.c+3]=terreno[10];
        matriz[st.sonambulo.f+2][st.sonambulo.c+3]=terreno[11];
        matriz[st.sonambulo.f+3][st.sonambulo.c+3]=terreno[12];
        matriz[st.sonambulo.f+3][st.sonambulo.c+2]=terreno[13];
        matriz[st.sonambulo.f+3][st.sonambulo.c+1]=terreno[14];
        matriz[st.sonambulo.f+3][st.sonambulo.c]=terreno[15];
        break;
	}
}

list<Action> AvanzaASaltosDeCaballo(){
	list<Action> secuencia;
	secuencia.push_back(actFORWARD);
	secuencia.push_back(actFORWARD);
	secuencia.push_back(actTURN_R);
    secuencia.push_back(actFORWARD);
	return secuencia;
}

bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa)
{
	return (mapa[x.f][x.c] != 'P' and mapa[x.f][x.c] != 'M');
}

/** Devuelve la ubicación siguiente según el avance del agente*/
ubicacion NextCasilla(const ubicacion &pos)
{
	ubicacion next = pos;
	switch (pos.brujula)
	{
	case norte:
		next.f = pos.f - 1;
		break;
	case noreste:
		next.f = pos.f - 1;
		next.c = pos.c + 1;
		break;
	case este:
		next.c = pos.c + 1;
		break;
	case sureste:
		next.f = pos.f + 1;
		next.c = pos.c + 1;
		break;
	case sur:
		next.f = pos.f + 1;
		break;
	case suroeste:
		next.f = pos.f + 1;
		next.c = pos.c - 1;
		break;
	case oeste:
		next.c = pos.c - 1;
		break;
	case noroeste:
		next.f = pos.f - 1;
		next.c = pos.c - 1;
		break;
	default:
		break;
	}

	return next;
}

/** Comprobar si el jugador tiene al sonámbulo en su campo visual CAMBIAR!!!!!!!!!!!!*/
bool SonambuloALaVista(const stateN0 &st, const vector<vector<unsigned char>> &mapa)
{
	switch ( st.jugador.brujula ){
		case 0:
			for ( int i=1;  i<4; i++ ) 
			{
				if ( st.sonambulo.f == ((st.jugador.f)-i) )
				{
					if ( abs(st.sonambulo.c - st.jugador.c) <= i )
					{
						return true;
					}
				}
			}
		break;
		case 2:
			for ( int i=1;  i<4; i++ ) 
			{
				if ( st.sonambulo.c == ((st.jugador.c)+i) )
				{
					if ( abs(st.sonambulo.f - st.jugador.f) <= i )
					{
						return true;
					}
				}
			}
		break;
		case 4:
			for ( int i=1;  i<4; i++ ) 
			{
				if ( st.sonambulo.f == ((st.jugador.f)+i) )
				{
					if ( abs(st.sonambulo.c - st.jugador.c) <= i )
					{
						return true;
					}
				}
			}
		break;
		case 6:
			for ( int i=1;  i<4; i++ ) 
			{
				if ( st.sonambulo.c == ((st.jugador.c)-i) )
				{
					if ( abs(st.sonambulo.f - st.jugador.f) <= i )
					{
						return true;
					}
				}
			}
		break;
	}
	return false;
}

/** Devuelve el estado que se genera si el agente puede avanzar.
 * Si no puede avanzar, se devuelve como salida el mismo estado de entrada.
 */
stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN0 st_result = st;
  ubicacion sig_ubicacion;

  switch (a){
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.sonambulo.f and sig_ubicacion.c==st.sonambulo.c)){
      st_result.jugador = sig_ubicacion;
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
  }
  return st_result;
}

/** Nivel 1 */
stateN1 apply1(const Action &a, const stateN1 &st, const vector<vector<unsigned char>> &mapa)
{

	stateN1 st_result = st;
  	ubicacion sig_ubicacion;

	switch (a){
	case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
	sig_ubicacion = NextCasilla(st.jugador);
	if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.sonambulo.f and sig_ubicacion.c==st.sonambulo.c))
	{
		st_result.jugador = sig_ubicacion;
	}
	break;
	case actTURN_L:
	st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
	break;

	case actTURN_R:
	st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
	break;

	case actSON_FORWARD:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	sig_ubicacion=NextCasilla(st.sonambulo);
	if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.jugador.f and sig_ubicacion.c==st.jugador.c))
	{
		st_result.sonambulo=sig_ubicacion;
	}
	break;

	case actSON_TURN_SL:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	st_result.sonambulo.brujula=static_cast<Orientacion>((st_result.sonambulo.brujula+7)%8);
	break;

	case actSON_TURN_SR:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	st_result.sonambulo.brujula=static_cast<Orientacion>((st_result.sonambulo.brujula+1)%8);
	break;
	
	}
	return st_result;
}

stateN2 apply2(const Action &a, const stateN2 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN2 st_result = st;
  ubicacion sig_ubicacion;

  switch (a){
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.sonambulo.f and sig_ubicacion.c==st.sonambulo.c)){
      st_result.jugador = sig_ubicacion;
	  //ACTUALIZAMOS VARIABLES BIKINI Y ZAPATILLAS
	  if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='K'){
		if (st_result.zapatillas==true){
			st_result.zapatillas=false;
		}
		st_result.bikini=true;
	  }
	  else if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='D'){
		if (st_result.bikini==true){
			st_result.bikini=false;
		}
		st_result.zapatillas=true;
	  }
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
	case actIDLE:
		if (mapa[st_result.jugador.f][st_result.jugador.c]=='K'){
			if (st_result.zapatillas==true){
				st_result.zapatillas=false;
			}
			st_result.bikini=true;
		}
		else if (mapa[st_result.jugador.f][st_result.jugador.c]=='D'){
			if (st_result.bikini==true){
				st_result.bikini=false;
			}
			st_result.zapatillas=true;
		}
	break;
  }
  return st_result;
}

stateN3 apply3(const Action &a, const stateN3 &st, const vector<vector<unsigned char>> &mapa)
{
  stateN3 st_result = st;
  ubicacion sig_ubicacion;

  switch (a){
  case actSON_FORWARD:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	sig_ubicacion=NextCasilla(st.sonambulo);
	if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.jugador.f and sig_ubicacion.c==st.jugador.c))
	{
		st_result.sonambulo=sig_ubicacion;

		if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='K'){
			if (st_result.zapatillas_son==true){
				st_result.zapatillas_son=false;
			}
			st_result.bikini_son=true;
		}
		else if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='D'){
			if (st_result.bikini_son==true){
				st_result.bikini_son=false;
			}
			st_result.zapatillas_son=true;
		}
	}
  break;
  case actSON_TURN_SL:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	st_result.sonambulo.brujula=static_cast<Orientacion>((st_result.sonambulo.brujula+7)%8);
  break;
  case actSON_TURN_SR:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	st_result.sonambulo.brujula=static_cast<Orientacion>((st_result.sonambulo.brujula+1)%8);
  break;
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.sonambulo.f and sig_ubicacion.c==st.sonambulo.c)){
      st_result.jugador = sig_ubicacion;
	  //ACTUALIZAMOS VARIABLES BIKINI Y ZAPATILLAS
	  if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='K'){
		if (st_result.zapatillas==true){
			st_result.zapatillas=false;
		}
		st_result.bikini=true;
	  }
	  else if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='D'){
		if (st_result.bikini==true){
			st_result.bikini=false;
		}
		st_result.zapatillas=true;
	  }
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
	case actIDLE:
		if (mapa[st_result.jugador.f][st_result.jugador.c]=='K'){
			if (st_result.zapatillas==true){
				st_result.zapatillas=false;
			}
			st_result.bikini=true;
		}
		else if (mapa[st_result.jugador.f][st_result.jugador.c]=='D'){
			if (st_result.bikini==true){
				st_result.bikini=false;
			}
			st_result.zapatillas=true;
		}
		if (mapa[st_result.sonambulo.f][st_result.sonambulo.c]=='K'){
			if (st_result.zapatillas_son==true){
				st_result.zapatillas_son=false;
			}
			st_result.bikini_son=true;
		}
		else if (mapa[st_result.sonambulo.f][st_result.sonambulo.c]=='D'){
			if (st_result.bikini_son==true){
				st_result.bikini_son=false;
			}
			st_result.zapatillas_son=true;
		}
	break;
  }
  return st_result;
}

stateN3 apply4(const Action &a, const stateN3 &st, const vector<vector<unsigned char>> &mapa)
{

	stateN3 st_result = st;
  	ubicacion sig_ubicacion;

  switch (a){
  case actSON_FORWARD:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	sig_ubicacion=NextCasilla(st.sonambulo);
	if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.jugador.f and sig_ubicacion.c==st.jugador.c))
	{
		st_result.sonambulo=sig_ubicacion;

		if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='K'){
			if (st_result.zapatillas_son==true){
				st_result.zapatillas_son=false;
			}
			st_result.bikini_son=true;
		}
		else if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='D'){
			if (st_result.bikini_son==true){
				st_result.bikini_son=false;
			}
			st_result.zapatillas_son=true;
		}
	}
  break;
  case actSON_TURN_SL:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	st_result.sonambulo.brujula=static_cast<Orientacion>((st_result.sonambulo.brujula+7)%8);
  break;
  case actSON_TURN_SR:
	if (!SonambuloALaVista(st, mapa))
	{
		return st;
	}
	st_result.sonambulo.brujula=static_cast<Orientacion>((st_result.sonambulo.brujula+1)%8);
  break;
  case actFORWARD: // si casilla delante es transitable y no está ocupada por el sonámbulo
    sig_ubicacion = NextCasilla(st.jugador);
    if (CasillaTransitable(sig_ubicacion, mapa) and !(sig_ubicacion.f==st.sonambulo.f and sig_ubicacion.c==st.sonambulo.c)){
      st_result.jugador = sig_ubicacion;
	  //ACTUALIZAMOS VARIABLES BIKINI Y ZAPATILLAS
	  if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='K'){
		if (st_result.zapatillas==true){
			st_result.zapatillas=false;
		}
		st_result.bikini=true;
	  }
	  else if (mapa[sig_ubicacion.f][sig_ubicacion.c]=='D'){
		if (st_result.bikini==true){
			st_result.bikini=false;
		}
		st_result.zapatillas=true;
	  }
    }
    break;
  case actTURN_L:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
    break;

  case actTURN_R:
    st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 2) % 8);
    break;
	case actIDLE:
		if (mapa[st_result.jugador.f][st_result.jugador.c]=='K'){
			if (st_result.zapatillas==true){
				st_result.zapatillas=false;
			}
			st_result.bikini=true;
		}
		else if (mapa[st_result.jugador.f][st_result.jugador.c]=='D'){
			if (st_result.bikini==true){
				st_result.bikini=false;
			}
			st_result.zapatillas=true;
		}
		if (mapa[st_result.sonambulo.f][st_result.sonambulo.c]=='K'){
			if (st_result.zapatillas_son==true){
				st_result.zapatillas_son=false;
			}
			st_result.bikini_son=true;
		}
		else if (mapa[st_result.sonambulo.f][st_result.sonambulo.c]=='D'){
			if (st_result.bikini_son==true){
				st_result.bikini_son=false;
			}
			st_result.zapatillas_son=true;
		}
	break;
  }
  return st_result;
}

/** Encuentra si el elmento item está en lista */
bool Find(const stateN0 &item, const list<stateN0> &lista)
{
  auto it = lista.begin();
  while (it != lista.end() and !((*it) == item))
    it++;

  return (!(it == lista.end()));
}

bool Find(const stateN0 &item, const list<nodeN0> &lista)
{
  auto it = lista.begin();
  while (it != lista.end() and !((*it).st == item))
    it++;

  return (!(it == lista.end()));
}

/** primera aproximación a la implimentación de la busqueda en anchura */
bool AnchuraSoloJugador(const stateN0 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &mapa)
{
	nodeN0 current_node;
	current_node.st = inicio;
	list<nodeN0> frontier;
	set<nodeN0> explored;
	bool SolutionFound = (current_node.st.jugador.f == final.f and current_node.st.jugador.c == final.c);
	frontier.push_back(current_node);

	while (!frontier.empty() and !SolutionFound)
	{
		frontier.pop_front();
		explored.insert(current_node);

		// Generar hijo actFORWARD
		nodeN0 child_forward = current_node;
		child_forward.st = apply(actFORWARD, current_node.st, mapa);
		if (child_forward.st.jugador.f == final.f and child_forward.st.jugador.c == final.c)
		{
			child_forward.secuencia.push_back(actFORWARD); 
			current_node = child_forward;
			SolutionFound = true;
		}
		else if (explored.find(child_forward)==explored.end())
		{
			child_forward.secuencia.push_back(actFORWARD);
			frontier.push_back(child_forward);
		}

		if (!SolutionFound)
		{
			// Generar hijo actTURN_L
			nodeN0 child_turnl = current_node; 
			child_turnl.st = apply(actTURN_L, current_node.st, mapa);
			if (explored.find(child_turnl)==explored.end())
			{
				child_turnl.secuencia.push_back(actTURN_L);
				frontier.push_back(child_turnl);
			}
			// Generar hijo actTURN_R
			nodeN0 child_turnr = current_node; 
			child_turnr.st = apply(actTURN_R, current_node.st, mapa);
			if (explored.find(child_turnr)==explored.end())
			{
				child_turnr.secuencia.push_back(actTURN_R);
				frontier.push_back(child_turnr);
			}
		}

		if (!SolutionFound and !frontier.empty())
		{
			current_node = frontier.front();
			while (!frontier.empty() and explored.find(current_node)!=explored.end()){
				frontier.pop_front();
				if (!frontier.empty()) {
					current_node=frontier.front();
				}
			}
		}
	}

	if(SolutionFound){ 
		plan = current_node.secuencia;
	}

	return SolutionFound;
}

bool AnchuraJugadorYSonambulo(const stateN1 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &mapa)
{
	nodeN1 current_node;
	current_node.st = inicio;
	list<nodeN1> frontier;
	set<nodeN1> explored;
	bool SolutionFound = (current_node.st.sonambulo.f == final.f and current_node.st.sonambulo.c == final.c);
	frontier.push_back(current_node);

	while (!frontier.empty() and !SolutionFound)
	{
		frontier.pop_front();
		explored.insert(current_node);

		// Generar hijo actSONFORWARD
		nodeN1 child_forward_son = current_node;
		child_forward_son.st = apply1(actSON_FORWARD, current_node.st, mapa);
		if (child_forward_son.st.sonambulo.f == final.f and child_forward_son.st.sonambulo.c == final.c)
		{
			child_forward_son.secuencia.push_back(actSON_FORWARD); 
			current_node = child_forward_son;
			SolutionFound = true;
		}
		else if (explored.find(child_forward_son)==explored.end())
		{
			child_forward_son.secuencia.push_back(actSON_FORWARD);
			frontier.push_back(child_forward_son);
		}

		if (!SolutionFound)
		{
			// Generar hijo actSONTURN_L
			nodeN1 child_turnl_son = current_node; 
			child_turnl_son.st = apply1(actSON_TURN_SL, current_node.st, mapa);
			if (explored.find(child_turnl_son)==explored.end())
			{
				child_turnl_son.secuencia.push_back(actSON_TURN_SL);
				frontier.push_back(child_turnl_son);
			}
			// Generar hijo actSONTURN_R
			nodeN1 child_turnr_son = current_node; 
			child_turnr_son.st = apply1(actSON_TURN_SR, current_node.st, mapa);
			if (explored.find(child_turnr_son)==explored.end())
			{
				child_turnr_son.secuencia.push_back(actSON_TURN_SR);
				frontier.push_back(child_turnr_son);
			}

			//Generar hijo actFORWARD
			nodeN1 child_forward = current_node; 
			child_forward.st = apply1(actFORWARD, current_node.st, mapa);
			if (explored.find(child_forward)==explored.end())
			{
				child_forward.secuencia.push_back(actFORWARD);
				frontier.push_back(child_forward);
			}

			//Generar hijo actTURN_R
			nodeN1 child_turnr = current_node; 
			child_turnr.st = apply1(actTURN_R, current_node.st, mapa);
			if (explored.find(child_turnr)==explored.end())
			{
				child_turnr.secuencia.push_back(actTURN_R);
				frontier.push_back(child_turnr);
			}

			// Generar hijo actTURN_L
			nodeN1 child_turnl = current_node; 
			child_turnl.st = apply1(actTURN_L, current_node.st, mapa);
			if (explored.find(child_turnl)==explored.end())
			{
				child_turnl.secuencia.push_back(actTURN_L);
				frontier.push_back(child_turnl);
			}

		}

		if (!SolutionFound and !frontier.empty())
		{
			current_node = frontier.front();
			while (!frontier.empty() and explored.find(current_node)!=explored.end()){
				frontier.pop_front();
				if (!frontier.empty()) {
					current_node=frontier.front();
				}
			}
		}
	}

	if(SolutionFound){ 
		plan = current_node.secuencia;
	}

	return SolutionFound;
}

/** Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st */
void ComportamientoJugador::VisualizaPlan(const stateN0 &st, const list<Action> &plan)
{
  AnularMatriz(mapaConPlan);
  stateN0 cst = st;

  auto it = plan.begin();
  while (it != plan.end()){
    switch (*it){
      case actFORWARD:
        cst.jugador = NextCasilla(cst.jugador);
	  mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
	  break;
	case actTURN_R:
        cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 2) % 8);
	  break;
	case actTURN_L:
	  cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
	  break;
	case actSON_FORWARD:
	  cst.sonambulo = NextCasilla(cst.sonambulo);
	  mapaConPlan[cst.sonambulo.f][cst.sonambulo.c] = 2;
	  break;
	case actSON_TURN_SR:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 1) % 8);
	  break;
	case actSON_TURN_SL:
	  cst.sonambulo.brujula = (Orientacion)((cst.sonambulo.brujula + 7) % 8);
	  break;
    }
    it++;
  }
}

/** pone a cero todos los elementos de una matriz */
void AnularMatriz(vector<vector<unsigned char>> &matriz)
{
  for (int i = 0; i < matriz.size(); i++)
    for (int j = 0; j < matriz[0].size(); j++)
      matriz[i][j] = 0;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

int CosteAccionN2 (const Action &accion, const unsigned char &terreno, const stateN2 &estado)
{
	switch (accion)
	{
		case actFORWARD:
			if (terreno=='A' and !estado.bikini){
				return 100;	
			}
			else if (terreno=='B' and !estado.zapatillas){
				return 50;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 10;
			}
			else if (terreno=='B'){
				return 15;
			}
			else {
				return 1;
			}
		break;
		case actTURN_L:
			if (terreno=='A' and !estado.bikini){
				return 25;	
			}
			else if (terreno=='B' and !estado.zapatillas){
				return 5;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 5;
			}
			else {
				return 1;
			}
		break;
		case actTURN_R:
			if (terreno=='A' and !estado.bikini){
				return 25;	
			}
			else if (terreno=='B' and !estado.zapatillas){
				return 5;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 5;
			}
			else {
				return 1;
			}
		break;

	}
	return 0;
}

int CosteAccionN3 (const Action &accion, const unsigned char &terreno, const stateN3 &estado)
{
	switch (accion)
	{
		case actFORWARD:
			if (terreno=='A' and !estado.bikini){
				return 100;	
			}
			else if (terreno=='B' and !estado.zapatillas){
				return 50;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 10;
			}
			else if (terreno=='B'){
				return 15;
			}
			else {
				return 1;
			}
		break;
		case actTURN_L:
			if (terreno=='A' and !estado.bikini){
				return 25;	
			}
			else if (terreno=='B' and !estado.zapatillas){
				return 5;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 5;
			}
			else {
				return 1;
			}
		break;
		case actTURN_R:
			if (terreno=='A' and !estado.bikini){
				return 25;	
			}
			else if (terreno=='B' and !estado.zapatillas){
				return 5;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 5;
			}
			else {
				return 1;
			}
		break;
		case actSON_FORWARD:
			if (terreno=='A' and !estado.bikini_son){
				return 100;	
			}
			else if (terreno=='B' and !estado.zapatillas_son){
				return 50;
			}
			else if (terreno=='T'){
				return 2;
			}
			else if (terreno=='A'){
				return 10;
			}
			else if (terreno=='B'){
				return 15;
			}
			else {
				return 1;
			}
		break;
		case actSON_TURN_SL:
			if (terreno=='A' and !estado.bikini_son){
				return 7;	
			}
			else if (terreno=='B' and !estado.zapatillas_son){
				return 3;
			}
			else if (terreno=='A'){
				return 2;
			}
			else {
				return 1;
			}
		break;
		case actSON_TURN_SR:
			if (terreno=='A' and !estado.bikini_son){
				return 7;	
			}
			else if (terreno=='B' and !estado.zapatillas_son){
				return 3;
			}
			else if (terreno=='A'){
				return 2;
			}
			else {
				return 1;
			}
		break;

	}
	return 0;
}

int DistanciaManhattan (const ubicacion &inicio, const ubicacion &fin) 
{
	int coste =0;
	coste+=(abs(inicio.f-fin.f));
	coste+=(abs(inicio.c-fin.c));
	return coste;
}

int DistanciaChebyshev (const ubicacion &inicio, const ubicacion &fin) 
{
	int dif_filas =0;
	int dif_cols = 0;
	int coste=0;
	dif_filas+=(abs(inicio.f-fin.f));
	dif_cols+=(abs(inicio.c-fin.c));
	if (dif_filas>dif_cols) { coste = dif_filas; }
	else { coste = dif_cols; }
	return coste;
}

bool Dijkstra (const stateN2 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &matriz)
{	
	nodeN2 current_node;
	current_node.st = inicio;
	//Ponemos el coste a 0
	current_node.st.coste=0;
	//Hacemos actIDLE para que se ponga las zapatillas o el bikini, si empieza en una de esas dos casillas
	current_node.st=apply2(actIDLE, current_node.st, matriz);
	priority_queue<nodeN2, vector<nodeN2>, greater<nodeN2>> frontier{};
	set<stateN2> explored{};
	bool SolutionFound = (current_node.st.jugador.f == final.f and current_node.st.jugador.c == final.c);
	frontier.push(current_node);

	while (!frontier.empty() and !SolutionFound)
	{
		frontier.pop();
		explored.insert(current_node.st);
		// Si al meterlo en cerrados, es solución, es óptimo
		if (current_node.st.jugador.f==final.f and current_node.st.jugador.c==final.c)
		{
			SolutionFound=true;
		}
		if (!SolutionFound){
		// Generar hijo actFORWARD
			nodeN2 child_forward = current_node;
			child_forward.st = apply2(actFORWARD, current_node.st, matriz);
			/*if (child_forward.st.jugador.f == final.f and child_forward.st.jugador.c == final.c)
			{
				child_forward.secuencia.push_back(actFORWARD); 

				// NO ES SOLUCIÓN HASTA QUE EL NODO NO ENTRE EN CERRADOS
				current_node = child_forward;
				SolutionFound = true;

				//child_forward.st.coste+=(CosteAccion(actFORWARD, matriz[child_forward.st.jugador.f][child_forward.st.jugador.c], child_forward.st))+(DistanciaManhattan(child_forward.st.jugador, final));
				//frontier.push(child_forward);

			}*/
			if (explored.find(child_forward.st)==explored.end())
			{
				child_forward.secuencia.push_back(actFORWARD);
				child_forward.st.coste+=(CosteAccionN2(actFORWARD, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				frontier.push(child_forward);
			}

			//if (!SolutionFound)
			//{		
			// Generar hijo actTURN_L
			nodeN2 child_turnl = current_node; 
			child_turnl.st = apply2(actTURN_L, current_node.st, matriz);
			if (explored.find(child_turnl.st)==explored.end())
			{
				child_turnl.secuencia.push_back(actTURN_L);
				child_turnl.st.coste+=(CosteAccionN2(actTURN_L, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				frontier.push(child_turnl);
			}
			// Generar hijo actTURN_R
			nodeN2 child_turnr = current_node; 
			child_turnr.st = apply2(actTURN_R, current_node.st, matriz);
			if (explored.find(child_turnr.st)==explored.end())
			{
				child_turnr.secuencia.push_back(actTURN_R);
				child_turnr.st.coste+=(CosteAccionN2(actTURN_R, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				frontier.push(child_turnr);
			}
		}

		if (!SolutionFound and !frontier.empty())
		{
			current_node = frontier.top();
			while (!frontier.empty() and explored.find(current_node.st)!=explored.end()){
				frontier.pop();
				if (!frontier.empty()) {
					current_node=frontier.top();
				}
			}
		}
	}

	if(SolutionFound){ 
		plan = current_node.secuencia;
	}

	return SolutionFound;

}

bool AEstrella2 (const stateN3 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &matriz)
{	
	nodeN3 current_node;
	current_node.st = inicio;
	//Ponemos el coste a 0
	current_node.st.coste=0;
	current_node.st.heuristica=DistanciaChebyshev(inicio.sonambulo, final);
	//Hacemos actIDLE para que se ponga las zapatillas o el bikini, si empieza en una de esas dos casillas
	current_node.st=apply3(actIDLE, current_node.st, matriz);
	priority_queue<nodeN3, vector<nodeN3>, greater<nodeN3>> frontier{};
	set<stateN3> explored{};
	bool SolutionFound = (current_node.st.sonambulo.f == final.f and current_node.st.sonambulo.c == final.c);
	frontier.push(current_node);

	while (!frontier.empty() and !SolutionFound)
	{
		frontier.pop();
		explored.insert(current_node.st);
		// Si al meterlo en cerrados, es solución, es óptimo
		if (current_node.st.sonambulo.f==final.f and current_node.st.sonambulo.c==final.c)
		{
			SolutionFound=true;
		}
		if (!SolutionFound){
			// Generar hijo actSON_FORWARD
			nodeN3 child_forward_son = current_node;
			child_forward_son.st=apply4(actSON_FORWARD, current_node.st, matriz);

			if (explored.find(child_forward_son.st)==explored.end())
			{
				child_forward_son.secuencia.push_back(actSON_FORWARD);
				// NO MIRO EN EL COSTE LAS ZAPATILLAS DEL SONAMBULO CREO!!

				if (matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c]!='?'){
					child_forward_son.st.coste+=(CosteAccionN3(actSON_FORWARD, matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c], current_node.st));
				}
				child_forward_son.st.coste+=1;
				child_forward_son.st.heuristica=DistanciaChebyshev(child_forward_son.st.sonambulo, final);
				frontier.push(child_forward_son);
			}
			// Generar hijo actSON_TURNSL
			nodeN3 child_left_son = current_node;
			child_left_son.st=apply4(actSON_TURN_SL, current_node.st, matriz);

			if (explored.find(child_left_son.st)==explored.end())
			{
				child_left_son.secuencia.push_back(actSON_TURN_SL);
				if (matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c]!='?'){
					child_left_son.st.coste+=(CosteAccionN3(actSON_TURN_SL, matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c], current_node.st));
				}
				child_left_son.st.coste+=1;
				child_left_son.st.heuristica=DistanciaChebyshev(child_left_son.st.sonambulo,final);
				frontier.push(child_left_son);
			}
			// Generar hijo actSON_TURNSR
			nodeN3 child_right_son = current_node;
			child_right_son.st=apply4(actSON_TURN_SR, current_node.st, matriz);

			if (explored.find(child_right_son.st)==explored.end())
			{
				child_right_son.secuencia.push_back(actSON_TURN_SR);
				if (matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c]!='?'){
					child_right_son.st.coste+=(CosteAccionN3(actSON_TURN_SR, matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c], current_node.st));
				}
				child_right_son.st.coste+=1;
				child_right_son.st.heuristica=DistanciaChebyshev(child_right_son.st.sonambulo,final);
				frontier.push(child_right_son);
			}

			// Generar hijo actFORWARD
			nodeN3 child_forward = current_node;
			child_forward.st = apply4(actFORWARD, current_node.st, matriz);

			if (explored.find(child_forward.st)==explored.end())
			{
				child_forward.secuencia.push_back(actFORWARD);
				if (matriz[current_node.st.jugador.f][current_node.st.jugador.c]!='?'){
					child_forward.st.coste+=(CosteAccionN3(actFORWARD, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				}
				child_forward.st.coste+=1;
				child_forward.st.heuristica=DistanciaChebyshev(child_forward.st.sonambulo, final);
				frontier.push(child_forward);
			}
			// Generar hijo actTURN_L
			nodeN3 child_turnl = current_node; 
			child_turnl.st = apply4(actTURN_L, current_node.st, matriz);
			if (explored.find(child_turnl.st)==explored.end())
			{
				child_turnl.secuencia.push_back(actTURN_L);
				if (matriz[current_node.st.jugador.f][current_node.st.jugador.c]!='?'){
					child_turnl.st.coste+=(CosteAccionN3(actTURN_L, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				}
				child_turnl.st.coste+=1;
				child_turnl.st.heuristica=DistanciaChebyshev(child_turnl.st.sonambulo,final);
				frontier.push(child_turnl);
			}
			// Generar hijo actTURN_R
			nodeN3 child_turnr = current_node; 
			child_turnr.st = apply4(actTURN_R, current_node.st, matriz);
			if (explored.find(child_turnr.st)==explored.end())
			{
				child_turnr.secuencia.push_back(actTURN_R);
				if (matriz[current_node.st.jugador.f][current_node.st.jugador.c]!='?'){
					child_turnr.st.coste+=(CosteAccionN3(actTURN_R, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				}
				child_turnr.st.coste+=1;
				child_turnr.st.heuristica=DistanciaChebyshev(child_turnr.st.sonambulo,final);
				frontier.push(child_turnr);
			}
		}

		if (!SolutionFound and !frontier.empty())
		{
			current_node = frontier.top();
			while (!frontier.empty() and explored.find(current_node.st)!=explored.end()){
				frontier.pop();
				if (!frontier.empty()) {
					current_node=frontier.top();
				}
			}
		}
	}

	if(SolutionFound){ 
		plan = current_node.secuencia;
	}

	return SolutionFound;

}

bool AEstrella (const stateN3 &inicio, const ubicacion &final, list<Action> & plan, const vector<vector<unsigned char>> &matriz)
{	
	nodeN3 current_node;
	current_node.st = inicio;
	//Ponemos el coste a 0
	current_node.st.coste=0;
	current_node.st.heuristica=DistanciaChebyshev(inicio.sonambulo, final);
	//Hacemos actIDLE para que se ponga las zapatillas o el bikini, si empieza en una de esas dos casillas
	current_node.st=apply3(actIDLE, current_node.st, matriz);
	priority_queue<nodeN3, vector<nodeN3>, greater<nodeN3>> frontier{};
	set<stateN3> explored{};
	bool SolutionFound = (current_node.st.sonambulo.f == final.f and current_node.st.sonambulo.c == final.c);
	frontier.push(current_node);

	while (!frontier.empty() and !SolutionFound)
	{
		frontier.pop();
		explored.insert(current_node.st);
		// Si al meterlo en cerrados, es solución, es óptimo
		if (current_node.st.sonambulo.f==final.f and current_node.st.sonambulo.c==final.c)
		{
			SolutionFound=true;
		}
		if (!SolutionFound){
			// Generar hijo actSON_FORWARD
			nodeN3 child_forward_son = current_node;
			child_forward_son.st=apply3(actSON_FORWARD, current_node.st, matriz);

			if (explored.find(child_forward_son.st)==explored.end())
			{
				child_forward_son.secuencia.push_back(actSON_FORWARD);
				// NO MIRO EN EL COSTE LAS ZAPATILLAS DEL SONAMBULO CREO!!

				child_forward_son.st.coste+=(CosteAccionN3(actSON_FORWARD, matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c], current_node.st));
				child_forward_son.st.heuristica=DistanciaChebyshev(child_forward_son.st.sonambulo, final);
				frontier.push(child_forward_son);
			}
			// Generar hijo actSON_TURNSL
			nodeN3 child_left_son = current_node;
			child_left_son.st=apply3(actSON_TURN_SL, current_node.st, matriz);

			if (explored.find(child_left_son.st)==explored.end())
			{
				child_left_son.secuencia.push_back(actSON_TURN_SL);
				child_left_son.st.coste+=(CosteAccionN3(actSON_TURN_SL, matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c], current_node.st));
				child_left_son.st.heuristica=DistanciaChebyshev(child_left_son.st.sonambulo,final);
				frontier.push(child_left_son);
			}
			// Generar hijo actSON_TURNSR
			nodeN3 child_right_son = current_node;
			child_right_son.st=apply3(actSON_TURN_SR, current_node.st, matriz);

			if (explored.find(child_right_son.st)==explored.end())
			{
				child_right_son.secuencia.push_back(actSON_TURN_SR);
				child_right_son.st.coste+=(CosteAccionN3(actSON_TURN_SR, matriz[current_node.st.sonambulo.f][current_node.st.sonambulo.c], current_node.st));
				child_right_son.st.heuristica=DistanciaChebyshev(child_right_son.st.sonambulo,final);
				frontier.push(child_right_son);
			}

			// Generar hijo actFORWARD
			nodeN3 child_forward = current_node;
			child_forward.st = apply3(actFORWARD, current_node.st, matriz);

			if (explored.find(child_forward.st)==explored.end())
			{
				child_forward.secuencia.push_back(actFORWARD);
				child_forward.st.coste+=(CosteAccionN3(actFORWARD, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				child_forward.st.heuristica=DistanciaChebyshev(child_forward.st.sonambulo, final);
				frontier.push(child_forward);
			}
			// Generar hijo actTURN_L
			nodeN3 child_turnl = current_node; 
			child_turnl.st = apply3(actTURN_L, current_node.st, matriz);
			if (explored.find(child_turnl.st)==explored.end())
			{
				child_turnl.secuencia.push_back(actTURN_L);
				child_turnl.st.coste+=(CosteAccionN3(actTURN_L, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				child_turnl.st.heuristica=DistanciaChebyshev(child_turnl.st.sonambulo,final);
				frontier.push(child_turnl);
			}
			// Generar hijo actTURN_R
			nodeN3 child_turnr = current_node; 
			child_turnr.st = apply3(actTURN_R, current_node.st, matriz);
			if (explored.find(child_turnr.st)==explored.end())
			{
				child_turnr.secuencia.push_back(actTURN_R);
				child_turnr.st.coste+=(CosteAccionN3(actTURN_R, matriz[current_node.st.jugador.f][current_node.st.jugador.c], current_node.st));
				child_turnr.st.heuristica=DistanciaChebyshev(child_turnr.st.sonambulo,final);
				frontier.push(child_turnr);
			}
		}

		if (!SolutionFound and !frontier.empty())
		{
			current_node = frontier.top();
			while (!frontier.empty() and explored.find(current_node.st)!=explored.end()){
				frontier.pop();
				if (!frontier.empty()) {
					current_node=frontier.top();
				}
			}
		}
	}

	if(SolutionFound){ 
		plan = current_node.secuencia;
	}

	return SolutionFound;

}

void PintarPrecipiciosBordes(const stateN3 &st, vector<vector<unsigned char>> &matriz){
    for (int i=0; i<3; i++){
      for (int j=0; j<matriz.size(); j++){
        matriz[i][j]='P';
      }
    }
    for (int i=0; i<matriz.size(); i++) {
      for (int j=0; j<3; j++){
        matriz[i][j]='P';
      }
    }
    for (int i=matriz.size()-3; i<matriz.size(); i++){
      for (int j=0; j<matriz.size(); j++){
        matriz[i][j]='P';
      }
    }
    for (int i=0; i<matriz.size(); i++){
      for (int j=matriz.size()-3; j<matriz.size(); j++){
        matriz[i][j]='P';
      }
    }
  }