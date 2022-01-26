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
const int LIM_SUP_VEL = 4;
const int LIM_SUP_HAB = 5;
const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;
const int JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
const int DIM_ARRAY_TENISTAS = 10;
const int DIFERENCIA_PARA_GANAR = 2;
const int MINIMO_SET = 3;
const int JUGADORES_FINAL = 2;
bool JUEGO_ALEATORIO = true;
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
	int posicion = 4;
	tPuntosJuego puntos = NADA;
	int juegos = 0;
	int golpesGanadores = 0;

	tConteoGolpes golpes;
};

struct tDatosTenista
{
	string iniciales;
	int habilidad = 0;
	int velocidad = 0;
	int partidosGanados = 0;
	int partidosPerdidos = 0;

	tDatosPartido datosPartido;
};

typedef tDatosTenista tArray[DIM_ARRAY_TENISTAS];

struct tListaTenistas
{
	tArray datos;
	int contador = 0;
};


int menu(); //Muestra las opciones que el programa puede realizar

int introducirDato(string datoString);

string introducirNombre(tListaTenistas& listaT);

bool cargar(tListaTenistas& listaT); //Carga el arvhivo .txt

void guardar(const tListaTenistas& listaT); //Guarda la informacón actual en el archivo .txt

void mostrar(const tListaTenistas& listaT); //Muestra la lista de tenistas, mostrando su velocidad, habilidad, partidos perdidos y partidos ganados

void mostrarIniciales(const tListaTenistas& listaT); //Muestra las iniciales de todos los tenistas disponibles

int buscarIniciales(const tListaTenistas& listaT, string ini); //Busca en la lista las iniciales y devuelve un numero con la posicion del tenista con esas iniciales o un -1 si no se han encontrado las iniciales

void pintarCampo(tTenista bola_jugador, int posicionBola, tTenista jugador);

void eliminarTenista(tListaTenistas& listaT); //Elimina el tenista introducido de la lista

void introducirTenista(tListaTenistas& listaT); //Introduce un tenista nuevo

string puntosAstring(tPuntosJuego puntuacion); //Transforma los puntos dados en fotma de tPuntosJuego a un string para poder visualizarlo

int elegirServicio(string nombreJugador1, string nombreJugador2); //Escoge al azar quien saca

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador); //Pinta el campo con las respectivas posiciones de los jugadores y de la bola, asi como el transucrso del punto en eeste mismo

void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para); //Pinta el marcador de la situacion actual y muestra el tenista al que le pertence el servicio con un *

void mostrarEstadistica(string nombreJugador, const tDatosTenista tenista);

void mostrarEstadisticas(string nombreJugador1, string nombreJugador2, tDatosTenista tenista1, tDatosTenista tenista2); //Muestra las estadisticas de cada punto jugado

tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2); //Registra quien ha ganado un punto o un juego y los suma al marcador

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador); //El tenista corre hacia la direccion de la bola

int golpeoBola(int posicionTenista, int habilidad, string nombreGolpeador); //La bola es lanzada hacia una posicion del campo y depende de la habilidad

tTenista lance(tTenista bolaPara, tDatosTenista& tenistaGolpea, tDatosTenista& tenistaRecibe, int& posicionBola); //Se ejecuta un golpeoBola() del jugador que golpea y un correTenista() del jugador que recibe. Devuelve al ganador del punto

tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para); //Ejecuta lance() hasta que hay un ganador del punto

tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para); //Ejecuta jugarPunto() hasta que haya un ganador del juego

tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2); //Se juega un partido entero hasta que alguien gane el set

void buscar2Jug(tListaTenistas& listaT, int& indT1, int& indT2);//Busca dos jugadores para un partido simple

void buscar4Jug(tListaTenistas& listaT, int& indT1, int& indT2, int& indT3, int& indT4);//Busca 4 jugadores para jugar un torneo

void actualizarGolpes(tDatosTenista& tenista, tTenista servicio, int posicionBola, tTenista ganador); //Registra donde ha golpeado la bola el tenista, tambien registra si la bola lanzada es una bola ganada

int contarGolpesTotales(const tDatosTenista tenista); //Cuenta los golpes totales de un jugador en lo que lleva de partido

int contarGolpesFallidos(const tDatosTenista tenista); //Cuenta los golpes totales fallidos de un jugador en lo que lleva de partido

double porcentajeDeGolpeo(const tDatosTenista tenista, double golpesTotales, int calle); //Registra el porcentaje de Golpeo hacia una sola calle

void arrayReset(tConteoGolpes& array); //Resetea los arrays para un partido nuevo

void resetearGolpesGanadores(tDatosTenista& tenista);//Resetea los golpesGanadores para un partido nuevo

void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4); //Juega un torneo entre 4 personas

void seleccionarTop4(const tListaTenistas& listaT, int& indT1, int& indT2, int& indT3, int& indT4); //Selecciona los 4 mejores jugadores del archivo .txt

void resetearJugadoresTorneo(tListaTenistas& listaT, int jugador);//Selecciona a los jugadores que han ganado en semifinales para jugar la final

void pintarLineaMedio();

void pintarJugador(int posicionJugador, string nombreJugador, tTenista tenista);



int main()
{
	tListaTenistas listaT;
	tDatosTenista tenista1, tenista2;
	string iniciales;
	int opcionMenu, indT1 = 0, indT2 = 0, indT3 = 0, indT4 = 0;
	cargar(listaT);
	if (MODO_DEBUG == false) {

		srand(time(NULL));
	}
	else {

		srand(0);
	}
	cout << endl;
	cout << setw(36) << "<|" << setw(45) << "|>" << endl;
	cout << setw(36) << "|" << setw(44) << "|" << endl;
	cout << setw(36) << " |" << "[---BIENVENIDO AL SIMULADOR DE TENIS V3---]" << "|" << endl << endl;
	do
	{
		
		cout << "Elija una opcion:" << endl << endl;
		opcionMenu = menu();

		if (opcionMenu == 1)
		{
			mostrar(listaT);
		}
		else if (opcionMenu == 2)
		{
			introducirTenista(listaT);
			guardar(listaT);
		}
		else if (opcionMenu == 3)
		{
			eliminarTenista(listaT);
			guardar(listaT);
		}
		else if (opcionMenu == 4)
		{
			mostrarIniciales(listaT);
			buscar2Jug(listaT, indT1, indT2);
			jugarPartido(listaT.datos[indT1], listaT.datos[indT2]);
		}
		else if (opcionMenu == 5)
		{
			mostrarIniciales(listaT);
			buscar4Jug(listaT, indT1, indT2, indT3, indT4);
			jugarTorneo(listaT, indT1, indT2, indT3, indT4);
		}
		else if (opcionMenu == 6)
		{
			seleccionarTop4(listaT, indT1, indT2, indT3, indT4);
			jugarTorneo(listaT, indT1, indT2, indT3, indT4);
		}
	} while (opcionMenu >= 1 && opcionMenu <= 6);
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
	cout << endl;
	return opcion;
}

int introducirDato(string datoString)
{
	int dato;
	cout << "Introduce la " << datoString << " del tenista ( valor entre ";
	if(datoString == "habilidad")
	{
		cout << LIM_INF_HAB << " y " << LIM_SUP_HAB;
	}
	else
	{
		cout << LIM_INF_VEL << " y " << LIM_SUP_VEL;
	}
	cout << "): ";
	cin >> dato;
	if(datoString == "habilidad")
	{
		while (dato < LIM_INF_HAB || dato > LIM_SUP_HAB)
		{
			cout << "Valores incorrectos, introduzca de nuevo la habilidad del jugador (valor entre " << LIM_INF_HAB << " y " << LIM_SUP_HAB << "): ";
			cin >> dato;
		}
	}
	else
	{
		while (dato < LIM_INF_VEL || dato > LIM_SUP_VEL)
		{
			cout << "Valores incorrectos, introduzca de nuevo la habilidad del jugador (valor entre " << LIM_INF_VEL << " y " << LIM_SUP_VEL << "): ";
			cin >> dato;
		}
	}
	return dato;
}
string introducirNombre(tListaTenistas& listaT) 
{
	string iniciales;
	int inicialesRepetidas = 0;
	cout << "Introduce las iniciales del tenista (deben ser 3 iniciales): ";
	cin >> iniciales;
	do
	{
		inicialesRepetidas = buscarIniciales(listaT, iniciales);
		if (iniciales.length() != 3)
		{
			cout << "Debe introducir solo 3 iniciales, por favor vuelva a introducir las iniciales del jugador: ";
			cin >> iniciales;
			inicialesRepetidas = buscarIniciales(listaT, iniciales);
		}
		if (inicialesRepetidas != -1)
		{
			cout << "Tenista repetido. Elija otro: ";
			cin >> iniciales;
			inicialesRepetidas = buscarIniciales(listaT, iniciales);
		}
	} while (iniciales.length() != 3 || inicialesRepetidas != -1);
	return iniciales;
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
	cout << endl;
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

void eliminarTenista(tListaTenistas& listaT)
{
	int posicion;
	string inicialesTenista;
	cout << "Introduzca las iniciales del tenista que desee eliminar: ";
	cin >> inicialesTenista;
	posicion = buscarIniciales(listaT, inicialesTenista);
	if (posicion != -1)
	{
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
	int velocidad = 0, habilidad = 0;
	string iniciales;
	if (listaT.contador < 10)
	{
		
		iniciales = introducirNombre(listaT);
		habilidad = introducirDato("habilidad");
		velocidad = introducirDato("velocidad");
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
	int saque, servicio;
	saque = rand() % 2;
	if (saque == 0)
	{
		servicio = 1;
	}
	else
	{
		servicio = 2;
	}
	return servicio;
}

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador)
{
	pintarJugador(posicionJugador1, nombreJugador1, TENISTA1);
	pintarCampo(bola_jugador, posicionBola, TENISTA1);
	pintarLineaMedio();
	pintarCampo(bola_jugador, posicionBola, TENISTA2);
	pintarJugador(posicionJugador2, nombreJugador2, TENISTA2);
}
void pintarJugador(int posicionJugador, string nombreJugador, tTenista tenista)
{
	if(tenista == TENISTA1)
	{
		cout << setw((posicionJugador * 2) + 2) << nombreJugador << endl;
		cout << "  - - - - - - - " << endl;
		cout << setw(2);
	}
	else
	{
		cout << endl;
		cout << "  - - - - - - - " << endl;
		cout << setw(posicionJugador * 2 + 2) << nombreJugador << endl;
	}
}
void pintarCampo(tTenista bola_jugador, int posicionBola, tTenista jugador)
{
	if (bola_jugador == jugador)
	{
		if (bola_jugador == TENISTA1)
		{
			if (posicionBola == 0)
			{
				cout << "o| ";
			}
			for (int f = 1; f <= ANCHO_PISTA; f++)
			{
				cout << "|" << setw(2);
				if (f == posicionBola && (f <= ANCHO_PISTA && f >= 1))
				{
					cout << "o| ";
				}
			}
			if (posicionBola >= ANCHO_PISTA + 1)
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
				if (f == posicionBola && (f <= ANCHO_PISTA && f >= 1))
				{
					cout << "o| ";
				}
			}
			if (posicionBola >= ANCHO_PISTA + 1)
			{
				cout << " |o";
			}
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
}

void pintarLineaMedio()
{
	cout << "-";
	for(int i = 1; i < ANCHO_PISTA + 1; i++)
	{
		cout << "-" << i;
	}
	cout << "--" << endl;
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

void mostrarEstadistica(string nombreJugador, const tDatosTenista tenista)
{
	int golpesTotales = contarGolpesTotales(tenista), golpesFallidos = contarGolpesFallidos(tenista);
	cout << "Estadisticas de " << tenista.iniciales << ":" << endl;
	cout << setw(3) << "Golpes totales: " << golpesTotales << endl;
	cout << setw(3) << "Golpes ganadores: " << tenista.datosPartido.golpesGanadores << endl;
	cout << setw(3) << "Errores no forzados: " << golpesFallidos << endl;
	cout << setw(3) << "Distribucion de los golpes en la pista:" << endl << endl;
	cout << setw(6) << "Calle" << setw(6) << "0" << setw(6) << "1" << setw(6) << "2" << setw(6) << "3" << setw(6) << "4" << setw(6) << "5" << setw(6) << "6" << setw(6) << "7" << setw(6) << "8" << endl;
	cout << setw(6) << "%" << setw(6) << fixed << setprecision(1) << porcentajeDeGolpeo(tenista, golpesTotales, 0) << setw(6) << fixed << setprecision(1) << porcentajeDeGolpeo(tenista, golpesTotales, 1) << setw(6) << fixed << setprecision(1) << porcentajeDeGolpeo(tenista, golpesTotales, 2) << fixed << setprecision(1) << setw(6) << porcentajeDeGolpeo(tenista, golpesTotales, 3) << fixed << setprecision(1) << setw(6) << porcentajeDeGolpeo(tenista, golpesTotales, 4) << fixed << setprecision(1) << setw(6) << porcentajeDeGolpeo(tenista, golpesTotales, 5) << fixed << setprecision(1) << setw(6) << porcentajeDeGolpeo(tenista, golpesTotales, 6) << fixed << setprecision(1) << setw(6) << porcentajeDeGolpeo(tenista, golpesTotales, 7) << fixed << setprecision(1) << setw(6) << porcentajeDeGolpeo(tenista, golpesTotales, 8) << fixed << setprecision(1) << endl << endl;
}

void mostrarEstadisticas(string nombreJugador1, string nombreJugador2, const tDatosTenista tenista1, const tDatosTenista tenista2)  //tDatosTenista tenista
{

	mostrarEstadistica(nombreJugador1, tenista1);
	mostrarEstadistica(nombreJugador2, tenista2);
}

tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2)
{
	tTenista ganador = NADIE;
	if (ganador_punto == TENISTA1 && datos_t1.puntos != VENTAJA)
	{
		datos_t1.puntos = tPuntosJuego(datos_t1.puntos + 1);
	}
	else if (ganador_punto == TENISTA2 && datos_t2.puntos != VENTAJA)
	{
		datos_t2.puntos = tPuntosJuego(datos_t2.puntos + 1);
	}
	else if (ganador_punto == TENISTA1 && datos_t1.puntos == VENTAJA)
	{
		ganador = TENISTA1;
	}
	else if (ganador_punto == TENISTA2 && datos_t2.puntos == VENTAJA)
	{
		ganador = TENISTA2;
	}

	if (datos_t1.puntos == VENTAJA && datos_t2.puntos == VENTAJA)
	{
		datos_t1.puntos = CUARENTA;
		datos_t2.puntos = CUARENTA;
	}

	if (datos_t1.puntos == VENTAJA && datos_t2.puntos < CUARENTA)
	{
		ganador = TENISTA1;
	}
	else if (datos_t2.puntos == VENTAJA && datos_t1.puntos < CUARENTA)
	{
		ganador = TENISTA2;
	}

	if (ganador != NADIE)
	{
		if (ganador == TENISTA1)
		{
			datos_t1.juegos++;
		}
		else
		{
			datos_t2.juegos++;
		}
		datos_t1.puntos = NADA;
		datos_t2.puntos = NADA;
	}
	return ganador;
}

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador)
{
	int diferencia, diferenciaCasillas;
	diferencia = abs(posicionBola - posicionTenista);
	if (velocidad >= diferencia)
	{
		if (MODO_DEBUG == true)
		{
			cout << "Su rival llega a la bola" << endl;
		}
		posicionTenista = posicionBola;
	}
	else //En el caso de que la velocidad fuera menor que la diferencia
	{
		if (posicionBola < posicionTenista)
		{
			posicionTenista = posicionTenista - velocidad;
			if (MODO_DEBUG == true)
			{
				diferenciaCasillas = posicionTenista - posicionBola;
				cout << "Su rival no llega a la bola." << endl;
			}	
		}
		else if (posicionBola > posicionTenista)
		{
			posicionTenista = posicionTenista + velocidad;
			if (MODO_DEBUG == true)
			{
				diferenciaCasillas = posicionBola - posicionTenista;
				cout << "Su rival no llega a la bola." << endl;
			}
		}
	}
	return posicionTenista;
}

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeadorBola)
{
	int diferencia, posicionDestino, acierto, desvio;
	double probabilidadExito;
	string nombreJugador1, nombreJugador2;
	desvio = rand() % 2;
	acierto = rand() % 100; // número aleatorio 0 - 100 

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

	cout << "Golpea " << nombreGolpeadorBola << endl << endl;
	cout << "El jugador dispara a la calle " << posicionDestino << endl;
	diferencia = abs(posicionDestino - posicion_tenista); 
	if (diferencia <= habilidad)
	{
		if (MODO_DEBUG == true)
		{
			cout << "Ese ha sido un tiro sencillo" << endl;
		}
	}
	else // Si la diferencia entre la posicion del tenista y la posicion de destino de la bola es mayor que la habilidad 
	{
		probabilidadExito = (100.0 - ((posicionDestino - habilidad) / ((ANCHO_PISTA - 1.0) - LIM_INF_HAB) * 100.0)); // porcentaje de acierto
		if (MODO_DEBUG == true)
		{
			cout << "Tiro complicado que... (probab_exito=" << probabilidadExito << " y resultado=" << acierto <<")" << endl;
		}
		if (acierto <= probabilidadExito)
		{
			cout << "LLega a su destino!" << endl;
		}
		else
		{
			if (desvio == 0)
			{
				if (MODO_DEBUG == true)
				{
					cout << "No ha sido preciso!" << endl;
				}
				posicionDestino = posicionDestino + 1; // Desvío a la derecha
			}
			else if (desvio == 1)
			{
				if (MODO_DEBUG == true)
				{
					cout << "No ha sido preciso!" << endl;
				}
				posicionDestino = posicionDestino - 1; // Desvío a la izquierda
			}
		}

	}
	return posicionDestino;
}

tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& posicionBola)
{
	tTenista ganador = NADIE;
	if (bola_para == TENISTA1)
	{
		posicionBola = golpeoBola(tenista_golpea.datosPartido.posicion, tenista_golpea.habilidad, tenista_golpea.iniciales); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
		{
			ganador = TENISTA2; //Gana el otro jugador
		}
		else //Si mete la bola dentro del campo
		{
			tenista_recibe.datosPartido.posicion = correTenista(tenista_recibe.datosPartido.posicion, tenista_recibe.velocidad, posicionBola, tenista_recibe.iniciales);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (tenista_recibe.datosPartido.posicion == posicionBola)//Si el jugador que recibe llega
			{
				ganador = NADIE; //Se sigue el punto
			}
			else //El jugador que recibe no llega a la bola
			{
				ganador = TENISTA1; //Gana el jugador que golpea
			}
		}
	}
	else
	{
		posicionBola = golpeoBola(tenista_golpea.datosPartido.posicion, tenista_golpea.habilidad, tenista_golpea.iniciales); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
		{
			ganador = TENISTA1; //Gana el otro jugador
		}
		else
		{
			tenista_recibe.datosPartido.posicion = correTenista(tenista_recibe.datosPartido.posicion, tenista_recibe.velocidad, posicionBola, tenista_recibe.iniciales);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (tenista_recibe.datosPartido.posicion == posicionBola)//Si el jugador que recibe llega
			{
				ganador = NADIE; //Se sigue el punto
			}
			else //El jugador que recibe no llega a la bola
			{
				ganador = TENISTA2; //Gana el jugador que golpea
			}
		}
	}
	return ganador;
}

tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para)
{
	tenista1.datosPartido.posicion = 4; tenista2.datosPartido.posicion = 4;
	int posicionBola = 4; //Al principio de todos los puntos las posiciones son las mismas
	tTenista ganaPunto = NADIE, turno = servicio_para; //Al prinicipio nadie gana el punto

	pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno); //Pinta el campo inicial
	while (ganaPunto == NADIE)//Se sigue el partido mientras que nadie gane el punto 
	{
		if (turno == TENISTA1) //Si saca el tenista1
		{
			ganaPunto = lance(turno, tenista1, tenista2, posicionBola); //Hace un lance, golpeoBola() y correTenista se ejecutan. Además, se actualizan los números de golpeos
			actualizarGolpes(tenista1, TENISTA1, posicionBola, ganaPunto);
			turno = TENISTA2;
		}
		else
		{
			ganaPunto = lance(turno, tenista2, tenista1, posicionBola);
			actualizarGolpes(tenista2, TENISTA2, posicionBola, ganaPunto);
			turno = TENISTA1;
		}
		pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, posicionBola, turno);
	}
	if(ganaPunto == TENISTA1)
	{
		cout << "Gana el punto " << tenista1.iniciales << "!" << endl;

	}
	else
	{
		cout << "Gana el punto " << tenista2.iniciales << "!" << endl;

	}
	return ganaPunto;
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
	arrayReset(tenista1.datosPartido.golpes);
	arrayReset(tenista2.datosPartido.golpes);
	resetearGolpesGanadores(tenista1);
	resetearGolpesGanadores(tenista2);
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
	if(ganadorPartido == TENISTA1)
	{
		tenista1.partidosGanados++;
	}
	else
	{
		tenista2.partidosGanados++;
	}
	return ganadorPartido;
}

void actualizarGolpes(tDatosTenista& datos_tenista, tTenista servicio, int posicionBola, tTenista ganador)
{
	for (int i = 0; i < DIM_ARRAY_GOLPES; i++)
	{
		if (posicionBola == i) //Se suma un golpe en la dirección a la que haya ido la bola
		{
			datos_tenista.datosPartido.golpes[i]++;
		}
	}
	if (servicio == ganador)
	{
		datos_tenista.datosPartido.golpesGanadores++; //Si el que golpea la bola gana el punto se suma uno a golpes ganados
	}
}

int contarGolpesTotales(const tDatosTenista tenista)
{
	int sumaDeGolpes = 0;
	for (int i = 0; i < DIM_ARRAY_GOLPES; i++)
	{
		sumaDeGolpes = sumaDeGolpes + tenista.datosPartido.golpes[i];
	}
	return sumaDeGolpes;
}

//calcula el porcentaje de golpes en una pista respecto al total de golpes



int contarGolpesFallidos(const tDatosTenista tenista)
{
	int golpesTotales = contarGolpesTotales(tenista), sumaDeGolpesDentro = 0;
	for (int i = 1; i < ANCHO_PISTA ; i++)
	{
		sumaDeGolpesDentro = sumaDeGolpesDentro + tenista.datosPartido.golpes[i];
	}
	return (golpesTotales - sumaDeGolpesDentro);
}

double porcentajeDeGolpeo(const tDatosTenista tenista, double golpesTotales, int calle)
{
	double porcentaje = 0;
	porcentaje = (double((tenista.datosPartido.golpes[calle]) / golpesTotales) * 100);
	return porcentaje;
}

void buscar2Jug(tListaTenistas& listaT, int& indT1, int& indT2)
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

void buscar4Jug(tListaTenistas& listaT, int& indT1, int& indT2, int& indT3, int& indT4)
{
	string iniciales1, iniciales2, iniciales3, iniciales4;
	cout << "introduce las iniciales del tenista1: ";
	cin >> iniciales1;
	indT1 = buscarIniciales(listaT, iniciales1);
	indT2 = buscarIniciales(listaT, iniciales2);
	indT3 = buscarIniciales(listaT, iniciales3);
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

	cout << "introduce las iniciales del tenista3: ";
	cin >> iniciales3;
	indT3 = buscarIniciales(listaT, iniciales3);
	while ((iniciales3 == listaT.datos[indT1].iniciales) || (iniciales3 == listaT.datos[indT2].iniciales) || indT3 < 0)
	{
		cout << "vuelva a introducir las iniciales del tenista3: ";
		cin >> iniciales3;
		indT3 = buscarIniciales(listaT, iniciales3);
	}

	cout << "introduce las iniciales del tenista4: ";
	cin >> iniciales4;
	indT4 = buscarIniciales(listaT, iniciales4);
	while ((iniciales4 == listaT.datos[indT1].iniciales) || (iniciales4 == listaT.datos[indT2].iniciales) || indT4 < 0 || (iniciales4 == listaT.datos[indT3].iniciales))
	{
		cout << "vuelva a introducir las iniciales del tenista4: ";
		cin >> iniciales4;
		indT4 = buscarIniciales(listaT, iniciales4);
	}
}



void arrayReset(tConteoGolpes& array)
{
	for (int i = 0; i < (ANCHO_PISTA + 1); i++)
	{
		array[i] = 0;
	}
}

void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4)
{
	int partido1, partido2, partido3; //enteros para indicar los ganadores de los partidos

	cout << endl << "Comienzan las semifinales!" << endl << endl;
	cout << "* Primera semifinal: " << listaT.datos[indT1].iniciales << " vs " << listaT.datos[indT4].iniciales << " *" << endl;
	cout << "* " << "Segunda semifinal: " << listaT.datos[indT2].iniciales << " vs " << listaT.datos[indT3].iniciales << " *" << endl << endl;
	cout << "* " <<  "COMIENZA EL TORNEO" << " *" << endl << endl;

	if (jugarPartido(listaT.datos[indT1], listaT.datos[indT4]) == tTenista(1))
	{
		partido1 = indT1;
		cout << "El primer finalista es: " << listaT.datos[indT1].iniciales << endl;
	}
	else
	{
		partido1 = indT4;
		cout << "El primer finalista es: " << listaT.datos[indT4].iniciales << endl;
	}

	if (jugarPartido(listaT.datos[indT2], listaT.datos[indT3]) == tTenista(1))
	{
		partido2 = indT2;
		cout << "El segundo finalista es: " << listaT.datos[indT2].iniciales << endl;
	}
	else
	{
		partido3 = indT3;
		cout << "El segundo finalista es: " << listaT.datos[indT3].iniciales << endl;
	}
	resetearJugadoresTorneo(listaT, partido1);
	resetearJugadoresTorneo(listaT, partido2);

	cout << "La final la disputaran: " << listaT.datos[partido1].iniciales << " y " << listaT.datos[partido2].iniciales << "!!!" << endl;

	if (jugarPartido(listaT.datos[partido1], listaT.datos[partido2]) == tTenista(1))
	{
		partido3 = partido1;
	}
	else
	{
		partido3 = partido2;
	}

	cout << "El ganador del torneo es: " << listaT.datos[partido3].iniciales << endl;

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
	if (indT1 == 0 || indT2 == 0)//Si el mayor es el primero
	{
		PGmayor3 = listaT.datos[1].partidosGanados;
	}
	else if ((indT1 == 0 && indT2 == 1) || (indT2 == 0 && indT1 == 1))//Si los mayores son los dos primeros.Son permutaciones sin repeticion por lo que las posibilidades son 2!
	{
		PGmayor3 = listaT.datos[2].partidosGanados;
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
	if (indT1 == 0 || indT2 == 0 || indT3 == 0)	//Si el mayor es uno de los tres pero los siguientes no lo son
	{
		PGmayor4 = listaT.datos[3].partidosGanados;
	}
	else if ((indT1 == 0 && indT2 == 1) || indT1 == 0 && indT3 == 1 || (indT1 == 1 && indT2 == 0) || (indT1 == 1 && indT3 == 1) || (indT2 == 0 && indT3 == 1) || (indT2 == 1 && indT3 == 0))
		//Si los mayores son solo dos. Se trataria de variaciones de 3 elementos con dos posiciones sin repeticion por lo que seria 3!/1! que son 6 posibilidades distintas
	{
		PGmayor4 = listaT.datos[2].partidosGanados;
	}
	else if ((indT1 == 0 && indT2 == 1 && indT3 == 2) || (indT1 == 0 && indT2 == 2 && indT3 == 1) || (indT1 == 1 && indT2 == 0 && indT3 == 2) || (indT1 == 1 && indT2 == 2 && indT3 == 0) || (indT1 == 2 && indT2 == 1 && indT3 == 0) || (indT1 == 2 && indT2 == 0 && indT3 == 1))// El bucle empieza en el cuarto jugador en el caso de que los tres mayores sean los tres primeros.Son permutaciones sin repeticion por lo que las posibilidades son 3!
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

void resetearGolpesGanadores(tDatosTenista& tenista)
{
	tenista.datosPartido.golpesGanadores = 0;
}

void resetearJugadoresTorneo(tListaTenistas& listaT, int jugador)
{
	listaT.datos[jugador].datosPartido.puntos = NADA;
	listaT.datos[jugador].datosPartido.juegos = 0;
	listaT.datos[jugador].datosPartido.golpesGanadores = 0;
}
