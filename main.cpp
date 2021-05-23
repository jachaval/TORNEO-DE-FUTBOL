#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
using namespace std;
#include "menu.h"
#include "rlutil.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"
#include "partido.h"
#include "equipo.h"


int main(){
    setlocale(LC_ALL, "spanish");

/*
    char nombre[30];
    int cant_jugadores,n;
    bool grabo;
    cout<<"    CARGAR EQUIPO Y JUGADORES"<<endl<<endl;
    Equipo eq;
    n=contar_equiposCargados();
    eq.setNro_equipo(n);
    cin.ignore();
    cout<<"    Ingrese nombre: ";
    cin.getline(nombre,25);

    eq.setNombre_equipo(nombre);
    if(!eq.guardarEnDisco()){
        cout<<"    NO SE HA PODIDO GUARDAR"<<endl;
        return false;
    }

*/

/*

    FILE* p;
    p=fopen(FILE_TORNEOS, "rb");
    if(p==NULL){
        cout<<" ERROR DE ARCHIVO TORNEO";
        anykey();
    }
    Torneo reg;
    cout << left;
    cout << setw(11) << "Tipo Torneo" << setw(17) << "|Cod. Torneo" << setw(18) << "|Instancia" << setw(13) << "|Partidos Jugados" << setw(17) << "|Torneo Activo";
    cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;

    while(fread(&reg, sizeof (Torneo),1,p)){
        reg.mostrar();


    }

    fclose(p);

    anykey();

    FILE* par;
    par=fopen(FILE_PARTIDOS, "rb");
    if(p==NULL){
        cout<<" ERROR DE ARCHIVO PARTIDOS";
        anykey();
    }
    Partido pa;
    cout << left;
    cout << setw(12) << "Cod. Torneo" << setw(14) << "|Equipo Local" << setw(18) << "|Equipo Visitante" << setw(13) << "|Goles Local" << setw(17) << "|Goles Visitante"<< setw(13) << "|Equipo Ganador"<< setw(13) << "|Instancia"<< setw(13) << "|Nro Partido"<< setw(13) << "|Jugado"<<endl;
    cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;

    while(fread(&pa, sizeof (Partido),1,par)){
    cout << left;
    cout << setw(13);
    cout << pa.getCodigo_toneo();
    cout << setw(14) ;
    cout << pa.getEquipo_local();
    cout << setw(18) ;
    cout << pa.getEquipo_visitante();
    cout << setw(13) ;
    cout << pa.getGoles_local();
    cout << setw(17) ;
    cout << pa.getGoles_visitante();
    cout << setw(15) ;
    cout << pa.getEquipo_ganador();
    cout << setw(13) ;
    cout << pa.getInstancia_torneo();
    cout << setw(11) ;
    cout << pa.getNro_partido();
    cout << setw(13) ;
    cout << pa.getJugado();
    cout << setw(13) ;
    cout << endl;
    }

    fclose(par);
    anykey();
*/

/*
    int cant,i, contador=0;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *pArchivo;
    pArchivo = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, pArchivo);
    fclose(pArchivo);

    if(cant==63){

        for (i=0 ;i<=31 ;i++ ){
            vec[i].setEquipo_local((2*i)+1);
            vec[i].setEquipo_visitante((i*2)+2);
            vec[i].escribrirEnDisco(i);
        }
    }
    if(cant==31){

        for (i=0 ;i<=15 ;i++ ){
            vec[i].setEquipo_local((2*i)+1);
            vec[i].setEquipo_visitante((i*2)+2);
            vec[i].escribrirEnDisco(i);
        }
    }
    if(cant==15){

        for (i=0 ;i<=7 ;i++ ){
            vec[i].setEquipo_local((2*i)+1);
            vec[i].setEquipo_visitante((i*2)+2);
            vec[i].escribrirEnDisco(i);
        }
    }
    if(cant==7){

        for (i=0 ;i<=3 ;i++ ){
            vec[i].setEquipo_local((2*i)+1);
            vec[i].setEquipo_visitante((i*2)+2);
            vec[i].escribrirEnDisco(i);
        }
    }
    delete []vec;
    anykey();
*/
    menu_principal();

    return 0;
}
