#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
#include <conio.h>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"
#include "partido.h"
#include "equipo.h"


Jugador::Jugador(){
    tarjeta_roja=0;
    tarjeta_amarilla=0;
    asistencias=0;
    cant_goles=0;
}

void Jugador::setNro_equipo(int nro){nro_equipo=nro;}
void Jugador::setNombre(char *nom){strcpy(nombre,nom);}
void Jugador::setApellido(char *ap){strcpy(apellido,ap);}
void Jugador::setNombre_equipo(char * nom){strcpy(nombre_equipo,nom);}
void Jugador::setPosicion(char *pos){strcpy(posicion,pos);}
void Jugador::setTarjeta_roja(int roja){tarjeta_roja=roja;}
void Jugador::setTarjeta_amarilla(int amarilla){tarjeta_amarilla=amarilla;}
void Jugador::setAsistencias(int asis){asistencias=asis;}
void Jugador::setCant_goles(int goles){cant_goles=goles;}
void Jugador::setNro_camiseta(int nro){nro_camiseta=nro;}
int  Jugador::getNro_equipo(){return nro_equipo;}
char *Jugador::getNombre(){return nombre;}
char *Jugador::getApellido(){return apellido;}
char *Jugador::getNombre_equipo(){return nombre_equipo;}
char *Jugador::getPosicion(){return posicion;}
int  Jugador::getTarjeta_roja(){return tarjeta_roja;}
int  Jugador::getTarjeta_amarilla(){return tarjeta_amarilla;}
int  Jugador::getAsistencias(){return asistencias;}
int  Jugador::getCant_goles(){return cant_goles;}
int  Jugador::getNro_camiseta(){return nro_camiseta;}

void Jugador::aumentar_gol(){
    cant_goles++;
}

void Jugador::aumentar_asistencia(){
    asistencias++;
}
void Jugador::aumentar_amarilla(){
    tarjeta_amarilla++;
}

void Jugador::aumentar_roja(){
    tarjeta_roja++;
}

void Jugador::mostrar(){
    bool existe;
    char nomb_equipo[30];
    cout << left;
    cout << setw(18);
    existe=copiar_nombre_equipo(nomb_equipo,getNro_equipo());
    if (existe){cout<<nomb_equipo;}
    cout << setw(18);
    cout << getNombre();
    cout << setw(15) ;
    cout << getApellido();
    cout << setw(15) ;
    cout << getPosicion();
    cout << setw(15) ;
    cout << getNro_camiseta();
    cout << setw(7) ;
    cout << getCant_goles();
    cout << setw(13) ;
    cout << getAsistencias();
    cout << setw(10) ;
    cout << getTarjeta_roja();
    cout << setw(14) ;
    cout << getTarjeta_amarilla();
    cout << endl;
}

bool Jugador::escribrirEnDisco(int pos){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb+");
    if(pArchivo==NULL)return false;
    fseek(pArchivo, pos * sizeof(Partido), SEEK_SET);
    guardo = fwrite(this, sizeof(Partido), 1, pArchivo);
    fclose(pArchivo);
    return guardo;
}

bool Jugador::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Jugador),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

void listar_jugadores(){
    FILE * pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"rb");

    if(pArchivo==NULL){
        msj("ERROR ARCHIVO JUGADORES", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    Jugador ju;

        cout << endl << "    LISTA DE JUGADORES"<<endl<<endl;

        cout << left;
        cout << setw(17) << "Equipo " << setw(17) << "|Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posición " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
        cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;
        while(fread(&ju, sizeof (Jugador),1, pArchivo)==1){

                ju.mostrar();
            }

         anykey();
}

void listar_jugadores_x_equipo(){
    bool existe;
    int equipo;
    char nomb_equipo[30];
    FILE * pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO JUGADORES", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    Jugador ju;
    cout << "    INGRESE NÚMERO DEL EQUIPO A BUSCAR: ";
    cin >> equipo;

    existe=copiar_nombre_equipo(nomb_equipo,equipo);/// carga el nombre para poder poner el nombre del equipo Y ADEMAS VERIFICA QUE EXISTA EL EQUIPO
    if(existe){
        cout << endl << "    LISTA DE JUGADORES DEL EQUIPO: ";
        setColor(RED);
        cout << nomb_equipo<<endl<<endl;
        setColor(WHITE);
        cout << left;
        cout << setw(17) << "Equipo " << setw(17) << "|Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posición " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
        cout << endl << "-------------------------------------------------------------------------------------------------------------------------" << endl;
        while(fread(&ju, sizeof (Jugador),1, pArchivo)==1){
            if(equipo==ju.getNro_equipo()){

                ju.mostrar();

            }
        }
         anykey();

    }
    else{
        msj("EQUIPO NO ENCONTRADO",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
    }
}

int cantidad_jugadores(){
    FILE *p = fopen(FILE_JUGADORES, "rb");
    if (p == NULL){
        return 1;
    }
    int bytes, cant;
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    fclose(p);
    cant = bytes / sizeof(Jugador);
    return cant;
}

void mostrar_jugador(Jugador reg){

 cout<<left;
    cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) <<"|Goles "<< setw(15) <<"|Asistencias "<< setw(20) <<"|Tarjetas amarillas "<< setw(20) <<"|Tarjetas rojas ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;

    cout << left;
    cout << setw(15);
    cout << reg.getNombre();
    cout << setw(15) ;
    cout << reg.getApellido();
    cout << setw(15) ;
    cout << reg.getCant_goles();
    cout << setw(15);
    cout << reg.getAsistencias();
    cout << setw(20);
    cout << reg.getTarjeta_amarilla();
    cout << setw(20);
    cout << reg.getTarjeta_roja();

    cout<<endl;
}

void mostrar_goleadores(Jugador *v){


    int i, c=0;
    cout<<endl;
    cout<<"-----------TABLA DE GOLEADORES-----------";
    cout<<endl<<endl;

    cout<<left;
    cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) <<"|Goles ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;



       for(i=0;i<10;i++){

            if(v[i].getCant_goles()>0){

                cout << left;
                cout << setw(16);
                cout << v[i].getNombre();
                cout << setw(15) ;
                cout << v[i].getApellido();
                cout << setw(10) ;
                cout << v[i].getCant_goles();
                cout<<endl;
                c++;
                }}

           if(c==0){
            cout<<"Aun no hay goleadores"<<endl;


           }
                return;

}

void mostrar_asistencias(Jugador *v){


    int i, c=0;
    cout<<endl;
    cout<<"-----------TABLA DE ASISTIDORES-----------";
    cout<<endl;

    cout<<left;
    cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) <<"|Asistencias ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;

       for(i=0;i<10;i++){

            if(v[i].getAsistencias()>0){

                cout << left;
                cout << setw(16);
                cout << v[i].getNombre();
                cout << setw(15) ;
                cout << v[i].getApellido();
                cout << setw(10) ;
                cout << v[i].getAsistencias();
                cout<<endl;
                c++;
                }}

           if(c==0){
            cout<<"Aun no hay asistidores"<<endl;


           }

                return;

}

void mostrar_amarillas(Jugador *v){


    int i, c=0;
    cout<<endl;
    cout<<"-----------TARJETAS AMARILLAS-----------";
    cout<<endl<<endl;

    cout<<left;
    cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(19) <<"|Tarjetas amarillas ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;

       for(i=0;i<10;i++){

            if(v[i].getTarjeta_amarilla()>0){

                cout << left;
                cout << setw(16);
                cout << v[i].getNombre();
                cout << setw(15) ;
                cout << v[i].getApellido();
                cout << setw(10) ;
                cout << v[i].getTarjeta_amarilla();
                cout<<endl;
                c++;
                }}

           if(c==0){
            cout<<"Aun no hay tarjetas amarillas"<<endl;


           }

                return;

}

void mostrar_rojas(Jugador *v){


    int i, c=0;
    cout<<endl;
    cout<<"-----------TARJETAS ROJAS-----------";
    cout<<endl<<endl;

    cout<<left;
    cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(19) <<"|Tarjetas rojas ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;

       for(i=0;i<10;i++){

            if(v[i].getTarjeta_roja()>0){

                cout << left;
                cout << setw(16);
                cout << v[i].getNombre();
                cout << setw(15) ;
                cout << v[i].getApellido();
                cout << setw(10) ;
                cout << v[i].getTarjeta_roja();
                cout<<endl;
                c++;
                }}

           if(c==0){


            cout<<setw(20)<<"Aun no hay tarjetas rojas"<<endl;


           }




                return;

}


void tabla_goleadores(){


    int cant,i,j,posmax;
    Jugador *v,aux;

    cant=cantidad_jugadores();

    v=new Jugador[cant];

        FILE *p;
        p = fopen(FILE_JUGADORES, "rb");
        fread(v, sizeof(Jugador), cant, p);
        fclose(p);

        for(i=0; i<cant-1; i++){
        posmax = i;
        for(j=i+1; j<cant; j++){
            if (v[j].getCant_goles() > v[posmax].getCant_goles()){
                posmax = j;
            }
        }
        aux = v[i];
        v[i] = v[posmax];
        v[posmax] = aux;
    }
    mostrar_goleadores(v);

delete []v;

return;

}


void tabla_asistidores(){


    int cant,i,j,posmax;
    Jugador *v,aux;

    cant=cantidad_jugadores();

    v=new Jugador[cant];

        FILE *p;
        p = fopen(FILE_JUGADORES, "rb");
        fread(v, sizeof(Jugador), cant, p);
        fclose(p);

        for(i=0; i<cant-1; i++){
        posmax = i;
        for(j=i+1; j<cant; j++){
            if (v[j].getAsistencias() > v[posmax].getAsistencias()){
                posmax = j;
            }
        }
        aux = v[i];
        v[i] = v[posmax];
        v[posmax] = aux;
    }
    mostrar_asistencias(v);

delete []v;

return;

}

void tabla_amarillas(){


    int cant,i,j,posmax;
    Jugador *v,aux;

    cant=cantidad_jugadores();

    v=new Jugador[cant];

        FILE *p;
        p = fopen(FILE_JUGADORES, "rb");
        fread(v, sizeof(Jugador), cant, p);
        fclose(p);

        for(i=0; i<cant-1; i++){
        posmax = i;
        for(j=i+1; j<cant; j++){
            if (v[j].getTarjeta_amarilla() > v[posmax].getTarjeta_amarilla()){
                posmax = j;
            }
        }
        aux = v[i];
        v[i] = v[posmax];
        v[posmax] = aux;
    }
    mostrar_amarillas(v);

delete []v;

return;

}

void tabla_rojas(){
    int cant,i,j,posmax;
    Jugador *v,aux;

    cant=cantidad_jugadores();

    v=new Jugador[cant];

        FILE *p;
        p = fopen(FILE_JUGADORES, "rb");
        fread(v, sizeof(Jugador), cant, p);
        fclose(p);

        for(i=0; i<cant-1; i++){
        posmax = i;
        for(j=i+1; j<cant; j++){
            if (v[j].getTarjeta_roja() > v[posmax].getTarjeta_roja()){
                posmax = j;
            }
        }
        aux = v[i];
        v[i] = v[posmax];
        v[posmax] = aux;
    }
    mostrar_rojas(v);

delete []v;

return;

}

void buscar_jugador() {

	Jugador reg;
	bool encontrado=false;
	char nombre_jugador[30], apellido_jugador[30];
	cout<<"Ingrese el nombre del jugador a buscar: ";
	cin>>nombre_jugador;
	strupr(nombre_jugador);
	cout<<endl;
	cout<<"Ingrese el apellido del jugador a buscar: ";
	cin>>apellido_jugador;
    strupr(apellido_jugador);
    cout<<endl;

	FILE* f;
	f = fopen(FILE_JUGADORES, "rb");
	if (f == NULL) {
		return;
	}
        cout << endl << "    JUGADOR ENCONTRADO"<<endl<<endl;

        cout << left;
        cout << setw(17) << "Equipo " << setw(17) << "|Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posición " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
        cout << endl << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	while (fread(&reg, sizeof(Jugador), 1, f)) {
		if (strcmp(nombre_jugador,reg.getNombre())==0 && strcmp(apellido_jugador, reg.getApellido())==0 ) {


            reg.mostrar();
            //mostrar_jugador(reg);
            encontrado=true;

			fclose(f);
			return;
		}
	}

	if(encontrado==false){
        cout<<"El jugador no existe"<<endl;

	}

	fclose(f);
	return;
}
