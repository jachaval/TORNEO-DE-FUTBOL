#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <fstream>
#include <conio.h>
using namespace std;
#include "configuraciones.h"
#include "equipo.h"
#include "interfaz.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
#include <ctime>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"
#include "partido.h"
#include "equipo.h"

void exportar_a_texto(){
    char seguro;
    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("EXPORTAR DATOS ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        cout << "    1. EXPORTAR EQUIPOS" << endl;
        cout << "    2. EXPORTAR JUGADORES" << endl;
        cout << "    3. EXPORTAR PARTIDOS" << endl;
        cout << "    4. EXPORTAR TORNEOS " << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        cout<< endl<< "    ¿ESTÁ SEGURO DE EXPORTAR EL ARCHIVO ELEGIDO? (S/N)"; ///FALTARIA AGREGAR VALIDACION POR INGRESOS INCORRECTOS
        cin>>seguro;

        while(seguro!='S' && seguro!='s'){
            if(seguro=='N' || seguro=='n') {
                return;
            }
            cout << "Ingreso incorrecto";
            cout<< endl<< "    >¿ESTÁ SEGURO DE LA ELECCIÓN? (S/N)"; ///FALTARIA AGREGAR VALIDACION POR INGRESOS INCORRECTOS
            cin>>seguro;
        }
        switch (opcion) {
            case 1:
                cls();
                exportar_equipos();
                break;
            case 2:
                cls();
                exportar_jugadores();
                break;
            case 3:
                cls();
                exportar_partidos();
                break;
            case 4:
                cls();
                exportar_torneos();
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

void exportar_equipos(){
    ofstream archivo;
    archivo.open("datos texto/equipos.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_EQUIPOS,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Equipo eq;

    archivo<<"NRO EQUIPO,NOMBRE,PG,PP,GF,GC"<<endl;
	while(fread(&eq, sizeof (Equipo), 1 , p)){
        archivo<<eq.getNro_equipo()<<","<<eq.getNombre_equipo()<<","<<eq.getPartidos_ganados()<<","<<eq.getPartidos_perdidos()<<","<<eq.getGoles_afavor()<<","<<eq.getGoles_encontra()<<endl;
    }
	fclose(p);
    archivo.close();

    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void exportar_jugadores(){
    ofstream archivo;
    archivo.open("datos texto/jugadores.csv", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_JUGADORES,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Jugador ju;

    archivo<<"NRO EQUIPO;NOMBRE;APELLIDO;POSICION;NRO CAMISETA;GOLES;ASISTENCIAS;T. ROJAS;T. AMARILLAS"<<endl;
	while(fread(&ju, sizeof (Jugador), 1 , p)){
        archivo<<ju.getNro_equipo()<<";"<<ju.getNombre()<<";"<<ju.getApellido()<<";"<<ju.getPosicion()<<";"<<ju.getNro_camiseta()<<";"<<ju.getCant_goles()<<";"<<ju.getAsistencias()<<";"<<ju.getTarjeta_roja()<<";"<<ju.getTarjeta_amarilla()<<endl;
    }
	fclose(p);
    archivo.close();

    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void exportar_partidos(){
    ofstream archivo;
    archivo.open("datos texto/partidos.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_PARTIDOS,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO PARTIDOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Partido par;

    archivo<<"CODIGO TORNEO,EQUIPO LOCAL,EQUIPO VISITANTE,GOLES LOCAL,GOLES VISITANTE,EQUIPO GANADOR,INSTANCIA,NRO PARTIDO"<<endl;
	while(fread(&par, sizeof (Partido), 1 , p)){
        archivo<<par.getCodigo_toneo()<<","<<par.getEquipo_local()<<","<<par.getEquipo_visitante()<<","<<par.getGoles_local()<<","<<par.getGoles_visitante()<<","<<par.getEquipo_ganador()<<","<<par.getInstancia_torneo()<<endl;
    }
	fclose(p);
    archivo.close();
    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void exportar_torneos(){
    ofstream archivo;
    archivo.open("datos texto/torneos.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_TORNEOS,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Torneo tor;

    archivo<<"TIPO TORNEO,CODIGO TORNEO,INSTANCIA,PARTIDOS JUGADOS,TORNEO ACTIVO"<<endl;
	while(fread(&tor, sizeof (Torneo), 1 , p)){
        archivo<<tor.getTipo_torneo()<<","<<tor.getCodigo_torneo()<<","<<tor.getInstancia_torneo()<<","<<tor.getPartidos_jugados()<<","<<tor.getTorneo_activo()<<endl;
	}
	fclose(p);
    archivo.close();
    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void modificar_registros(){

        int i, opcion;

        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        setColor(RED);
        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("INICIAR TORNEO");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }
        setColor(WHITE);

        gotoxy(1,6);
        cout << "    1. MODIFICAR NOMBRE EQUIPOS" << endl;
        cout << "    2. MODIFICAR JUGADOR" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;


        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);

                modificar_equipo();

                break;
            case 2:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                modificar_jugadores();

            break;
            case 3:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                creditos();
                anykey();
                break;
            case 0:
                return;
            break;
        }
}



void modificar_equipo(){
    Equipo eq;
    FILE*p;
    int opcion;

    p=fopen(FILE_EQUIPOS,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }


    listar_equipos_del_torneo();
    cout<<endl<< "Ingrese el número del equipo cuyo nombre desea modificar: ";
    cin>>opcion;
    cls();
    char nombre[40];
    cout<<"Ingrese el nuevo nombre de el equipo: ";
    cin.ignore();
    cin.getline(nombre, 40);

    strupr(nombre);


    while(fread(&eq,sizeof(Equipo),1,p)==1){
        if(opcion==eq.getNro_equipo()){
            eq.setNombre_equipo(nombre);
            cout<<endl;
            cout<<"  Nombre cambiado correctamente"<<endl;
            fseek(p,ftell(p)-sizeof (Equipo),0);
            fwrite(&eq, sizeof(Equipo), 1 , p);
            fclose(p);
            return;
        }
    }
}


void modificar_jugadores(){

    Jugador jug;
    FILE*p;
    int opcion, opcion2, opcion3, opcion4;

    p=fopen(FILE_JUGADORES,"rb");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }


    listar_equipos_del_torneo();
    cout<<endl;
    cout<<"Ingrese el número del equipo donde está el jugador que desea editar: ";
    cin>>opcion;
    cls();

    cout << left;
    cout << setw(17) << "Equipo " << setw(17) << "|Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posición " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
    cout << endl << "-------------------------------------------------------------------------------------------------------------------------" << endl;

    while(fread(&jug,sizeof(Jugador),1,p)==1){
        if(opcion==jug.getNro_equipo()){
            jug.mostrar();
        }
    }
    fclose(p);
    cout<<endl;
    cout<<"Ingrese el número de camiseta del jugador que desea modificar: "<<endl;
    cin>>opcion2;
    cls();

    Jugador ju;
    FILE*pArchivo;


    pArchivo=fopen(FILE_JUGADORES,"rb+");
    if (pArchivo == NULL){
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(opcion==ju.getNro_equipo() && opcion2==ju.getNro_camiseta()){
            cout << "    1. MODIFICAR NOMBRE DEL JUGADOR" << endl;
            cout << "    2. MODIFICAR APELLIDO DEL JUGADOR" << endl;
            cout << "    3. MODIFICAR NÚMERO DE CAMISETA DEL JUGADOR" << endl;
            cout << "    4. MODIFICAR POSICIÓN DEL JUGADOR" << endl;
            cout << "    0. SALIR" << endl;
            cout << "    ------------------------------" << endl;

            cout <<"    Opción-> ";
            cin >> opcion3;

            char nombre[30], apellido[30], posicion[30];
            int camiseta;

            switch (opcion3) {
                case 1:
                    cls();
                    cout<<"Ingrese el nuevo nombre de el jugador: ";
                    cin.ignore();
                    cin.getline(nombre, 30);
                    strupr(nombre);
                    ju.setNombre(nombre);
                    fseek(p,ftell(p)-sizeof (Jugador),0);
                    fwrite(&ju, sizeof(Jugador), 1 , p);
                    fclose(p);
                    cls();
                    cout<<endl;
                    cout<<"  Registro editado correctamente."<<endl;
                break;
                case 2:
                    cls();
                    cout<<"Ingrese el nuevo apellido del jugador: ";
                    cin.ignore();
                    cin.getline(apellido, 30);
                    strupr(apellido);
                    ju.setApellido(apellido);
                    fseek(p,ftell(p)-sizeof (Jugador),0);
                    fwrite(&ju, sizeof(Jugador), 1 , p);
                    fclose(p);
                    cls();
                    cout<<endl;
                    cout<<"  Registro editado correctamente."<<endl;

                break;
                case 3:
                    cls();
                    cout<<"Ingrese el nuevo numero de camiseta del jugador: ";
                    cin>>camiseta;

                    ju.setNro_camiseta(camiseta);
                    fseek(p,ftell(p)-sizeof (Jugador),0);
                    fwrite(&ju, sizeof(Jugador), 1 , p);
                    fclose(p);
                    cls();
                    cout<<endl;
                    cout<<"  Registro editado correctamente."<<endl;
                break;
                case 4:
                    cls();
                    cout<< "    1-ARQUERO."<<endl;
                    cout<< "    2-DEFENSOR."<<endl;
                    cout<< "    3-MEDIOCAMPISTA."<<endl;
                    cout<< "    4-DELANTERO."<<endl;
                    cout<< "    Ingresar la nueva posición del jugador: ";
                    cin>>opcion4;

                    switch(opcion4){
                        case 1:
                            strcpy(posicion, "ARQUERO");
                            ju.setPosicion(posicion);
                            fseek(p,ftell(p)-sizeof (Jugador),0);
                            fwrite(&ju, sizeof(Jugador), 1 , p);
                            fclose(p);
                            cls();
                            cout<<endl;
                            cout<<"  Registro editado correctamente."<<endl;
                        break;
                        case 2:
                            strcpy(posicion, "DEFENSOR");
                            ju.setPosicion(posicion);
                            fseek(p,ftell(p)-sizeof (Jugador),0);
                            fwrite(&ju, sizeof(Jugador), 1 , p);
                            fclose(p);
                            cls();
                            cout<<endl;
                            cout<<"  Registro editado correctamente."<<endl;
                        break;
                        case 3:
                            strcpy(posicion, "MEDIOCAMPISTA");
                            ju.setPosicion(posicion);
                            fseek(p,ftell(p)-sizeof (Jugador),0);
                            fwrite(&ju, sizeof(Jugador), 1 , p);
                            fclose(p);
                            cls();
                            cout<<endl;
                            cout<<"  Registro editado correctamente."<<endl;
                        break;
                        case 4:
                            strcpy(posicion, "DELANTERO");
                            ju.setPosicion(posicion);
                            fseek(p,ftell(p)-sizeof (Jugador),0);
                            fwrite(&ju, sizeof(Jugador), 1 , p);
                            fclose(p);
                            cls();
                            cout<<endl;
                            cout<<"  Registro editado correctamente."<<endl;
                        break;
                        case 0:
                            return;
                        break;
                    }
                break;
                case 0:	return;
                break;
            }

        }
    }

return;
}

void creditos(){
    system("cls");
    title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
    setColor(YELLOW);
    for (int i = 0; i < 24; i++) {
        gotoxy(i + 4, 3); printf("*");
        gotoxy(9, 4); printf("!!! CRÉDITOS !!! ");
        gotoxy(i + 4, 5); printf("*");
        gotoxy(4, 4); printf("*");
        gotoxy(27, 4); printf("*");
    }
    gotoxy(1,6);
    setColor(WHITE);

    cout<<endl<< "    EL PROGAMA FUE UNA CREACIÓN REALIZADA POR "<< endl<<endl<<endl;
    setColor(GREEN);
    cout<< "    ACHÁVAL DURIA JOAQUÍN nro legajo: 23900 "<< endl;
    setColor(RED);
    cout<< "    AGUSTÍN ROBLES        nro legajo: 23992 "<< endl<<endl<<endl;
    setColor(WHITE);

    cout<< "    PARA CORRECCIONES O SUGERENCIAS SOBRE EL PROGAMA "<<endl;
    cout<< "    MANDAR MAIL A SUGERENCIAS@TORNEODEFUTBOL.COM "<<endl;

}
