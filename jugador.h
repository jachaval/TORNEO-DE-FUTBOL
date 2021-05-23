#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#define FILE_JUGADORES "datos/jugadores.dat"
class Jugador{
	private:
		int nro_equipo;
		char nombre[25];
		char apellido[25];
		char nombre_equipo[30];
		char posicion[25];
		int tarjeta_roja;
		int tarjeta_amarilla;
		int asistencias;
		int cant_goles;
		int nro_camiseta;
	public:
	    Jugador();
		void cargar();
		void mostrar();
		bool escribrirEnDisco(int pos);
		bool guardarEnDisco();
		void setNro_equipo(int);
		void setNombre(char *);
		void setApellido(char *);
		void setNombre_equipo(char *);
		void setPosicion(char *);
		void setTarjeta_roja(int);
		void setTarjeta_amarilla(int);
		void setAsistencias(int);
		void setCant_goles(int);
		void setNro_camiseta(int);


		int getNro_equipo();
		char *getNombre();
		char *getApellido();
		char *getNombre_equipo();
		char *getPosicion();
		int getTarjeta_roja();
		int getTarjeta_amarilla();
		int getAsistencias();
		int getCant_goles();
		int getNro_camiseta();
		void aumentar_gol();
		void aumentar_asistencia();
		void aumentar_amarilla();
		void aumentar_roja();
};

Jugador buscar_jugador(Jugador nro_camiseta);
void listar_jugadores();
void listar_jugadores_x_equipo();
void mostrar_goleadores(Jugador *v);
void mostrar_asistencias(Jugador *v);
void mostrar_amarillas(Jugador *v);
void mostrar_rojas(Jugador *v);
void mostrar_jugador(Jugador);
void mostrar_nombre_equipo();

int cantidad_jugadores();


void tabla_goleadores();
void tabla_asistidores();
void tabla_amarillas();
void tabla_rojas();
void buscar_jugador();





#endif // JUGADOR_H_INCLUDED
