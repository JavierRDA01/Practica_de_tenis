//Rishi Pursnani Mirpuri y Javier Ramírez de Andrés
//Version 3
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>

using namespace std;

const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;
const int LIM_SUP_VEL = 3;
const int LIM_SUP_HAB = 3;
const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;
const int JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
const int DIM_ARRAY_TENISTAS = 10;
bool JUEGO_ALEATORIO = false;
bool MODO_DEBUG = true;

enum tPuntosJuego { NADA, QUINCE, TREINTA, CUARENTA, VENTAJA };

typedef int tConteoGolpes[DIM_ARRAY_GOLPES];

struct tDatosTenista
{
	string iniciales;
	int habilidad;
	int velocidad;
	int partidosGanados;
	int partidosPerdidos;
};

typedef tDatosTenista tArray[DIM_ARRAY_TENISTAS];
struct tDatosPartido
{
	int posicion;
	int puntos;
	int juegos;
	int golpesGanadores;
	tConteoGolpes golpes;
};
struct tListaTenistas
{
	tDatosTenista datos[DIM_ARRAY_TENISTAS];
	int contador = 0;
};

int menu();

bool cargar(tListaTenistas& listaT);

void mostrar(const tListaTenistas& listaT);






int main()
{
	tListaTenistas listaDeTenistas;
	int opcionMenu;
	//opcionMenu = menu();
	cargar(listaDeTenistas);
	mostrar(listaDeTenistas);

	return 0;
}



int menu()
{
	int opcion;
	cout << "<1> Ver datos tenistas" << endl;
	cout << "<2> Nuevo tenista" << endl;
	cout << "<3> Eliminar tenista" << endl;
	cout << "<4> Jugar partido" << endl;
	cout << "<5> Torneo semifinales/final" << endl;
	cout << "<6> Torneo top-4" << endl;
	cout << "<0> Salir" << endl;
	cout << "Opcion: ";
	cin >> opcion;
	return opcion;
}

void mostrar(const tListaTenistas& listaT)
{
	cout << setw(2) << "INI" << setw(5) << "HAB" << setw(5) << "VEL" << setw(4) << "PG" << setw(4) << "PP" << endl;
	for (int i = 0; i < listaT.contador; i++)
	{
		cout << setw(2) << listaT.datos[i].iniciales << setw(5) <<  listaT.datos[i].habilidad << setw(5) << listaT.datos[i].velocidad << setw(4) << listaT.datos[i].partidosGanados << setw(4) << listaT.datos[i].partidosPerdidos << endl;
	}
	cout << "done" << endl;
}


bool cargar(tListaTenistas &listaT)
{
	ifstream archivoLista;
	bool archivoAbierto;
	char aux;
	archivoLista.open("Tenistas.txt");
	archivoAbierto = archivoLista.is_open();
	if (!archivoAbierto)
	{
		cout << "Ha habido un error en el archivo" << endl;	
	}
	else
	{
		while (!archivoLista.eof()) 
		{
			for (int i = 0; !archivoLista.eof(); i++)
			{
				archivoLista >> listaT.datos[i].iniciales;
				archivoLista >> listaT.datos[i].habilidad;
				archivoLista >> listaT.datos[i].velocidad;
				archivoLista >> listaT.datos[i].partidosGanados;
				archivoLista >> listaT.datos[i].partidosPerdidos;
				archivoLista.get(aux);//Cada vuelta del bucle es la lectura de un jugador
				listaT.contador++;//Contamos el número de jugadores
			}
		}
		archivoLista.close();
	}
	return archivoAbierto;
}
