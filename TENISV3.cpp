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

enum tPuntosJuego
{
	NADA, QUINCE, TREINTA, CUARENTA, VENTAJA
};

enum tTenista
{
	NADIE, TENISTA1, TENISTA2
};

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

void guardar(const tListaTenistas& listaT);

void mostrar(const tListaTenistas& listaT);

void mostrarIniciales(const tListaTenistas& listaT);

int buscarIniciales(const tListaTenistas& listaT, string ini);

void eliminarTenista(tListaTenistas& listaT, string iniciales);

void introducirTenista(tListaTenistas& listaT);

int tenistaRepetido(const tListaTenistas& listaT, string iniciales);

string puntosAstring(tPuntosJuego puntuacion);

int elegirServicio(string nombreJugador1, string nombreJugador2);

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador);

int golpeoBola(int posicionTenista, int habilidad, string nombreGolpeador);

tTenista lance(tTenista bolaPara, tDatosTenista& tenistaGolpea, tDatosTenista& tenistaRecibe, int& posicionBola);


int main()
{
	tListaTenistas listaDeTenistas, listaT;
	string iniciales;
	int opcionMenu;
	opcionMenu = menu();

	if (opcionMenu == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (opcionMenu == 1)
	{
		mostrar( listaT);
	}
	else if (opcionMenu == 2)
	{
		introducirTenista(listaDeTenistas);
	}
	else if (opcionMenu == 3)
	{
		eliminarTenista(listaT, iniciales);
	}
	else if (opcionMenu == 4)
	{

	}
	else if (opcionMenu == 5)
	{

	}
	else if (opcionMenu == 6)
	{

	}
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


bool cargar(tListaTenistas& listaT)
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

void guardar(const tListaTenistas& listaT)
{
	ofstream archivoLista;
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
		for (int i = 0; i < (listaT.contador - 1); i++)
		{
			archivoLista << listaT.datos[i].iniciales << " " << listaT.datos[i].habilidad << " " << listaT.datos[i].velocidad << " " << listaT.datos[i].partidosGanados << " " << listaT.datos[i].partidosPerdidos << endl;
		}
		archivoLista << listaT.datos[listaT.contador - 1].iniciales << " " << listaT.datos[listaT.contador - 1].habilidad << " " << listaT.datos[listaT.contador - 1].velocidad << " " << listaT.datos[listaT.contador - 1].partidosGanados << " " << listaT.datos[listaT.contador - 1].partidosPerdidos;

	}
	archivoLista.close();
}
void mostrar(const tListaTenistas& listaT)
{
	cout << setw(2) << "INI" << setw(5) << "HAB" << setw(5) << "VEL" << setw(4) << "PG" << setw(4) << "PP" << endl;
	for (int i = 0; i < listaT.contador; i++)
	{
		cout << setw(2) << listaT.datos[i].iniciales << setw(5) << listaT.datos[i].habilidad << setw(5) << listaT.datos[i].velocidad << setw(4) << listaT.datos[i].partidosGanados << setw(4) << listaT.datos[i].partidosPerdidos << endl;
	}
}



void mostrarIniciales(const tListaTenistas& listaT)
{
	cout << "Iniciales de los tenistas: " << listaT.datos[0].iniciales;
	for (int i = 1; i < listaT.contador; i++)
	{
		cout << " - " << listaT.datos[i].iniciales;
	}
	cout << endl;
}

int buscarIniciales(const tListaTenistas& listaT, string ini)
{
	int posicionInicial = -1;
	for (int i = 0; i < listaT.contador; i++)
	{
		if (ini == listaT.datos[i].iniciales)
		{
			posicionInicial = i;
			return posicionInicial;
		}
		else
		{
			posicionInicial = -1;
		}
	}
	return posicionInicial;
}

void eliminarTenista(tListaTenistas& listaT, string iniciales)
{
	int posicion;
	posicion = buscarIniciales(listaT, iniciales);
	if (posicion != -1)
	{
		cout << listaT.contador << endl;
		for (int i = posicion; i < (listaT.contador - 1); i++)
		{
			listaT.datos[i].iniciales = listaT.datos[i + 1].iniciales;
			listaT.datos[i].habilidad = listaT.datos[i + 1].habilidad;
			listaT.datos[i].velocidad = listaT.datos[i + 1].velocidad;
			listaT.datos[i].partidosGanados = listaT.datos[i + 1].partidosGanados;
			listaT.datos[i].partidosPerdidos = listaT.datos[i + 1].partidosPerdidos;
		}
		listaT.contador--;
	}
	else
	{
		cout << "No hay ningun tenista con esas iniciales" << endl;
	}
}

void introducirTenista(tListaTenistas& listaT)
{
	int velocidad, habilidad;
	string iniciales;
	if (listaT.contador < 10)
	{
		cout << "Introduce las iniciales del tenista (deben ser 3 iniciales): ";
		cin >> iniciales;
		while (iniciales.length() != 3)
		{
			cout << "Debe introducir solo 3 iniciales, por favor vuelva a introducir las iniciales del jugador: ";
			cin >> iniciales;
		}
		cout << "Introduce la habilidad del jugador (Intervalo 1-3): ";
		cin >> habilidad;
		while (habilidad < 1 || habilidad > 3)
		{
			cout << "Valores incorrectos, introduzca de nuevo la habilidad del jugador (Intervalo 1-3): ";
			cin >> habilidad;
		}
		cout << "Introduce la velocidad del jugador (Intervalo 1-3): ";
		cin >> velocidad;
		while (velocidad < 1 || velocidad > 3)
		{
			cout << "Valores incorrectos, introduzca de nuevo la velocidad del jugador (Intervalo 1-3): ";
			cin >> velocidad;
		}
		listaT.datos[listaT.contador].iniciales = iniciales;
		listaT.datos[listaT.contador].habilidad = habilidad;
		listaT.datos[listaT.contador].velocidad = velocidad;
		listaT.datos[listaT.contador].partidosGanados = 0;
		listaT.datos[listaT.contador].partidosPerdidos = 0;
		listaT.contador++;
	}
	else
	{
		cout << "No hay espacio suficiente para el tenista, primero debe eliminar un tenista" << endl;
	}
}

int tenistaRepetido(const tListaTenistas& listaT, string iniciales)
{
	int posicion;
	posicion = buscarIniciales(listaT, iniciales);
	if (posicion != -1)
	{
		cout << "Tenista repetido. Elija otro" << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

string puntosAstring(tPuntosJuego puntuacion)
{
	string puntos;
	if (puntuacion == NADA)
	{
		puntos = "00";
	}
	else if (puntuacion == QUINCE)
	{
		puntos = "15";
	}
	else if (puntuacion == TREINTA)
	{
		puntos = "30";
	}
	else if (puntuacion == CUARENTA)
	{
		puntos = "40";
	}
	else if (puntuacion == VENTAJA)
	{
		puntos = "[AD]";
	}
	return puntos;
}

int elegirServicio(string nombreJugador1, string nombreJugador2)
{
	int saque;
	saque = rand() % 2;
	if (saque == 0)
	{
		cout << "Servicio para " << nombreJugador1 << endl;
		return 1;
	}
	else if (saque == 1)
	{
		cout << "Servicio para " << nombreJugador2 << endl;
		return 2;
	}
}
