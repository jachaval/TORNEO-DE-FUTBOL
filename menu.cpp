#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
using namespace std;
#include "menu.h"
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "equipo.h"
#include "jugador.h"
#include "torneo.h"
#include "partido.h"
#include "configuraciones.h"

void menu_principal(){

    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("MENÚ PRINCIPAL ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        cout << "    1. INICAR TORNEO" << endl;
        cout << "    2. CONTINUAR TORNEO" << endl;
        cout << "    3. VER TORNEO" << endl;
        cout << "    4. ESTADÍSTICAS E INFORMES " << endl;
        cout << "    5. CONFIGURACIONES " << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                menu_iniciar_torneo();
                break;
            case 2:
                cls();
                menu_cargar_torneo();
                break;
            case 3:
                cls();
                menu_ver_torneo();
                break;
            case 4:
                cls();
                menu_estadisticas();
                break;
            case 5:
                menu_configuraciones();
                break;

            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

void menu_iniciar_torneo(){
    int opcion,i, cant_equipos;

	do{
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
        cout << "    1. SELECCIONAR TORNEO" << endl;
        cout << "    2. CARGAR EQUIPO Y JUGADORES" << endl;
        cout << "    3. SORTEAR EQUIPOS" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;


        int cantidad_equipos;
        int cant_equiposCargados;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                FILE*pArchivo;
                pArchivo=fopen(FILE_TORNEOS,"rb");
                if (pArchivo==NULL){ /// VERFICO ATRAVES DE LA APERTURA LA EXISTENCIA DEL ARCHIVO POR LO TANTO TAMBIEN SE INICIO UN TORNEO
                    cant_equipos=seleccionar_torneo();
                }
                else {
                    cout<< "    YA HAY UN TORNEO ACTIVO"<<endl;
                    anykey();
                    fclose(pArchivo);
                }
                break;
            case 2:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);

                FILE *p;
                p=fopen(FILE_TORNEOS,"rb");
                if(p==NULL){
                    cout << "    SELECCIONAR TORNEO PRIMERO"<<endl<<endl;
                    anykey();
                }
                else{
                    cantidad_equipos=informar_tipoTorneo(); ///devuelve la cantidad de equipos total del torneo seleccionado.
                    cant_equiposCargados=contar_equiposCargados(); //devuelve la cantidad de los equipos cargados, si ya estan todo no permite cargar mas

                    if(cant_equiposCargados==cantidad_equipos){
                        if(cantidad_equipos>0){
                            cout<<"    YA ESTÁN TODOS LOS EQUIPOS CARGADOS. SORTEE LOS EQUIPO Y CONTINUE TORNEO"<<endl;
                            anykey();
                        }
                        else{
                            cout<<"    PRIMERO SELECCIONE EL TORNEO PARA PODER CARGAR LOS EQUIPOS"<<endl;
                            anykey();
                        }
                    }
                    else{
                        cout<< "    EQUIPOS CARGADOS HASTA EL MOMENTO: "<< cant_equiposCargados<<" de " << cantidad_equipos<<endl<<endl;
                        ingresar_equipos(cant_equipos); //agrega todos los equipos y jugadores y los guarda en equipos.dat
                    }
                }
                fclose(p);
            break;
            case 3:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                int valor;

                valor=verificar_sorteo();
                if(valor==1){
                    sortear();

                }
                else{
                    cout<<"EL TORNEO NO SE PUEDE VOLVER A SORTEAR SI YA HAY UN PARTIDO JUGADO"<<endl;
                    anykey();
                }

            break;
            case 0:
                return;
            break;
        }
	} while (opcion != 0);
}

void menu_cargar_torneo(){
    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        setColor(GREEN);
        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("CONTINUAR TORNEO ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }
        setColor(WHITE);
        gotoxy(1,6);
        cout << "    1. CARGAR PARTIDOS" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);

                cargar_resultado_partido();

                break;

            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

void menu_estadisticas(){

    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        setColor(YELLOW);
        for (i = 0; i < 29; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(7, 4); printf("ESTADÍSTICAS DEL TORNEO ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(32, 4); printf("*");
        }
        setColor(WHITE);
        gotoxy(1,6);
        cout << "    1. RESULTADOS  " << endl;
        cout << "    2. GOLEADORES  " << endl;
        cout << "    3. ASISTENCIAS " << endl;
        cout << "    4. TARJETAS ROJAS " << endl;
        cout << "    5. TARJETAS AMARILLAS " << endl;
        cout << "    6. BUSCAR JUGADOR " << endl;
        cout << "    7. BUSCAR EQUIPO " << endl;
        cout << "    8. LISTAR EQUIPOS" << endl;
        cout << "    9. LISTAR JUGADORES" << endl;
        cout << "    10. LISTAR JUGADORES POR EQUIPO"<<endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                menu_resultados();
                anykey();

                break;
            case 2:

                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                tabla_goleadores();
                anykey();


                break;
            case 3:
                 cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                tabla_asistidores();
                anykey();


                break;
            case 4:
              cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                tabla_rojas();
                anykey();

                break;
            case 5:
                 cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                tabla_amarillas();
                anykey();


                break;
            case 6:

                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                buscar_jugador();
                anykey();

                break;
            case 7:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                buscarEquipo();
                anykey();


                break;
            case 8:
                system("cls");
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                listar_equipos();
                anykey();
                break;
            case 9:
                system("cls");
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                listar_jugadores();
                anykey();
                break;
            case 10:
                system("cls");
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                listar_jugadores_x_equipo();
                anykey();
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

void menu_ver_torneo(){
    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        setColor(MAGENTA);
        for (i = 0; i < 29; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(7, 4); printf("VER TORNEO ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(32, 4); printf("*");
        }
        setColor(WHITE);
        gotoxy(1,6);
        cout << "    1. VER FASE ACTUAL  " << endl;
        cout << "    2. VER PROXIMOS ENCUENTROS  " << endl;
        cout << "    3. VER GANADOR DEL TORNEO " << endl;

        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                ver_fase_torneo();
                anykey();

                break;
            case 2:

                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                ver_proximos_encuentros();
                anykey();


                break;
            case 3:
                 cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                ver_ganador();
                anykey();


                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);

}

void menu_configuraciones(){
    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        setColor(MAGENTA);
        for (i = 0; i < 29; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(7, 4); printf("CONFIGURACIONES");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(32, 4); printf("*");
        }
        setColor(WHITE);
        gotoxy(1,6);
        cout << "    1. EXPORTAR ARCHIVOS EN FORMATO TEXTO" << endl;
        cout << "    2. EDITAR REGISTROS" << endl;
        cout << "    3. CRÉDITOS " << endl;

        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                exportar_a_texto();
                anykey();

                break;
            case 2:

                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);
                modificar_registros();


                anykey();


                break;
            case 3:
                 cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                creditos();
                anykey();


                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);

}

void menu_resultados(){

 int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
        setColor(GREEN);
        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("RESULTADOS ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }
        setColor(WHITE);
        gotoxy(1,6);
        cout << "    1. TODOS LOS RESULTADOS" << endl;
        cout << "    2. RESULTADOS POR FASE" << endl;
        cout << "    3. RESULTADOS POR EQUIPO" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                listar_partidos();

                break;
            case 2:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                resultados_por_fase();

                break;
            case 3:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                resultados_por_equipo();

                break;

            case 0:	return;
            break;
        }
	} while (opcion != 0);
}



