#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED
#define FILE_EQUIPOS "datos/equipos.dat"

class Equipo{
	private:
		int nro_equipo;
		char nombre_equipo[30];
		int goles_afavor;
		int goles_encontra;
		int partidos_ganados;
		int partidos_perdidos;
		bool activo;
		bool existe;
	public:
	    Equipo();
		void cargar();
		void mostrar();
		bool escribrirEnDisco(int pos);
		bool guardarEnDisco();
		void setNro_equipo(int);
		void setNombre_equipo(char *);
		void setGoles_afavor(int);
		void setGoles_encontra(int);
		void setPartidos_ganados(int);
		void setPartidos_perdidos(int);
		void setActivo();
		void setExiste();
		int getNro_equipo();
		char *getNombre_equipo();
		int getGoles_afavor();
		int getGoles_encontra();
		int getPartidos_ganados();
		int getPartidos_perdidos();
		bool getExiste();
		bool getActivo();
		void aumentar_gol_afavor(int);
        void aumentar_gol_encontra(int);
        void aumentar_partidos_ganados();
        void aumentar_partidos_perdidos();
};

void ingresar_equipos(int cant_equipos);

bool cargar_equipo(int cant_equipos);
bool cargar_jugadores(int cant_jugadores, int nroEquipo, char *);
int contar_equiposCargados();

void buscarEquipo();

void mostrar_equipo(Equipo);
void listar_equipos();

bool copiar_nombre_equipo(char *,int);
void nombre_equipo1(char * nom_equipo,int equipo);


bool checkrep(int n, int num[]);
void poner_equipos_aleatorios(int * vecAleatorio, int cant_equipos); //carga un vector aleatorio para poner en orden al alzar lo equipos
void sortear();
void sortear_equipos(int cantidad_equipos);
void cambiar_nroequipo_jugadores(int *vecAleatorio, int cant);
int verificar_sorteo();
void listar_equipos_en_competencia();
void ver_proximos_encuentros();
void listar_equipos_del_torneo();


void ver_ganador();


void fase_final(int);
void fase_semi(int);
void fase_cuartos(int);
void fase_octavos(int);
void fase_16(int);
void fase_32(int);

void poner_equipos_enpartidos(int cant_equipos);

bool verificar_camiseta_equipo(int , int);


#endif // EQUIPO_H_INCLUDED
