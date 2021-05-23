#ifndef PARTIDO_H_INCLUDED
#define PARTIDO_H_INCLUDED
#define FILE_PARTIDOS "datos/partidos.dat"
#include "equipo.h"

class Partido {
private: //////// AGREGAR FECHA DE PARTIDO (agregar clase fecha)
    int codigo_toneo;
    int equipo_local;
    int equipo_visitante;
    int goles_local;
    int goles_visitante;
    int equipo_ganador;
    int instancia_torneo;
    int nro_partido;
    bool jugado;

public:
    Partido();
    Partido(int cant_equipos);
    void setCodigo_toneo(int);
    void setEquipo_local(int);
    void setEquipo_visitante(int);
    void setGoles_local(int);
    void setGoles_visitante(int);
    void setEquipo_ganador(int);
    void setInstancia_torneo(int);
    void setNro_partido(int);
    void setJugado();
    int getCodigo_toneo();
    int getEquipo_local();
    int getEquipo_visitante();
    int getGoles_local();
    int getGoles_visitante();
    int getEquipo_ganador();
    int getInstancia_torneo();
    int getNro_partido();
    bool getJugado();
    bool escribrirEnDisco(int pos);
    bool guardarEnDisco();
    void aumentar_partidos_jugados(int);
    void ingresarCodigo_torneo();
    void autonumerar_partido();
};



void cargar_partido_8(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo);

void cargar_partido_16(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo);

void cargar_partido_32(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo);

void cargar_partido_64(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo, int partidos_jugados, int codigo_torneo);

int cantidad_partidos();

void listar_partidos();

void resultados_por_fase();

void resultados_por_equipo();

void mostrar_resultados(int , int );

void buscar_nombre_equipo(int);

void generar_registros_partidos(int, int);

int buscar_posicion_nropartido_jugado(Partido *,int, int);

int buscar_posicion_nropartido_prox_fase(Partido *,int, int);

void mostrar_fase(int);


#endif // PARTIDO_H_INCLUDED
