#ifndef TORNEO_H_INCLUDED
#define TORNEO_H_INCLUDED
#define FILE_TORNEOS "datos/torneos.dat"

class Torneo {
    private:
        int tipo_torneo;///64 equipos, 32 equipos, 16 equipos o 8 equipos.
        int codigo_torneo;
        int instancia_torneo;/// al iniciar torneo se carga con la llave inicial correspondiente. cuando pasa de llave se va cambiando el valor.
        int partidos_jugados;
        bool torneo_activo;
   public:
        Torneo();
        void setTipo_torneo(int);
        void setCodigo_torneo(int);
        void setInstancia_torneo(int);
        void setPartidos_jugados(int);
        void setTorneo_activo(bool);
        int getTipo_torneo();
        int getCodigo_torneo();
        int getInstancia_torneo();
        int getPartidos_jugados();
        bool getTorneo_activo();
        void cargar();
		void mostrar();
		bool escribrirEnDisco(int pos);
		bool guardarEnDisco();
		void cambiar_instacia_torneo();
		void autonumerar_torneo();
		void aumentar_partidos_jugados();
};

int informar_tipoTorneo();
int seleccionar_torneo();
int verificar_partido_misma_fase(int , int);
void cargar_resultado_partido();

bool registrarResultado(int, int, int, int);

bool registrarGol(int nro_equipo, int numeroCamiseta);

bool registrarAsistencia(int nro_equipo, int numeroCamiseta);

bool registrarAmarilla(int nro_equipo, int numeroCamiseta);

bool registrarRoja(int nro_equipo, int numeroCamiseta);

void mostrar_llaveTorneo();

void cambiar_instancia_torneo();

void contar_partido_cargado();

int contar_torneosCargados();

void ver_fase_torneo();

int verificar_camiseta(int nro_equipo, int nro_jugador);

bool verificar_activo(int);
#endif // TORNEO_H_INCLUDED
