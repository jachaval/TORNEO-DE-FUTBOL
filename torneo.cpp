#include <iostream>
#include <cstdlib>
#include <ctime>
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

void Torneo::setTipo_torneo(int tipo){tipo_torneo=tipo;}
void Torneo::setCodigo_torneo(int codigo){codigo_torneo=codigo;}
void Torneo::setInstancia_torneo(int inst){instancia_torneo=inst;}
void Torneo::setPartidos_jugados(int par){partidos_jugados=par;}
void Torneo::setTorneo_activo(bool activo){torneo_activo=activo;}
int  Torneo::getTipo_torneo(){return tipo_torneo;}
int  Torneo::getCodigo_torneo(){return codigo_torneo;}
int  Torneo::getInstancia_torneo(){return instancia_torneo;}
int  Torneo::getPartidos_jugados(){return partidos_jugados;}
bool Torneo::getTorneo_activo(){return torneo_activo;}

Torneo::Torneo(){
    partidos_jugados=0;
    torneo_activo=true;
}

bool Torneo::escribrirEnDisco(int pos){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb+");
    if(pArchivo==NULL)return false;
    fseek(pArchivo, pos * sizeof(Partido), SEEK_SET);
    guardo = fwrite(this, sizeof(Partido), 1, pArchivo);
    fclose(pArchivo);
    return guardo;
}

void Torneo::mostrar(){

    cout << left;
    cout << setw(18);
    cout << getTipo_torneo();
    cout << setw(15) ;
    cout << getCodigo_torneo();
    cout << setw(15) ;
    cout << getInstancia_torneo();
    cout << setw(15) ;
    cout << getPartidos_jugados();
    cout << setw(7) ;
    cout << getTorneo_activo();
    cout << setw(13) ;
    cout << endl;

}

void Torneo::aumentar_partidos_jugados(){
    partidos_jugados++;
}

bool Torneo::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Torneo),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

void Torneo::cambiar_instacia_torneo(){
    instancia_torneo=instancia_torneo/2;
}

void Torneo::autonumerar_torneo(){
    int cant;
    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS, "rb");
    if(pArchivo==NULL){
        codigo_torneo=1;
        return;
    }
    cant=contar_torneosCargados();

    /// esto es para el final que serian varios toreos
    codigo_torneo=cant+1;
    cls();
    cout<<"codigo torneo "<<codigo_torneo<<endl<<endl;
    anykey();
    fclose(pArchivo);
}

int contar_torneosCargados(){
    FILE*pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if (pArchivo == NULL){
        return 0;
    }
    int bytes, cant;
    fseek(pArchivo, 0, SEEK_END);
    bytes = ftell(pArchivo);
    fclose(pArchivo);
    cant = bytes / sizeof(Equipo);
    return cant;
}

int informar_tipoTorneo(){

    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if(pArchivo==NULL){
        return 0;
    }
    int cant;
    Torneo tor;
    fread(&tor, sizeof(Torneo), 1, pArchivo);
    fclose(pArchivo);
    cant=tor.getTipo_torneo();
    return cant;
}

int seleccionar_torneo(){
    int torneo, cant_equipos;
    char seguro;
    cout<<"    Seleccionar torneo:"<<endl<<endl;
    cout<<"    1 - 32vos = 64 EQUIPOS "<<endl;
    cout<<"    2 - 16vos = 32 EQUIPOS"<<endl;
    cout<<"    3 - 8vos  = 16 EQUIPOS"<<endl;
    cout<<"    4 - 4tos  = 8 EQUIPOS"<<endl<<endl;

    cout<<"    Opción-> ";
    cin>> torneo;

    while(torneo<1 || torneo>4){

        cout<< endl<< "    LA OPCIÓN INGRESADA ES INCORRETA. POR FAVOR, INGRESE UNA DE LAS OPCIONES EN PANTALLA. "<<endl;
        cout<<"    >Opción-> ";
        cin>>torneo;
        cout<<endl;

    }

    if(torneo==1) cant_equipos=64;
    if(torneo==2) cant_equipos=32;
    if(torneo==3) cant_equipos=16;
    if(torneo==4) cant_equipos=8;

    cout<< endl<< "    HA SELECCIONADO EL TORNEO PARA "<< cant_equipos << " EQUIPOS"<<endl;
    cout<< endl<< "    ¿ESTÁ SEGURO DE LA ELECCIÓN? (S/N)";
    cin>>seguro;

    while(seguro!='S' && seguro!='s'){
        if(seguro=='N' || seguro=='n') {
            return 0;
        }
        cout << "Ingreso incorrecto";
        cout<< endl<< "    >¿ESTÁ SEGURO DE LA ELECCIÓN? (S/N)";
        cin>>seguro;
    }
    msj("TORNEO SELECCIONADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);

    Torneo tor;
    tor.autonumerar_torneo();
    tor.setInstancia_torneo(cant_equipos/2);
    tor.setTipo_torneo(cant_equipos);
    tor.guardarEnDisco();

    generar_registros_partidos(cant_equipos, tor.getPartidos_jugados());    /// Genera los registro de los partidos para que se modiquen y se completen a medida que se jugan los partidos

    return cant_equipos;
}

int verificar_partido_misma_fase(int instancia, int nro_equipo){
    Partido par;
    FILE* pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb");

    while(fread(&par,sizeof(Partido),1,pArchivo)){
        if(par.getInstancia_torneo()==instancia && par.getJugado()==1){
            if(nro_equipo==par.getEquipo_local()|| nro_equipo==par.getEquipo_visitante()){
                return 1;
            }
        }

    }
    fclose(pArchivo);
    return 0;
}

void cargar_resultado_partido(){
    int numeroEquipo1,numeroEquipo2, numeroCamiseta, numeroCamiseta_asistencia, golesEquipo1,golesEquipo2, equipo_ganador;
    int resultado, res_penales1=0, res_penales2=0;
    bool grabo;
    Torneo tor;
    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if(pArchivo==NULL){

        cout << "INICIAR TORNEO PRIMERO"<<endl<<endl;
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    fread(&tor, sizeof(Torneo),1 , pArchivo);
    pclose(pArchivo);
    char nomb_equipo1[30];
    char nomb_equipo2[30];

    switch (tor.getTipo_torneo()){
        case 8:
            if(tor.getInstancia_torneo()==4){
                cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE CUARTOS DE FINAL" <<endl<<endl;
            }
            if(tor.getInstancia_torneo()==2){
                if(tor.getPartidos_jugados()==4){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<1<< " DE LA LLAVE DE SEMIFINAL" <<endl<<endl;
                }
                if(tor.getPartidos_jugados()==5){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<2<< " DE LA LLAVE DE SEMIFINAL" <<endl<<endl;
                }
            }
            if(tor.getInstancia_torneo()==1){
                cout<<"    CARGAR DATOS DEL PARTIDO FINAL" <<endl<<endl;
            }
        break;
        case 16:
            if(tor.getInstancia_torneo()==8){
                cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"VOS" <<endl<<endl;
            }
            if(tor.getInstancia_torneo()==4){
                if(tor.getPartidos_jugados()==8){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<1<< " DE LA LLAVE DE CUARTOS DE FINAL" <<endl<<endl;
                }
                if(tor.getPartidos_jugados()==9){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<2<< " DE LA LLAVE DE CUARTOS DE FINAL" <<endl<<endl;
                }
                if(tor.getPartidos_jugados()==10){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<3<< " DE LA LLAVE DE CUARTOS DE FINAL" <<endl<<endl;
                }
                if(tor.getPartidos_jugados()==11){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<4<< " DE LA LLAVE DE CUARTOS DE FINAL" <<endl<<endl;
                }
            }
            if(tor.getInstancia_torneo()==2){
                if(tor.getPartidos_jugados()==12){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<1<< " DE LA LLAVE DE SEMIFINAL" <<endl<<endl;
                }
                if(tor.getPartidos_jugados()==13){
                    cout<<"    CARGAR DATOS DEL PARTIDO "<<2<< " DE LA LLAVE DE SEMIFINAL" <<endl<<endl;
                }
            }
            if(tor.getInstancia_torneo()==1){
                cout<<"    CARGAR DATOS DEL PARTIDO FINAL" <<endl<<endl;
            }
        break;
        case 32:
            if(tor.getInstancia_torneo()==16){
                cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"VOS" <<endl<<endl;
            }
        break;
        case 64:
            if(tor.getInstancia_torneo()==32){
                cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"VOS" <<endl<<endl;
            }
        break;

        default:
        break;
    }

    int verificado;
    bool eq;

    cout<<"    Número del primer equipo: ";
    cin>>numeroEquipo1;
    eq=copiar_nombre_equipo(nomb_equipo1,numeroEquipo1);
    while(eq==false){
        cout<<"   El equipo no existe. Por favor, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo1;
        eq=copiar_nombre_equipo(nomb_equipo1,numeroEquipo1);
    }

    while(verificar_activo(numeroEquipo1)==false){
        cout<<"   El equipo quedo eliminado del torneo. Por favor, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo1;
    }


    cout<<"    EQUIPO "<<nomb_equipo1;
    cout<<endl;
    verificado=verificar_partido_misma_fase( tor.getInstancia_torneo(),numeroEquipo1 );
    while(verificado==1){
        cout<<"   El equipo ya jugo un partido en esa fase, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo1;
        verificado=verificar_partido_misma_fase( tor.getInstancia_torneo(),numeroEquipo1 );
    }

    cout<<"    Goles: ";
    cin>>golesEquipo1;
    cout<<endl;

    while(golesEquipo1<0 || golesEquipo1>100){
        cout<<"    La opción es inválida."<<endl;
        cout<<"    >Goles: ";
        cin>>golesEquipo1;
    }



    cout<<"    Número del segundo equipo: ";
    cin>>numeroEquipo2;
    verificado=verificar_partido_misma_fase( tor.getInstancia_torneo(),numeroEquipo1 );
    while(verificado==1){
        cout<<"   El equipo ya jugo un partido en esa fase, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo2;
        verificado=verificar_partido_misma_fase( tor.getInstancia_torneo(),numeroEquipo1 );
    }
    eq=copiar_nombre_equipo(nomb_equipo2,numeroEquipo2);

     while(eq==false){
        cout<<"   El equipo no existe. Por favor, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo2;
        eq=copiar_nombre_equipo(nomb_equipo2,numeroEquipo2);
    }

    while(numeroEquipo1==numeroEquipo2){
        cout<<"   Un equipo no puede enfrentarse a si mismo. Por favor, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo2;
        cout<<endl;
         eq=copiar_nombre_equipo(nomb_equipo2,numeroEquipo2);

          while(eq==false){
           cout<<"   El equipo no existe. Por favor, vuelva a ingresar el número de equipo: "<<endl;
           cin>>numeroEquipo2;
            eq=copiar_nombre_equipo(nomb_equipo2,numeroEquipo2);}
    }

    while(verificar_activo(numeroEquipo2)==false){
        cout<<"   El esta eliminado del torneo. Por favor, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo2;
         eq=copiar_nombre_equipo(nomb_equipo2,numeroEquipo2);

        while(eq==false){
        cout<<"   El equipo no existe. Por favor, vuelva a ingresar el número de equipo: "<<endl;
        cin>>numeroEquipo2;
        eq=copiar_nombre_equipo(nomb_equipo2,numeroEquipo2);}
     }



    cout<<"    EQUIPO "<<nomb_equipo2;
    cout<<endl;
    cout<<"    Goles: ";
    cin>>golesEquipo2;
    cout<<endl;

    while(golesEquipo2<0 || golesEquipo2>100){
        cout<<"    La opción es inválida."<<endl;
        cout<<"    >Goles: ";
        cin>>golesEquipo2;
    }

    resultado=golesEquipo1-golesEquipo2;
    res_penales1=0;
    res_penales2=0;

    if(resultado==0){
        int penales1,penales2;

        cout<< "    INGRESE LOS RESULTADOS DE LA RONDA DE PENALTIES RESPETANDO EL ORDEN ANTERIOR"<<endl<<endl;
        cout<< "    Penales a favor de "<<nomb_equipo1<<": ";
        cin>>penales1;
        cout<<endl;

        cout<< "    Penales a favor de "<<nomb_equipo2<<": ";
        cin>>penales2;
        cout<<endl;

        while(penales1==penales2){
            cout<<"    Los penales no pueden ser iguales. Por favor, ingrese el resultado de nuevo."<<endl;

        cout<< "    Penales a favor de "<<nomb_equipo1<<": "<<endl;
        cin>>penales1;
        cout<<endl;

        cout<< "    Penales a favor de "<<nomb_equipo2<<": ";
        cin>>penales2;
        cout<<endl;

        }


        res_penales1=penales1-penales2;
        res_penales2=penales2-penales1;
        if (res_penales1>0){
            equipo_ganador=numeroEquipo1;
        }
        else{
            equipo_ganador=numeroEquipo2;
        }
    }
    else{
        if(golesEquipo1>golesEquipo2){
            equipo_ganador=numeroEquipo1;
        }
        else {
            equipo_ganador=numeroEquipo2;
        }
    }

    grabo=registrarResultado(golesEquipo1,golesEquipo2,res_penales1,numeroEquipo1);
    if(!grabo){
        msj("NO SE HA PODIDO GUARDAR EL RESULTADO",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    grabo=registrarResultado(golesEquipo2,golesEquipo1,res_penales2,numeroEquipo2);
    if(!grabo){
        msj("NO SE HA PODIDO GUARDAR EL RESULTADO",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
//////////////////////
    int i;
    char asis;
    int camiseta;

    if(golesEquipo1>0){
        cout<<"    ASIGNE GOLES DEL EQUIPO ";
        setColor(RED);
        cout<< nomb_equipo1<<endl<<endl;
        setColor(WHITE);

        for(i=0;i<golesEquipo1;i++){
            cout << "    Del gol "<<i+1<<"."<<endl<<endl;
            cout<<"    Ingrese nro de camiseta del jugador que marcó: ";
            cin>>numeroCamiseta;
            camiseta = verificar_camiseta(numeroEquipo1, numeroCamiseta);
            if (camiseta != -1){

                numeroCamiseta=camiseta;
            }

            cout<<"    ¿HUBO ASISTENCIA?(S/N):";
            cin>>asis;
            cout<<endl;

           while(asis!='S' && asis!='s' && asis!='N' && asis!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>asis;
            cout<<endl;
            }


            if(asis=='s' || asis=='S'){
                cout<<"    Ingrese nro de camiseta del jugador que asistió: ";
                cin>>numeroCamiseta_asistencia;
                cout<<endl;
                  camiseta = verificar_camiseta(numeroEquipo1, numeroCamiseta_asistencia);
                if (camiseta != -1){

                numeroCamiseta_asistencia=camiseta;
            }

            }
            else{
                numeroCamiseta_asistencia=0;
            }

            grabo=registrarGol(numeroEquipo1,numeroCamiseta);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR EL GOL",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
            grabo=registrarAsistencia(numeroEquipo1,numeroCamiseta_asistencia);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA ASISTENCIA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
        }
    }
    if(golesEquipo2>0){
        cout<<"    ASIGNE GOLES DEL EQUIPO ";
        setColor(RED);
        cout<< nomb_equipo2<<endl<<endl;
        setColor(WHITE);
        for(i=0;i<golesEquipo2;i++){
            cout << "    Del gol "<<i+1<<"."<<endl<<endl;
            cout<<"    Ingrese nro de camiseta del jugador que marcó: ";
            cin>>numeroCamiseta;
              camiseta = verificar_camiseta(numeroEquipo2, numeroCamiseta);
            if (camiseta != -1){

                numeroCamiseta=camiseta;
            }

            cout<<"    ¿HUBO ASISTENCIA?(S/N):";
            cin>>asis;
            cout<<endl;


           while(asis!='S' && asis!='s' && asis!='N' && asis!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>asis;
            cout<<endl;
            }

            if(asis=='s' || asis=='S'){
                cout<<"    Ingrese nro de camiseta del jugador que asistió: ";
                cin>>numeroCamiseta_asistencia;
                cout<<endl;
            camiseta = verificar_camiseta(numeroEquipo2, numeroCamiseta_asistencia);
            if (camiseta != -1){

                numeroCamiseta=camiseta;
            }

            }
            else{
                numeroCamiseta_asistencia=0;
            }

            grabo=registrarGol(numeroEquipo2,numeroCamiseta);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR EL GOL",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
            grabo=registrarAsistencia(numeroEquipo2,numeroCamiseta_asistencia);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA ASISTENCIA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
        }
    }
//////////////////
    int numeroCamiseta_amarilla,numeroCamiseta_roja;
    char amarillas,rojas;

    cout<<"    ¿EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo1;
    setColor(WHITE);
    cout<<" HUBO TARJETAS AMARILLAS?(S/N): ";
    cin>>amarillas;

    while(amarillas!='S' && amarillas!='s' && amarillas!='N' && amarillas!='n'){
        cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
        cin>>amarillas;
        cout<<endl;
        }


    while(amarillas=='s' || amarillas=='S'){
        cout<< endl<<"    Ingrese número de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_amarilla;


          camiseta = verificar_camiseta(numeroEquipo1, numeroCamiseta_amarilla);
            if (camiseta != -1){

                numeroCamiseta_amarilla=camiseta;
            }


        grabo=registrarAmarilla(numeroEquipo1, numeroCamiseta_amarilla);
        if(!grabo){
            msj("NO SE HA PODIDO GUARDAR LA TARJETA AMARILLA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
            return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA AMARILLA?(S/N): ";
        cin>>amarillas;
        while(amarillas!='S' && amarillas!='s' && amarillas!='N' && amarillas!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>amarillas;
            cout<<endl;
        }
    }

    cout<<endl<<"    ¿EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo2;
    setColor(WHITE);
    cout<<" HUBO TARJETAS AMARILLAS?(S/N): ";
    cin>>amarillas;


    while(amarillas!='S' && amarillas!='s' && amarillas!='N' && amarillas!='n'){
        cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
        cin>>amarillas;
        cout<<endl;
    }

    while(amarillas=='s' || amarillas=='S'){
        cout<< endl<<"    Ingrese número de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_amarilla;
          camiseta = verificar_camiseta(numeroEquipo2, numeroCamiseta_amarilla);
            if (camiseta != -1){

                numeroCamiseta_amarilla=camiseta;
            }


        grabo=registrarAmarilla(numeroEquipo2, numeroCamiseta_amarilla);
        if(!grabo){
            msj("NO SE HA PODIDO GUARDAR LA TARJETA AMARILLA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
            return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA AMARILLA?(S/N): ";
        cin>>amarillas;
        while(amarillas!='S' && amarillas!='s' && amarillas!='N' && amarillas!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>amarillas;
            cout<<endl;
        }
    }

////////////////////

    cout<<endl<<"    ¿EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo1;
    setColor(WHITE);
    cout<<" HUBO TARJETAS ROJAS?(S/N): ";
    cin>>rojas;

    while(rojas!='S' && rojas!='s' && rojas!='N' && rojas!='n'){
    cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
    cin>>rojas;
    cout<<endl;
    }

    while(rojas=='s' || rojas=='S'){
        cout<< endl<<"    Ingrese número de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_roja;
          camiseta = verificar_camiseta(numeroEquipo1, numeroCamiseta_roja);
            if (camiseta != -1){

                numeroCamiseta_roja=camiseta;
            }


        grabo=registrarRoja(numeroEquipo1, numeroCamiseta_roja);
        if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA TARJETA ROJA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA ROJA?(S/N): ";
        cin>>rojas;
        while(rojas!='S' && rojas!='s' && rojas!='N' && rojas!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>rojas;
            cout<<endl;
        }
    }

    cout<<endl<<"    ¿EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo2;
    setColor(WHITE);
    cout<<" HUBO TARJETAS ROJAS?(S/N): ";
    cin>>rojas;

    while(rojas!='S' && rojas!='s' && rojas!='N' && rojas!='n'){
        cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
        cin>>rojas;
        cout<<endl;
    }
    while(rojas=='s' || rojas=='S'){
        cout<< endl<<"    Ingrese número de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_roja;
          camiseta = verificar_camiseta(numeroEquipo2, numeroCamiseta_roja);
            if (camiseta != -1){

                numeroCamiseta_roja=camiseta;
            }


        registrarRoja(numeroEquipo2, numeroCamiseta_roja);
        if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA TARJETA ROJA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA ROJA?(S/N): ";
        cin>>rojas;
        while(rojas!='S' && rojas!='s' && rojas!='N' && rojas!='n'){
            cout<<"    Opción inválida. Debe ingresar 'S' o 'N'.";
            cin>>rojas;
            cout<<endl;
        }
    }
    switch (tor.getTipo_torneo()){ ///tipo torneo = a 64 32 16 o 8 cantidad de equipos
        case 64:
            cargar_partido_64(numeroEquipo1, numeroEquipo2, golesEquipo1, golesEquipo2, equipo_ganador, tor.getInstancia_torneo(), tor.getPartidos_jugados(), tor.getCodigo_torneo());
        break;
        case 32:
            cargar_partido_32(numeroEquipo1, numeroEquipo2, golesEquipo1, golesEquipo2, equipo_ganador, tor.getInstancia_torneo(), tor.getPartidos_jugados(), tor.getCodigo_torneo());
        break;
        case 16:
            cargar_partido_16(numeroEquipo1, numeroEquipo2, golesEquipo1, golesEquipo2, equipo_ganador, tor.getInstancia_torneo(), tor.getPartidos_jugados(), tor.getCodigo_torneo());
        break;
        case 8:
            cargar_partido_8(numeroEquipo1, numeroEquipo2, golesEquipo1, golesEquipo2, equipo_ganador, tor.getInstancia_torneo(), tor.getPartidos_jugados(), tor.getCodigo_torneo());
        break;
        default:
        break;
    }

    if(grabo){
        contar_partido_cargado();
        cambiar_instancia_torneo();
        msj("PARTIDO GUARDADO CORRECTAMENTE",APP_TITLEFORECOLOR, APP_OKCOLOR);
    }
}

bool registrarResultado(int goles_a_favor,int goles_en_contra, int diferencia_penales, int equipo){
    Equipo eq;
    int diferencia;
    FILE*p;
    p=fopen(FILE_EQUIPOS,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }
    diferencia=goles_a_favor-goles_en_contra;


    while(fread(&eq,sizeof(Equipo),1,p)==1){
        if(equipo==eq.getNro_equipo()){
            eq.aumentar_gol_afavor(goles_a_favor);
            eq.aumentar_gol_encontra(goles_en_contra);
            if(diferencia>0)eq.aumentar_partidos_ganados();

            if(diferencia<0){
                eq.aumentar_partidos_perdidos();
                eq.setActivo();
            }
            if(diferencia==0){
                if(diferencia_penales>0){
                    eq.aumentar_partidos_ganados();
                }
                else{
                    eq.aumentar_partidos_perdidos();
                    eq.setActivo();
                }
            }
            fseek(p,ftell(p)-sizeof (Equipo),0);
            fwrite(&eq, sizeof(Equipo), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool registrarGol(int nro_equipo, int numeroCamiseta){

    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta==ju.getNro_camiseta()){

            ju.aumentar_gol();

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool registrarAsistencia(int nro_equipo, int numeroCamiseta_asistencia){
    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta_asistencia==ju.getNro_camiseta()){


            if(numeroCamiseta_asistencia>0){
                ju.aumentar_asistencia();
            }

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return true;
}

bool registrarAmarilla(int nro_equipo, int numeroCamiseta_amarilla){
    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta_amarilla==ju.getNro_camiseta()){


            if(numeroCamiseta_amarilla>0){
                ju.aumentar_amarilla();
            }

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return true;
}

bool registrarRoja(int nro_equipo, int numeroCamiseta_roja){
    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta_roja==ju.getNro_camiseta()){


            if(numeroCamiseta_roja>0){
                ju.aumentar_roja();
            }

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

void cambiar_instancia_torneo(){

    Torneo tor;
    FILE *p;
    p=fopen(FILE_TORNEOS,"rb+");
    if(p==NULL){
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    fread(&tor,sizeof(Torneo), 1,p);

    switch (tor.getTipo_torneo()){
        case 8:
            if(tor.getPartidos_jugados()==4){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==6){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
        break;
        case 16:
            if(tor.getPartidos_jugados()==8){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==12){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==14){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
        break;
        case 32:
            if(tor.getPartidos_jugados()==16){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==24){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==28){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==30){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
        break;
        case 64:
            if(tor.getPartidos_jugados()==32){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==48){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==56){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==60){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
            if(tor.getPartidos_jugados()==62){

                tor.cambiar_instacia_torneo();

                fseek(p, ftell(p)-sizeof(Torneo),0);
                fwrite(&tor , sizeof(Torneo),1 ,p);
                fclose(p);
            }
        break;
    }
    fclose(p);
}

void contar_partido_cargado(){
    Torneo tor;
    FILE *p;
    p=fopen(FILE_TORNEOS,"rb+");
    if(p==NULL){
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    fread(&tor,sizeof(Torneo), 1,p);

    tor.aumentar_partidos_jugados();

    fseek(p, ftell(p)-sizeof(Torneo),0);
    fwrite(&tor , sizeof(Torneo),1 ,p);


    fclose(p);
}

void ver_fase_torneo(){
    FILE*p;
    p=fopen(FILE_TORNEOS,"rb");
    if (p == NULL){
        msj("ERROR DE ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    Torneo tor;

    ///para varios torneos hay que agruegar un buscador de torneo por nombre
    fread(&tor, sizeof(Torneo), 1, p);

    switch(tor.getInstancia_torneo()){
        case 1:
            cout<< "    EL TORNEO SE ENCUENTRA EN LA FASE FINAL"<<endl;
            break;
        case 2:
            cout<< "    EL TORNEO SE ENCUENTRA EN LA FASE SEMIFINAL"<<endl;
            break;
        case 4:
            cout<< "    EL TORNEO SE ENCUENTRA EN LA FASE CUARTOS DE FINAL"<<endl;
            break;
        case 8:
            cout<< "    EL TORNEO SE ENCUENTRA EN LA FASE OCTAVOS DE FINAL"<<endl;
            break;
        case 16:
            cout<< "    EL TORNEO SE ENCUENTRA EN LA FASE 16 AVOS DE FINAL"<<endl;
            break;
        case 32:
            cout<< "    EL TORNEO SE ENCUENTRA EN LA FASE 32 AVOS DE FINAL"<<endl;
            break;

    }


    cout<< endl<< "    LOS EQUIPOS EN COMPETENCIA SON: "<<endl<<endl;

    listar_equipos_en_competencia();

    fclose(p);
}

int verificar_camiseta(int nro_equipo, int nro_jugador){
     Jugador reg;
     bool encontrado=false;




	while (encontrado==false ) {
        FILE* f;
        f = fopen(FILE_JUGADORES, "rb");
        if (f == NULL) {
            return -1;
        }

        while (fread(&reg, sizeof(Jugador), 1, f)) {
            if (nro_equipo == reg.getNro_equipo() && nro_jugador ==reg.getNro_camiseta() ) {
                encontrado=true;
                fclose(f);
                return nro_jugador;
            }
        }
        if(encontrado==false){
            cout<<"    El número de camiseta no existe. Por favor, vuelva a ingresarlo: "<<endl;
            cin>>nro_jugador;
            cout<<endl;
        }
        fclose(f);
	}
	return nro_jugador;

}

bool verificar_activo(int nro_de_equipo){

    Equipo reg;

    FILE* f;
	f = fopen(FILE_EQUIPOS, "rb");
	if (f == NULL) {

		return false;
	}

    while (fread(&reg, sizeof(Equipo), 1, f)) {
        if(reg.getNro_equipo()==nro_de_equipo){
            if (reg.getActivo()==true ) {
                    fclose(f);
                    return true;
            }
        }
    }
fclose(f);
return false;
}












































