#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "equipo.h"
#include "jugador.h"
#include "torneo.h"
#include "partido.h"

void Partido::setCodigo_toneo(int cod){codigo_toneo=cod;}
void Partido::setEquipo_local(int equipo){equipo_local=equipo;}
void Partido::setEquipo_visitante(int equipo){equipo_visitante=equipo;}
void Partido::setGoles_local(int goles){goles_local=goles;}
void Partido::setGoles_visitante(int goles){goles_visitante=goles;}
void Partido::setEquipo_ganador(int equipo){equipo_ganador=equipo;}
void Partido::setInstancia_torneo(int instancia){instancia_torneo=instancia;}
void Partido::setNro_partido(int partido){nro_partido=partido;}
void Partido::setJugado(){jugado=true;}
int Partido::getCodigo_toneo(){return codigo_toneo;}
int Partido::getEquipo_local(){return equipo_local;}
int Partido::getEquipo_visitante(){return equipo_visitante;}
int Partido::getGoles_local(){return goles_local;}
int Partido::getGoles_visitante(){return goles_visitante;}
int Partido::getEquipo_ganador(){return equipo_ganador;}
int Partido::getInstancia_torneo(){return instancia_torneo;}
int Partido::getNro_partido(){return nro_partido;}
bool  Partido::getJugado(){return jugado;}

void Partido::ingresarCodigo_torneo(){    //deberia ingresar nombre del torneo para ingresar al ingresar y ese es lo que recibiria la funcion
    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    Torneo tor;
    fread(&tor, sizeof(Torneo), 1, pArchivo);
    fclose(pArchivo);

    codigo_toneo=tor.getCodigo_torneo();
}

Partido::Partido(){
    codigo_toneo=0;
    equipo_local=0;
    equipo_visitante=0;
    goles_local=0;
    goles_visitante=0;
    equipo_ganador=0;
    instancia_torneo=0;
    nro_partido=0;
    jugado=false;
}

Partido::Partido(int cant_equipos){
    codigo_toneo=0;
    equipo_local=0;
    equipo_visitante=0;
    goles_local=0;
    goles_visitante=0;
    equipo_ganador=0;
    instancia_torneo=0;
    nro_partido=0;
    jugado=false;

}

bool Partido::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Partido),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

bool Partido::escribrirEnDisco(int pos){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb+");
    if(pArchivo==NULL)return false;
    fseek(pArchivo, pos * sizeof(Partido), SEEK_SET);
    guardo = fwrite(this, sizeof(Partido), 1, pArchivo);
    fclose(pArchivo);
    return guardo;
}

void Partido::aumentar_partidos_jugados(int numeroPartido){
    nro_partido=numeroPartido+1;
}

void cargar_partido_8(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo){

    int cant,i, posicion_partido,posicion_ganador;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
            //cuartos///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==0){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,1);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,5);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==1){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,2);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,5);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==2){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,3);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,6);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==3){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,4);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,6);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //semi///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==4){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,5);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,7);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //semi///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==5){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,6);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,7);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //final///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==6){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,7);
        }

    }
            vec[posicion_partido].setEquipo_local(numeroEquipo1);
            vec[posicion_partido].setEquipo_visitante(numeroEquipo2);
            vec[posicion_partido].setGoles_local(golesEquipo1);
            vec[posicion_partido].setGoles_visitante(golesEquipo2);
            vec[posicion_partido].setEquipo_ganador(equipo_ganador);
            vec[posicion_partido].setJugado();
            vec[posicion_partido].escribrirEnDisco(posicion_partido);

            vec[posicion_ganador].escribrirEnDisco(posicion_ganador);
    delete []vec;
}

void cargar_partido_16(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo){

    int cant,i, posicion_partido,posicion_ganador;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
            //octavos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==0){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,1);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,9);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==1){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,2);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,9);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==2){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,3);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,10);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==3){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,4);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,10);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }

            //octavos5///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==4){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,5);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,11);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos6///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==5){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,6);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,11);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos7///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==6){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,7);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,12);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos8///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==7){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,8);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,12);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==8){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,9);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,13);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==9){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,10);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,13);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==10){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,11);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,14);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==11){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,12);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,14);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //semi1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==12){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,13);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,15);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //semi2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==13){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,14);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,15);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //final///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==14){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,15);
        }

    }
            vec[posicion_partido].setEquipo_local(numeroEquipo1);
            vec[posicion_partido].setEquipo_visitante(numeroEquipo2);
            vec[posicion_partido].setGoles_local(golesEquipo1);
            vec[posicion_partido].setGoles_visitante(golesEquipo2);
            vec[posicion_partido].setEquipo_ganador(equipo_ganador);
            vec[posicion_partido].setJugado();
            vec[posicion_partido].escribrirEnDisco(posicion_partido);

            vec[posicion_ganador].escribrirEnDisco(posicion_ganador);
    delete []vec;
}

void cargar_partido_32(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo){
    int cant,i, posicion_partido,posicion_ganador;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
            //16avos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==0){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,1);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,17);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==1){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,2);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,17);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==2){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,3);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,18);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==3){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,4);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,18);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos5///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==4){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,5);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,19);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos6///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==5){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,6);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,19);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos7///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==6){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,7);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,20);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos8///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==7){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,8);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,20);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos9///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==8){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,9);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,21);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos10///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==9){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,10);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,21);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos11///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==10){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,11);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,22);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos12///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==11){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,12);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,22);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos13///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==12){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,13);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,23);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos14///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==13){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,14);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,23);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos15///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==14){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,15);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,24);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos16///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==15){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,16);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,24);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==16){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,17);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,25);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==17){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,18);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,25);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==18){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,19);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,26);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==19){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,20);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,26);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos5///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==20){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,21);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,27);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos6///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==21){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,22);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,27);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos7///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==22){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,23);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,28);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos8///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==23){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,24);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,28);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==24){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,25);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,29);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==25){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,26);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,29);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==26){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,27);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,30);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==27){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,28);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,30);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //semi1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==28){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,29);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,31);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //semi2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==29){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,30);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,31);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //final///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==30){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,31);
        }

    }
            vec[posicion_partido].setEquipo_local(numeroEquipo1);
            vec[posicion_partido].setEquipo_visitante(numeroEquipo2);
            vec[posicion_partido].setGoles_local(golesEquipo1);
            vec[posicion_partido].setGoles_visitante(golesEquipo2);
            vec[posicion_partido].setEquipo_ganador(equipo_ganador);
            vec[posicion_partido].setJugado();
            vec[posicion_partido].escribrirEnDisco(posicion_partido);

            vec[posicion_ganador].escribrirEnDisco(posicion_ganador);
    delete []vec;
}

void cargar_partido_64(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo){
    int cant,i, posicion_partido,posicion_ganador;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
            //32avos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==0){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,1);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,33);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==1){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,2);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,33);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==2){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,3);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,34);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==3){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,4);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,34);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos5///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==4){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,5);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,35);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos6///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==5){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,6);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,35);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos7///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==6){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,7);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,36);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos8///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==7){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,8);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,36);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos9///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==8){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,9);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,37);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos10///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==9){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,10);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,37);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos11///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==10){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,11);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,38);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos12///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==11){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,12);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,38);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos13///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==12){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,13);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,39);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos14///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==13){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,14);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,39);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos15///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==14){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,15);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,40);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos16///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==15){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,16);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,40);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos17///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==16){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,17);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,41);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos18///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==17){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,18);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,41);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos19///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==18){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,19);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,42);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos20///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==19){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,20);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,42);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos21///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==20){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,21);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,43);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos22///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==21){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,22);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,43);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos23///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==22){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,23);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,44);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos24///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==23){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,24);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,44);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos25///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==24){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,25);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,45);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos26///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==25){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,26);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,45);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos27///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==26){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,27);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,46);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos28///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==27){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,28);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,46);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos29///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==28){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,29);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,47);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos30///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==29){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,30);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,47);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //32avos31///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==30){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,31);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,48);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //32avos32///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==31){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,32);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,48);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==32){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,33);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,49);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==33){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,34);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,49);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==34){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,35);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,50);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==35){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,36);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,50);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos5///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==36){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,37);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,51);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos6///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==37){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,38);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,51);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos7///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==38){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,39);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,52);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos8///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==39){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,40);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,52);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos9///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==40){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,41);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,53);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos10///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==41){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,42);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,53);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos11///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==42){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,43);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,54);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos12///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==43){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,44);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,54);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos13///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==44){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,45);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,55);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos14///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==45){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,46);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,55);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //16avos15///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==46){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,47);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,56);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //16avos16///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==47){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,48);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,56);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==48){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,49);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,57);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==49){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,50);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,57);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==50){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,51);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,58);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==51){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,52);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,58);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos5///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==52){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,53);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,59);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos6///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==53){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,54);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,59);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //octavos7///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==54){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,55);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,60);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //octavos8///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==55){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,56);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,60);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==56){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,57);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,61);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==57){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,58);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,61);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //cuartos3///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==58){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,59);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,62);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //cuartos4///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==59){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,60);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,62);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //semi1///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==60){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,61);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,63);
            vec[posicion_ganador].setEquipo_local(equipo_ganador);
        }
            //semi2///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==61){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,62);
            posicion_ganador=buscar_posicion_nropartido_prox_fase(vec,cant,63);
            vec[posicion_ganador].setEquipo_visitante(equipo_ganador);
        }
            //final///////////////////////////////////////////////////////////////////////////
        if(vec[i].getCodigo_toneo()==codigo_torneo&&partidos_jugados==62){
            posicion_partido=buscar_posicion_nropartido_jugado(vec,cant,63);
        }

    }
            vec[posicion_partido].setEquipo_local(numeroEquipo1);
            vec[posicion_partido].setEquipo_visitante(numeroEquipo2);
            vec[posicion_partido].setGoles_local(golesEquipo1);
            vec[posicion_partido].setGoles_visitante(golesEquipo2);
            vec[posicion_partido].setEquipo_ganador(equipo_ganador);
            vec[posicion_partido].setJugado();
            vec[posicion_partido].escribrirEnDisco(posicion_partido);

            vec[posicion_ganador].escribrirEnDisco(posicion_ganador);
    delete []vec;
}


int cantidad_partidos(){
    FILE *p = fopen(FILE_PARTIDOS, "rb");
    if (p == NULL){
        return 1;
    }
    int bytes, cant;
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    fclose(p);
    cant = bytes / sizeof(Partido);
    return cant;
}

void listar_partidos(){
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO PARTIDOS", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }

    int a,b,c;

    Partido par;
        cout << left;
        cout << setw(11) << "Nombre torneo" << setw(20) << "|Equipo Local"<< setw(10)<< "|Resultado" << setw(18) << "|Equipo Visitante"<< setw(18) << "|Instancia Torneo"<< setw(17) << "|Equipo Ganador";
        cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(11);
    while(fread(&par, sizeof (Partido), 1, pArchivo)==1){
        if(par.getEquipo_ganador()!=0){
      cout << left;
        cout << setw(14);
        cout << par.getCodigo_toneo();
        cout << setw(20) ;
        a=par.getEquipo_local();
        buscar_nombre_equipo(a);
        cout << setw(1) ;
        cout << par.getGoles_local();
        cout <<setw(1);
        cout<<"-";
        cout <<setw(9);
        cout << par.getGoles_visitante();
        cout << setw(17);
        buscar_nombre_equipo(par.getEquipo_visitante());
        cout << setw(18) ;
        mostrar_fase(par.getInstancia_torneo());
        cout << setw(17) ;
        c=par.getEquipo_ganador();
        buscar_nombre_equipo(c);
        cout<<endl;

    }}
    anykey();
    fclose(pArchivo);
}

void buscar_nombre_equipo(int a){

    char nombre[30];
    Equipo reg;
	FILE* f;
	f = fopen(FILE_EQUIPOS, "rb");
	if (f == NULL) {
        cout<<"ERROR ARCHIVO EQUIPOS" << endl;
	}
	while (fread(&reg, sizeof(Equipo), 1, f)) {

            if(a==reg.getNro_equipo()){

                strcpy(nombre, reg.getNombre_equipo());
                cout<< nombre;

            }
    }

    fclose(f);
}

void generar_registros_partidos(int cant_equipos, int partidos_jugados){
    for(int i=0;i<cant_equipos-1;i++){
        Partido par(cant_equipos);
        FILE* pArchivo;
        pArchivo=fopen(FILE_PARTIDOS, "ab");
        if(pArchivo==NULL){
            msj("ERROR ARCHIVO PARTIDOS", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
            return;
        }

        par.ingresarCodigo_torneo();
        switch (cant_equipos){
            case 64:
                if(i>=0 && i<=31){
                    par.setInstancia_torneo(32);
                }
                if(i>=32 && i<=47){
                    par.setInstancia_torneo(16);
                }
                if(i>=48 && i<=55){
                    par.setInstancia_torneo(8);
                }
                if(i>=56 && i<=59){
                    par.setInstancia_torneo(4);
                }
                if(i>=60 && i<=61){
                    par.setInstancia_torneo(2);
                }
                if(i==62){
                    par.setInstancia_torneo(1);
                }
            break;
            case 32:
                if(i>=0 && i<=15){
                    par.setInstancia_torneo(16);
                }
                if(i>=16 && i<=23){
                    par.setInstancia_torneo(8);
                }
                if(i>=24 && i<=27){
                    par.setInstancia_torneo(4);
                }
                if(i>=28 && i<=29){
                    par.setInstancia_torneo(2);
                }
                if(i==30){
                    par.setInstancia_torneo(1);
                }
            break;
            case 16:
                if(i>=0 && i<=7){
                    par.setInstancia_torneo(8);
                }
                if(i>=8 && i<=11){
                    par.setInstancia_torneo(4);
                }
                if(i>=12 && i<=13){
                    par.setInstancia_torneo(2);
                }
                if(i==14){
                    par.setInstancia_torneo(1);
                }
            break;
            case 8:
                if(i>=0 && i<=3){
                    par.setInstancia_torneo(4);
                }
                if(i>=4 && i<=5){
                    par.setInstancia_torneo(2);
                }
                if(i==6){
                    par.setInstancia_torneo(1);
                }
            break;
        }

        par.aumentar_partidos_jugados(i);

        par.guardarEnDisco();

        fclose(pArchivo);
    }
}

int buscar_posicion_nropartido_jugado(Partido *vec, int tam,int nro_partido){
    int posicion,i;

    for(i=0;i<tam;i++){
        if(vec[i].getNro_partido()== nro_partido){
            posicion=i;
        }
    }
return posicion;
}

int buscar_posicion_nropartido_prox_fase(Partido *vec, int tam,int nro_partido){
    int posicion,i;

    for(i=0;i<tam;i++){
        if(vec[i].getNro_partido()== nro_partido){
            posicion=i;
        }
    }
return posicion;
}

void resultados_por_fase(){

    int opcion;
        cout << "    1. FASE DE TREINTA Y DOS AVOS" << endl;
        cout << "    2. FASE DE DIECISEIS AVOS" << endl;
        cout << "    3. FASE DE OCTAVOS" << endl;
        cout << "    4. FASE DE CUARTOS" << endl;
        cout << "    5. FASE DE SEMIFINALES" << endl;
        cout << "    6. FASE DE FINALES" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        int instancia;

      switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                if(informar_tipoTorneo()<64){
                cout<< "El torneo seleccionado no posee esta fase."<<endl;
                }
                else{mostrar_resultados(1,32);}

                anykey();

                break;
            case 2:

                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                instancia=informar_tipoTorneo();

                if(instancia==64){
                   mostrar_resultados(33,48);
                }
                else if(instancia==32){
                    mostrar_resultados(1, 16);
                }

                else if(instancia==16){
                    cout<< "El torneo seleccionado no posee esta fase."<<endl;

                }
                anykey();


                break;
            case 3:
                 cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);
                instancia=informar_tipoTorneo();

                if(instancia==64){
                   mostrar_resultados(49,56);
                }
                else if(instancia==32){
                    mostrar_resultados(17,24);
                }

                else if(instancia==16){
                     mostrar_resultados(1,8);

                }

                else if(instancia==8){
                    cout<< "El torneo seleccionado no posee esta fase."<<endl;
                }
                anykey();

                break;
            case 4:
              cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);
                   instancia=informar_tipoTorneo();

                if(instancia==64){
                   mostrar_resultados(57,61);
                }
                else if(instancia==32){
                    mostrar_resultados(25,28);
                }

                else if(instancia==16){
                     mostrar_resultados(9,12);

                }

                else if(instancia==8){
                    mostrar_resultados(1,4);
                }


                anykey();

                break;
            case 5:
                 cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                 instancia=informar_tipoTorneo();

                if(instancia==64){
                   mostrar_resultados(61,62);
                }
                else if(instancia==32){
                    mostrar_resultados(29,30);
                }

                else if(instancia==16){
                     mostrar_resultados(13,14);

                }

                else if(instancia==8){
                    mostrar_resultados(5,6);
                }


                anykey();


                break;
            case 6:

                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                   instancia=informar_tipoTorneo();

                if(instancia==64){
                   mostrar_resultados(0, 63);
                }
                else if(instancia==32){
                    mostrar_resultados(0,31);
                }

                else if(instancia==16){
                     mostrar_resultados(0,15);

                }

                else if(instancia==8){
                    mostrar_resultados(0,7);
                }

                anykey();

                break;
            case 0: return;
            break;

    }

return;


}

void resultados_por_equipo(){

    int a,b,c;
    bool opcion;

    do{
    opcion=true;
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO PARTIDOS", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    cls();

    Partido par;

    int nro_equipo;;

    int nro=0;



    cout<<"Estos son los equipos en competencia. Por favor, ingrese el Numero de equipo cuyos resultados desea observar."<<endl;;
    listar_equipos_del_torneo();
    cout<<endl;
    cin>>nro_equipo;
    cout<<endl;
    cls();

        cout << left;
        cout << setw(11) << "Nombre torneo" << setw(20) << "|Equipo Local"<< setw(10)<< "|Resultado" << setw(18) << "|Equipo Visitante"<< setw(18) << "|Instancia Torneo"<< setw(17) << "|Equipo Ganador";
        cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(11);


     while(fread(&par, sizeof (Partido), 1, pArchivo)==1){
        if(nro_equipo == par.getEquipo_local() || nro_equipo == par.getEquipo_visitante()) {
        if(par.getEquipo_ganador()!=0){
        cout << left;
        cout << setw(14);
        cout << par.getCodigo_toneo();
        cout << setw(20) ;
        a=par.getEquipo_local();
        buscar_nombre_equipo(a);
        cout << setw(1) ;
        cout << par.getGoles_local();
        cout <<setw(1);
        cout<<"-";
        cout <<setw(9);
        cout << par.getGoles_visitante();
        cout << setw(17);
        buscar_nombre_equipo(par.getEquipo_visitante());
        cout << setw(18) ;
        mostrar_fase(par.getInstancia_torneo());
        cout << setw(17) ;
        c=par.getEquipo_ganador();
        buscar_nombre_equipo(c);
        nro++;
        cout<<endl;
        }
        }
        }

        anykey();

     fclose(pArchivo);
     char asis;
     if(nro==0){
        cls();
        cout<<"    El equipo no existe o aún no ha disputado ningun encuentro."<<endl;
        cout<<"    ¿Desea volver a ingresarlo?(S/N)";
        cin>>asis;

           while(asis!='S' && asis!='s' && asis!='N' && asis!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>asis;
            cout<<endl;
            }


            if(asis=='s' || asis=='S'){
               opcion=false;
            }

            }
            else{
              return;
            }

     } while(opcion==false);

     return;


}

void mostrar_resultados(int nro_partido_a, int nro_partido_b){
FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO PARTIDOS", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }

    int a,b,c;

    Partido par;
        cout << left;
        cout << setw(11) << "Nombre torneo" << setw(20) << "|Equipo Local"<< setw(10)<< "|Resultado" << setw(18) << "|Equipo Visitante"<< setw(18) << "|Instancia Torneo"<< setw(17) << "|Equipo Ganador";
        cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(11);

    while(fread(&par, sizeof (Partido), 1, pArchivo)==1){
        if(par.getNro_partido()>=nro_partido_a && par.getNro_partido()<=nro_partido_b && par.getJugado()==true){
               cout << left;
        cout << setw(14);
        cout << par.getCodigo_toneo();
        cout << setw(20) ;
        a=par.getEquipo_local();
        buscar_nombre_equipo(a);
        cout << setw(1) ;
        cout << par.getGoles_local();
        cout <<setw(1);
        cout<<"-";
        cout <<setw(9);
        cout << par.getGoles_visitante();
        cout << setw(17);
        buscar_nombre_equipo(par.getEquipo_visitante());
        cout << setw(18) ;
        mostrar_fase(par.getInstancia_torneo());
        cout << setw(17) ;
        c=par.getEquipo_ganador();
        buscar_nombre_equipo(c);
        cout<<endl;

    }}
    anykey();
    fclose(pArchivo);

}

void mostrar_fase(int instancia){

     switch(instancia){
        case 1:
            cout<< "Final";
            break;
        case 2:
            cout<< "Semifinal";
            break;
        case 4:
            cout<< "Cuartos de final";
            break;
        case 8:
            cout<< "Octavos de final";
            break;
        case 16:
            cout<< "Dieciseisavos de final";
            break;
        case 32:
            cout<< "Treintaidosavos de final";
            break;}

  return;

}
