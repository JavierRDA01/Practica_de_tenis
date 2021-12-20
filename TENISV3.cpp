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
const int DIFERENCIA_PARA_GANAR = 2;
const int MINIMO_SET = 3;
bool JUEGO_ALEATORIO = false;
bool MODO_DEBUG = true;

typedef enum 
{
	NADA, QUINCE, TREINTA, CUARENTA, VENTAJA
}tPuntosJuego;

typedef enum 
{
	NADIE, TENISTA1, TENISTA2
}tTenista;

typedef int tConteoGolpes[DIM_ARRAY_GOLPES];

struct tDatosPartido
{
	int posicion;
	int puntos;
	int juegos;
	int golpesGanadores;
	tConteoGolpes golpes;
};

struct tDatosTenista
{
	string iniciales;
	int habilidad;
	int velocidad;
	int partidosGanados;
	int partidosPerdidos;

	tDatosPartido datosPartido;
};

typedef tDatosTenista tArray[DIM_ARRAY_TENISTAS];

struct tListaTenistas
{
	tDatosTenista datos[DIM_ARRAY_TENISTAS];
	int contador = 0;
};


int menu(); //muestra las opciones que el programa puede realizar

bool cargar(tListaTenistas& listaT); //

void guardar(const tListaTenistas& listaT); //

void mostrar(const tListaTenistas& listaT); //muestra el tenista que se le pida

void mostrarIniciales(const tListaTenistas& listaT); //muestra las iniciales de los tenistas existentes

int buscarIniciales(const tListaTenistas& listaT, string ini); //esto es para poder realizar la busqueda de cualquier jugador que se solicite

void eliminarTenista(tListaTenistas& listaT, string iniciales); //elimina el tenista solicitado

void introducirTenista(tListaTenistas& listaT); //introduce un tenista cualquiera

tDatosTenista imprimirTenista(tListaTenistas listaT, int jugador);//Imprime los datos del tenista en las iniciales elegidas

int tenistaRepetido(const tListaTenistas& listaT, string iniciales); //para localizar a ver si existe un tenista repetido

string puntosAstring(tPuntosJuego puntuacion); //transforma los puntos dados en fotma de tPuntosJuego a un string para poder visualizarlo

int elegirServicio(string nombreJugador1, string nombreJugador2);

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador); //pinta el campo con las respectivas posiciones de los jugadores y de la bola, asi como el transucrso del punto en eeste mismo

void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para); //pinta el marcador de la situacion actual y muestra el tenista al que le pertence el servicio con un *

void mostrarEstadisticas(string nombreJugador1, string nombreJugador2, tDatosTenista tenista1, tDatosTenista tenista2); //muestra las estadisticas de cada punto jugado

tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2); //

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador); //

int golpeoBola(int posicionTenista, int habilidad, string nombreGolpeador); //

tTenista lance(tTenista bolaPara, tDatosTenista& tenistaGolpea, tDatosTenista& tenistaRecibe, int& posicionBola); //

tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para); //

void actualizarGolpes(tDatosTenista& tenista, tTenista servicio, int posicionBola, tTenista ganador); //

int contarGolpesTotales(tConteoGolpes golpes_totales); //

int contarGolpesFallidos(tConteoGolpes golpes_fallados); //

double porcentajeDeAcierto(tDatosTenista tenista, int golpesTotales, int calle); //

tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para); //

tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2); //

void buscar2Jug(tListaTenistas& listaT, int indT1, int indT2);//funcion para buscar los 2 jugadores para el partido

void arrayReset(tConteoGolpes array); //una funcion que permita reiniciar cualquier array

void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4); //jugar un Torneo entre 4 personas

void seleccionarTop4(const tListaTenistas& listaT, int& indT1, int& indT2, int& indT3, int& indT4); //seleccionar los los 4 para el torneo


int main()
{
	tListaTenistas listaT;
	tDatosTenista tenista1, tenista2;
	string iniciales;
	int opcionMenu, indT1 = 0, indT2 = 0, indT3 = 0, indT4 = 0;
	cargar(listaT);
	cout << setw(3) << "SIMULADOR DE TENIS V3" << endl;

	opcionMenu = menu();

	if (opcionMenu == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (opcionMenu == 1)
	{
		mostrar(listaT);
	}
	else if (opcionMenu == 2)
	{
		introducirTenista(listaT);
	}
	else if (opcionMenu == 3)
	{
		eliminarTenista(listaT, iniciales);
	}
	else if (opcionMenu == 4)
	{
		mostrarIniciales(listaT);
		buscar2Jug(listaT, indT1, indT2);
		tenista1 = imprimirTenista(listaT, indT1);
		tenista2 = imprimirTenista(listaT, indT2);
		jugarPartido(tenista1, tenista2);
	}
	else if (opcionMenu == 5)
	{	
		jugarTorneo(listaT, indT1, indT2, indT3, indT4);
	}
	else if (opcionMenu == 6)
	{
		seleccionarTop4(listaT, indT1, indT2, indT3, indT4);
		jugarTorneo(listaT, indT1, indT2, indT3, indT4);
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
	bool palabraEncontrada = false;

	for (int i = 0; i < listaT.contador && !palabraEncontrada; i++)
	{
		if (ini == listaT.datos[i].iniciales)
		{
			posicionInicial = i;
			palabraEncontrada = true;
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

tDatosTenista imprimirTenista(tListaTenistas listaT, int jugador)
{
	tDatosTenista tenista;
	tenista.iniciales = listaT.datos[jugador].iniciales;
	tenista.habilidad = listaT.datos[jugador].habilidad;
	tenista.velocidad = listaT.datos[jugador].velocidad;
	tenista.partidosGanados = listaT.datos[jugador].partidosGanados;
	tenista.partidosPerdidos = listaT.datos[jugador].partidosPerdidos;
	tenista.datosPartido = listaT.datos[jugador].datosPartido;
	return tenista;
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

int elegirServicio()
{
	int saque;
	saque = rand() % 2;
	if (saque == 0)
	{
		//cout << "Servicio para " << nombreJugador1 << endl;
		return 1;
	}
	else if (saque == 1)
	{
		//cout << "Servicio para " << nombreJugador2 << endl;
		return 2;
	}
}

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador)
{
	cout << setw((posicionJugador1 * 2) + 2) << nombreJugador1 << endl;
	cout << "  - - - - - - - " << endl;
	cout << setw(2);
	if (bola_jugador == TENISTA1)
	{
		if (posicionBola == 0)
		{
			cout << "o| ";
		}
		for (int f = 1; f <= ANCHO_PISTA; f++)
		{
			cout << "|" << setw(2);
			if (f == posicionBola && (f <= 7 && f >= 1))
			{
				cout << "o| ";
			}
		}
		if (posicionBola == 8)
		{
			cout << " |o";
		}
		cout << endl;
		for (int a = 1; a <= (LARGO_PISTA - 1); a++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
	}
	else
	{
		for (int i = 1; i <= LARGO_PISTA; i++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
	}
	cout << "--1-2-3-4-5-6-7--" << endl;

	if (bola_jugador == TENISTA2)
	{
		for (int a = 1; a <= (LARGO_PISTA - 1); a++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
		cout << setw(2);
		if (posicionBola == 0)
		{
			cout << "o| ";
		}
		for (int f = 1; f <= ANCHO_PISTA; f++)
		{
			cout << "|" << setw(2);
			if (f == posicionBola && (f <= 7 && f >= 1))
			{
				cout << "o| ";
			}
		}
		if (posicionBola == 8)
		{
			cout << " |o";
		}
	}

	else
	{
		for (int i = 1; i <= LARGO_PISTA; i++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
	}
	cout << endl;
	cout << "  - - - - - - - " << endl;
	cout << setw(posicionJugador2 * 2 + 2) << nombreJugador2 << endl;
}

void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para)
{
	if (servicio_para == TENISTA1)
	{
		cout << setw(5) << iniciales1 << setw(2) << datos_t1.juegos << " : " << puntosAstring(tPuntosJuego(datos_t1.puntos)) << "*" << endl;
		cout << setw(5) << iniciales2 << setw(2) << datos_t2.juegos << " : " << puntosAstring(tPuntosJuego(datos_t2.puntos)) << endl;
	}
	else
	{
		cout << setw(5) << iniciales1 << setw(2) << datos_t1.juegos << " : " << puntosAstring(tPuntosJuego(datos_t1.puntos)) << endl;
		cout << setw(5) << iniciales2 << setw(2) << datos_t2.juegos << " : " << puntosAstring(tPuntosJuego(datos_t2.puntos)) << "*" << endl;
	}
}

void mostrarEstadisticas(string nombreJugador1, string nombreJugador2, tDatosTenista tenista1, tDatosTenista tenista2)  //tDatosTenista tenista
{
	int golpesTotales1 = contarGolpesTotales(tenista1.datosPartido.golpes), golpesTotales2 = contarGolpesTotales(tenista2.datosPartido.golpes);
	cout << "Estadisticas de " << tenista1.iniciales << ":" << endl;
	cout << setw(3) << "Golpes totales: " << contarGolpesTotales(tenista1.datosPartido.golpes) << endl;
	cout << setw(3) << "Golpes ganadores: " << tenista1.datosPartido.golpesGanadores << endl;
	cout << setw(3) << "Errores no forzados: " << contarGolpesFallidos(tenista1.datosPartido.golpes) << endl;
	cout << setw(3) << "Distribucion de los golpes en la pista:" << endl << endl;
	cout << setw(6) << "Calle" << setw(6) << "0" << setw(6) << "1" << setw(6) << "2" << setw(6) << "3" << setw(6) << "4" << setw(6) << "5" << setw(6) << "6" << setw(6) << "7" << setw(6) << "8" << endl;
	cout << setw(6) << "%" << setw(6) << fixed << setprecision(1) << porcentajeDeAcierto(tenista1, golpesTotales1, 0) << setw(6) << fixed << setprecision(1) << porcentajeDeAcierto(tenista1, golpesTotales1, 1) << setw(6) << fixed << setprecision(1) << porcentajeDeAcierto(tenista1, golpesTotales1, 2) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista1, golpesTotales1, 3) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista1, golpesTotales1, 4) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista1, golpesTotales1, 5) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista1, golpesTotales1, 6) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista1, golpesTotales1, 7) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista1, golpesTotales1, 8) << fixed << setprecision(1) << endl << endl;

	cout << "Estadisticas de " << tenista2.iniciales << ":" << endl;
	cout << setw(3) << "Golpes totales: " << contarGolpesTotales(tenista2.datosPartido.golpes) << endl;
	cout << setw(3) << "Golpes ganadores: " << tenista2.datosPartido.golpesGanadores << endl;
	cout << setw(3) << "Errores no forzados: " << contarGolpesFallidos(tenista2.datosPartido.golpes) << endl;
	cout << setw(3) << "Distribucion de los golpes en la pista:" << endl << endl;
	cout << setw(6) << "Calle" << setw(6) << "0" << setw(6) << "1" << setw(6) << "2" << setw(6) << "3" << setw(6) << "4" << setw(6) << "5" << setw(6) << "6" << setw(6) << "7" << setw(6) << "8" << endl;
	cout << setw(6) << "%" << setw(6) << fixed << setprecision(1) << porcentajeDeAcierto(tenista2, golpesTotales2, 0) << setw(6) << fixed << setprecision(1) << porcentajeDeAcierto(tenista2, golpesTotales2, 1) << setw(6) << fixed << setprecision(1) << porcentajeDeAcierto(tenista2, golpesTotales2, 2) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista2, golpesTotales2, 3) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista2, golpesTotales2, 4) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista2, golpesTotales2, 5) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista2, golpesTotales2, 6) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista2, golpesTotales2, 7) << fixed << setprecision(1) << setw(6) << porcentajeDeAcierto(tenista2, golpesTotales2, 8) << fixed << setprecision(1) << endl << endl;
}

tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2)
{
	if (ganador_punto == TENISTA1)
	{
		if (datos_t1.puntos == NADA)
		{
			datos_t1.puntos = QUINCE;
			return NADIE;
		}
		else if (datos_t1.puntos == QUINCE)
		{
			datos_t1.puntos = TREINTA;
			return NADIE;
		}
		else if (datos_t1.puntos == TREINTA)
		{
			datos_t1.puntos = CUARENTA;
			return NADIE;
		}
	}
	else if (ganador_punto == TENISTA2)
	{
		if (datos_t2.puntos == NADA)
		{
			datos_t2.puntos = QUINCE;
			return NADIE;
		}
		else if (datos_t2.puntos == QUINCE)
		{
			datos_t2.puntos = TREINTA;
			return NADIE;
		}
		else if (datos_t2.puntos == TREINTA)
		{
			datos_t2.puntos = CUARENTA;
			return NADIE;
		}

	}
	if (datos_t1.puntos == CUARENTA && datos_t2.puntos == CUARENTA)// Controlar deuce
	{
		if (ganador_punto == TENISTA1)
		{
			datos_t1.puntos = VENTAJA;
			return NADIE;
		}
		else if (ganador_punto == TENISTA2)
		{
			datos_t2.puntos = VENTAJA;
			return NADIE;
		}
	}
	else if (datos_t1.puntos == VENTAJA || datos_t2.puntos == VENTAJA)
	{
		if (datos_t1.puntos == VENTAJA)
		{
			if (ganador_punto == TENISTA1)
			{
				datos_t1.puntos = NADA;
				datos_t2.puntos = NADA;
				datos_t1.juegos++;
				return TENISTA1;
			}
			else
			{
				datos_t1.puntos = CUARENTA;
				datos_t2.puntos = CUARENTA;
				return NADIE;
			}
		}
		else if (datos_t2.puntos == VENTAJA)
		{
			if (ganador_punto == TENISTA2)
			{
				datos_t1.puntos = NADA;
				datos_t2.puntos = NADA;
				datos_t2.juegos++;
				return TENISTA2;
			}
			else
			{
				datos_t1.puntos = CUARENTA;
				datos_t2.puntos = CUARENTA;
				return NADIE;
			}
		}
	}
	else
	{
		if (datos_t1.puntos == CUARENTA)
		{
			datos_t1.puntos = NADA;
			datos_t2.puntos = NADA;
			datos_t1.juegos++;
			return TENISTA1;
		}
		else
		{
			if (datos_t2.puntos == CUARENTA)
			{
				datos_t1.puntos = NADA;
				datos_t2.puntos = NADA;
				datos_t2.juegos++;
			}
			return TENISTA2;
		}
	}
}

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador)
{
	int diferencia, diferenciaCasillas;
	diferencia = abs(posicionBola - posicionTenista);
	if (velocidad >= diferencia)
	{
		if (MODO_DEBUG == true)
		{
			cout << "ese ha sido un tiro sencillo" << endl;
			cout << "su rival llega a la bola" << endl;
		}
		posicionTenista = posicionBola;
		return posicionTenista;
	}
	else //En el caso de que la velocidad fuera menor que el diferencia
	{
		if (posicionBola < posicionTenista)
		{
			if (MODO_DEBUG == true)
			{
				diferenciaCasillas = posicionTenista - posicionBola;
				cout << nombreJugador << " intenta llegar por la derecha pero se queda en la posicion " << posicionTenista << " a " << diferenciaCasillas << " de su objetivo y pierde el punto" << endl;
			}
			posicionTenista = posicionTenista - velocidad;
			return posicionTenista;// Posición adelantada
		}
		else if (posicionBola > posicionTenista)
		{
			if (MODO_DEBUG == true)
			{
				diferenciaCasillas = posicionBola - posicionTenista;
				cout << nombreJugador << " intenta llegar por la izquierda pero se queda en la posicion " << posicionTenista << " a " << diferenciaCasillas << " de su objetivo y pierde el punto" << endl;
			}
			posicionTenista = posicionTenista + velocidad;
			return posicionTenista;// Posición atrasada
		}
		else
		{
			if (posicionBola < posicionTenista)
			{
				return posicionTenista;// Punto para el otro jugador
			}
		}
	}
}

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeadorBola)
{
	int diferencia, posicionDestino, acierto, desvio;
	double probabilidadExito;
	string nombreJugador1, nombreJugador2;
	desvio = rand() % 2;
	acierto = rand() % 100; // número aleatorio 0 - 100 
	cout << "Golpea " << nombreGolpeadorBola << "!" << endl;

	if (JUEGO_ALEATORIO == false) {
		cout << "Indique donde quiere tirar de la bola: "; //juego controlado por usuario
		cin >> posicionDestino;
	}

	else if (JUEGO_ALEATORIO == true) { //juego aleatorio
		srand(time(NULL));
		posicionDestino = rand() % ANCHO_PISTA + 1;
		system("PAUSE");
		cout << endl;
	}
	diferencia = abs(posicionDestino - posicion_tenista); 
	if (diferencia <= habilidad)
	{
		if (MODO_DEBUG == true)
		{
			cout << nombreGolpeadorBola << " lanza la bola a la posición " << posicionDestino << endl;
		}
		return posicionDestino;
	}
	else // Si la diferencia entre la posicion del tenista y la posicion de destino de la bola es mayor que la habilidad 
	{
		probabilidadExito = (100.0 - ((posicionDestino - habilidad) / ((ANCHO_PISTA - 1.0) - LIM_INF_HAB) * 100.0)); // porcentaje de acierto
		if (acierto <= probabilidadExito)
		{
			if (MODO_DEBUG == true)
			{
				cout << nombreGolpeadorBola << " lanza la bola a " << posicionDestino << endl;
			}
			return posicionDestino;
		}
		else
		{
			if (desvio == 0)
			{
				if (MODO_DEBUG == true)
				{
					cout << nombreGolpeadorBola << " lanza la bola a " << posicionDestino << " pero se desvía a la derecha y acaba en la posición " << posicionDestino + 1 << endl;
					cout << "es un tipo complicado con prob_acierto: " << probabilidadExito << " y el resultado es: " << acierto << endl;
				}
				return posicionDestino + 1; // Desvío a la derecha
			}
			else if (desvio == 1)
			{
				if (MODO_DEBUG == true)
				{
					cout << nombreGolpeadorBola << " lanza la bola a " << posicionDestino << " pero se desvía a la izquierda y acaba en la posicion " << posicionDestino - 1 << endl;
					cout << "es un tipo complicado con prob_acierto: " << probabilidadExito << " y el resultado es: " << acierto << endl;
				}
				return posicionDestino - 1; // Desvío a la izquierda
			}
		}

	}
}

tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& posicionBola)
{
	if (bola_para == TENISTA1)
	{
		posicionBola = golpeoBola(tenista_golpea.datosPartido.posicion, tenista_golpea.habilidad, tenista_golpea.iniciales); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
		{
			return TENISTA2; //Gana el otro jugador
		}
		else //Si mete la bola dentro del campo
		{
			tenista_recibe.datosPartido.posicion = correTenista(tenista_recibe.datosPartido.posicion, tenista_recibe.velocidad, posicionBola, tenista_recibe.iniciales);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (tenista_recibe.datosPartido.posicion == posicionBola)//Si el jugador que recibe llega
			{
				return NADIE; //Se sigue el punto
			}
			else //El jugador que recibe no llega a la bola
			{
				return TENISTA1; //Gana el jugador que golpea
			}
		}
	}
	else
	{
		posicionBola = golpeoBola(tenista_golpea.datosPartido.posicion, tenista_golpea.habilidad, tenista_golpea.iniciales); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
		{
			return TENISTA1; //Gana el otro jugador
		}
		else
		{
			tenista_recibe.datosPartido.posicion = correTenista(tenista_recibe.datosPartido.posicion, tenista_recibe.velocidad, posicionBola, tenista_recibe.iniciales);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (tenista_recibe.datosPartido.posicion == posicionBola)//Si el jugador que recibe llega
			{
				return NADIE; //Se sigue el punto
			}
			else //El jugador que recibe no llega a la bola
			{
				return TENISTA2; //Gana el jugador que golpea
			}
		}
	}
}

tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para)
{
	int pos_jugador1 = 4, pos_jugador2 = 4, posicionBola = 4; //Al principio de todos los puntos las posiciones son las mismas
	tTenista ganaPunto = NADIE, turno = servicio_para; //Al prinicipio nadie gana el punto

	pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno); //Pinta el campo inicial

	while (ganaPunto == NADIE)//Se sigue el partido mientras que nadie gane el punto 
	{
		if (turno == TENISTA1) //Si saca el tenista1
		{
			ganaPunto = lance(turno, tenista1, tenista2, posicionBola); //Hace un lance, golpeoBola() y correTenista se ejecutan. Además, se actualizan los números de golpeos
			actualizarGolpes(tenista1, TENISTA1, posicionBola, ganaPunto);
			if (ganaPunto == TENISTA1) //Si gana el punto el tenista1 se pinta la pista y devuelve que ha ganado el tenista1
			{
				turno = TENISTA2;
				pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
				cout << "Gana el punto " << tenista1.iniciales << "!" << endl;
				return TENISTA1;
			}
			else if (ganaPunto == TENISTA2)//Si gana el punto el tenista1 se pinta la pista y devuelve que ha ganado el tenista1
			{
				turno = TENISTA2;
				pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
				cout << "Gana el punto " << tenista2.iniciales << "!" << endl;
				return TENISTA2;
			}
			else //Si no gana nadie se repite el lance() pero el turno pasa al otro jugador
			{
				turno = TENISTA2;
				pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
			}
		}
		else if (turno == TENISTA2)
		{
			ganaPunto = lance(turno, tenista2, tenista1, posicionBola);
			tTenista lance(tTenista bolaPara, tDatosTenista & tenistaGolpea, tDatosTenista & tenistaRecibe, int& posicionBola);
			actualizarGolpes(tenista2, TENISTA2, posicionBola, ganaPunto);
			if (ganaPunto == TENISTA1)
			{
				turno = TENISTA1;
				pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
				cout << "Gana el punto " << tenista1.iniciales << "!" << endl;
				return TENISTA1;
			}
			else if (ganaPunto == TENISTA2)
			{
				turno = TENISTA1;
				pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
				cout << "Gana el punto " << tenista2.iniciales << "!" << endl;
				return TENISTA2;
			}
			else
			{
				turno = TENISTA1;
				pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
			}
		}
	}
}

tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para)
{
	tTenista ganadorPunto = jugarPunto(tenista1, tenista2, servicio_para);
	tPuntosJuego puntos1 = NADA, puntos2 = NADA;

	while (actualizarMarcador(ganadorPunto, tenista1.datosPartido, tenista2.datosPartido) == NADIE) // Se juegan los puntos hasta que actualizarMarcador devuelva o TENISTA1 o TENISTA2
	{
		pintarMarcador(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido, tenista2.datosPartido, servicio_para); //Muestra el marcador
		ganadorPunto = jugarPunto(tenista1, tenista2, servicio_para);
	}

	pintarMarcador(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido, tenista2.datosPartido, servicio_para);
	mostrarEstadisticas(tenista1.iniciales, tenista2.iniciales, tenista1, tenista2); //Al final de cada juego muestra las estadísticas
	return ganadorPunto;
}

tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2)
{
	tTenista ganadorJuego = NADIE, ganadorPartido = NADIE, servicio = tTenista(elegirServicio());
	int puntos1 = 0, puntos2 = 0, absoluto = 0;
	absoluto = abs(puntos1 - puntos2);
	while ((puntos1 < MINIMO_SET && puntos2 < MINIMO_SET) || (absoluto < DIFERENCIA_PARA_GANAR)) //Hasta que uno de los dos llegue a 3 puntos y hasta que haya una diferencia de 2
	{
		ganadorJuego = jugarJuego(tenista1, tenista2, servicio);
		
			if (ganadorJuego == TENISTA1)
			{
				puntos1++;
			}
			else
			{
				puntos2++;
			}
			if (servicio == TENISTA1)
			{
				servicio = TENISTA2;
			}
			else
			{
				servicio = TENISTA1;
			}
		absoluto = abs(puntos1 - puntos2);
	}
	if (puntos1 > puntos2)
	{
		ganadorPartido = TENISTA1;
	}
	else
	{
		ganadorPartido = TENISTA2;
	}
	return ganadorPartido;
}

void actualizarGolpes(tDatosTenista& datos_tenista, tTenista servicio, int posicionBola, tTenista ganador)
{
	datos_tenista.datosPartido.golpes[posicionBola]++; //Se suma un golpe en la dirección a la que haya ido la bola
	if (servicio == ganador)
	{
		datos_tenista.datosPartido.golpesGanadores++; //Si el que golpea la bola gana el punto se suma uno a golpes ganados
	}
}

int contarGolpesTotales(tConteoGolpes golpes_totales)
{
	int sumaDeGolpes = 0;
	for (int i = 0; i < DIM_ARRAY_GOLPES; i++)
	{
		sumaDeGolpes = sumaDeGolpes + golpes_totales[i];
	}
	return sumaDeGolpes;
}

int contarGolpesFallidos(tConteoGolpes golpes_fallados)
{
	int golpesTotales = contarGolpesTotales(golpes_fallados), sumaDeGolpesDentro = 0;
	for (int i = 1; i < ANCHO_PISTA + 1; i++)
	{
		sumaDeGolpesDentro = sumaDeGolpesDentro + golpes_fallados[i];
	}
	return (golpesTotales - sumaDeGolpesDentro);
}

double porcentajeDeAcierto(tDatosTenista tenista, int golpesTotales, int calle)
{
	double golpesCalle = tenista.datosPartido.golpes[calle];
	double porcentaje;
	porcentaje = (golpesCalle / golpesTotales) * 100;
	return porcentaje;
}

void buscar2Jug(tListaTenistas& listaT, int indT1, int indT2)
{
	string iniciales1, iniciales2;
	cout << "introduce las iniciales del tenista1: ";
	cin >> iniciales1;
	indT1 = buscarIniciales(listaT, iniciales1);

	while (indT1 < 0)
	{
		cout << "vuelva a introducir las iniciales del tenista1: ";
		cin >> iniciales1;
		indT1 = buscarIniciales(listaT, iniciales1);
	}

	cout << "introduce las iniciales del tenista2: ";
	cin >> iniciales2;
	indT2 = buscarIniciales(listaT, iniciales2);


	while ((iniciales2 == listaT.datos[indT1].iniciales) || (indT2 < 0))
	{
		cout << "vuelva a introducir las iniciales del tenista2: ";
		cin >> iniciales2;
		indT2 = buscarIniciales(listaT, iniciales2);
	}
}



void arrayReset(tConteoGolpes array)
{
	for (int i = 0; i < (DIM_ARRAY_GOLPES - 1); i++)
	{
		array[i] = 0;
	}
}

void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4)
{
	int partido1, partido2, partido3; //enteros para indicar los ganadores de los partidos

	cout << "comienzan las semifinales!!" << endl;
	cout << "Primer partido: " << listaT.datos[indT1].iniciales << " ENFRENTADO A " << listaT.datos[indT4].iniciales << endl;
	cout << "Segundo partido: " << listaT.datos[indT2].iniciales << " ENFRENTADO A " << listaT.datos[indT3].iniciales << endl;

	if (jugarPartido(listaT.datos[indT1], listaT.datos[indT4]) == tTenista(1))
	{
		partido1 = indT1;
		cout << "el primer partido lo ha ganado: " << listaT.datos[indT1].iniciales << endl;
	}
	else
	{
		partido1 = indT4;
		cout << "el primer partido lo ha ganado: " << listaT.datos[indT4].iniciales << endl;
	}

	if (jugarPartido(listaT.datos[indT2], listaT.datos[indT3]) == tTenista(1))
	{
		partido2 = indT2;
		cout << "el segundo partido lo ha ganado: " << listaT.datos[indT2].iniciales << endl;
	}
	else
	{
		partido3 = indT3;
		cout << "el segundo partido lo ha ganado: " << listaT.datos[indT3].iniciales << endl;
	}

	cout << "la final sera entre: " << listaT.datos[partido1].iniciales << " y " << listaT.datos[partido2].iniciales << "!!!" << endl;

	if (jugarPartido(listaT.datos[partido1], listaT.datos[partido2]) == tTenista(1))
	{
		partido3 = partido1;
	}
	else
	{
		partido3 = partido2;
	}

	cout << "el ganador ha sido: " << listaT.datos[partido3].iniciales << endl;

	//guardar(listaT);
}

void seleccionarTop4(const tListaTenistas& listaT, int& indT1, int& indT2, int& indT3, int& indT4)
{
	int  PGmayor1 = listaT.datos[0].partidosGanados, PGmayor2 = listaT.datos[0].partidosGanados, PGmayor3 = listaT.datos[0].partidosGanados, PGmayor4 = listaT.datos[0].partidosGanados;
	for (int i = 0; i < listaT.contador; i++)//Inicio del bucle del jugador con mas partidos ganados
	{
		if (PGmayor1 < listaT.datos[i].partidosGanados) // Recorre todos los partidos ganados y se queda con el mayor numero de partidos ganados
		{
			PGmayor1 = listaT.datos[i].partidosGanados;
			indT1 = i;
		}
	}
	//Fin del bucle 1
	if (indT1 == 0)
	{
		PGmayor2 = listaT.datos[1].partidosGanados;//El bucle empieza en el cuarto jugador en el caso de que el mayores sea el primero
	}
	for (int i = 0; i < listaT.contador; i++)//Inicio del bucle del jugador 2 con mas partidos ganados
	{

		if (PGmayor2 < listaT.datos[i].partidosGanados && i != indT1)//Recorre todos los partidos ganados y se queda con el mayor numero de partidos ganados pero sin contar con jugador1
		{
			PGmayor2 = listaT.datos[i].partidosGanados;
			indT2 = i;
		}
	}
	//Fin del bucle 2
	if ((indT1 == 0 && indT2 == 1) || (indT2 == 0 && indT1 == 1))//Si los mayores son los dos primeros.Son permutaciones sin repeticion por lo que las posibilidades son 2!
	{
		PGmayor3 = listaT.datos[2].partidosGanados;
	}
	else if (indT1 == 0 || indT2 == 0)//Si el mayor es el primero
	{
		PGmayor3 = listaT.datos[1].partidosGanados;
	}
	for (int i = 0; i < listaT.contador; i++)//Inicio del bucle del jugador 3 con mas partidos ganados
	{
		if (PGmayor3 < listaT.datos[i].partidosGanados && i != indT1 && i != indT2)//Recorre todos los partidos ganados y se queda con el mayor numero de partidos ganadospero sin contar con jugador1 y jugador2
		{
			PGmayor3 = listaT.datos[i].partidosGanados;
			indT3 = i;
		}
	}
	//Fin del bucle 3
	if ((indT1 == 0 && indT2 == 1 && indT3 == 2) || (indT1 == 0 && indT2 == 2 && indT3 == 1) || (indT1 == 1 && indT2 == 0 && indT3 == 2) || (indT1 == 1 && indT2 == 2 && indT3 == 0) || (indT1 == 2 && indT2 == 1 && indT3 == 0) || (indT1 == 2 && indT2 == 0 && indT3 == 1))
		//El bucle empieza en el cuarto jugador en el caso de que los tres mayores sean los tres primeros. Son permutaciones sin repeticion por lo que las posibilidades son 3!
	{
		PGmayor4 = listaT.datos[3].partidosGanados;
	}
	else if ((indT1 == 0 && indT2 == 1) || indT1 == 0 && indT3 == 1 || (indT1 == 1 && indT2 == 0) || (indT1 == 1 && indT3 == 1) || (indT2 == 0 && indT3 == 1) || (indT2 == 1 && indT3 == 0))
		//Si los mayores son solo dos. Se trataria de variaciones de 3 elementos con dos posiciones sin repeticion por lo que seria 3!/1! que son 6 posibilidades distintas
	{
		PGmayor4 = listaT.datos[2].partidosGanados;
	}
	else if (indT1 == 0 || indT2 == 0 || indT3 == 0)//Si el mayor es uno de los tres pero los siguientes no lo son
	{
		PGmayor4 = listaT.datos[1].partidosGanados;
	}
	for (int i = 0; i < listaT.contador; i++)//Inicio del bucle del jugador 4 con mas partidos ganados
	{
		if (PGmayor4 < listaT.datos[i].partidosGanados && i != indT1 && i != indT2 && i != indT3)//Recorre todos los partidos ganados y se queda con el mayor numero de partidos ganadospero sin contar con jugador1, jugador2 y jugador3
		{
			PGmayor4 = listaT.datos[i].partidosGanados;
			indT4 = i;
		}
	}
}
