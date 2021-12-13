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

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador);

tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2);

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador);

int golpeoBola(int posicionTenista, int habilidad, string nombreGolpeador);

tTenista lance(tTenista bolaPara, tDatosTenista& tenistaGolpea, tDatosTenista& tenistaRecibe, int& posicionBola);

tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para);

void actualizarGolpes(tDatosTenista& tenista, tTenista servicio, int posicionBola, tTenista ganador);

int contarGolpesTotales(tDatosTenista tenista);

int contarGolpesFallidos(tDatosTenista tenista);

int porcentajeDeAcierto(tDatosTenista tenista, int golpesTotales, int calle);

tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para);







int main()
{
	tListaTenistas listaDeTenistas;
	int opcionMenu;
	//opcionMenu = menu();
	cargar(listaDeTenistas);
	mostrar(listaDeTenistas);
	mostrarIniciales(listaDeTenistas);
	introducirTenista(listaDeTenistas);
	guardar(listaDeTenistas);
	mostrarIniciales(listaDeTenistas);
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
		cout << setw(2) << listaT.datos[i].iniciales << setw(5) <<  listaT.datos[i].habilidad << setw(5) << listaT.datos[i].velocidad << setw(4) << listaT.datos[i].partidosGanados << setw(4) << listaT.datos[i].partidosPerdidos << endl;
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
	for(int i = 0; i < listaT.contador; i++)
	{
		if(ini == listaT.datos[i].iniciales)
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
	if(posicion != -1)
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
	if(posicion != -1)
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

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador)
{
	if (bola_jugador == TENISTA1)
	{
		cout << setw((posicionJugador1 * 2) + 2) << nombreJugador1 << endl;
		cout << "  - - - - - - - " << endl;
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
		cout << endl;
		for (int a = 1; a <= (LARGO_PISTA - 1); a++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
		cout << "--1-2-3-4-5-6-7--" << endl;
		for (int i = 1; i <= LARGO_PISTA; i++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
		cout << "  - - - - - - - " << endl;
		cout << setw((posicionJugador2 * 2) + 2) << nombreJugador2 << endl;
	}
	else if (bola_jugador == TENISTA2)
	{
		cout << setw((posicionJugador1 * 2) + 2) << nombreJugador1 << endl;
		cout << "  - - - - - - - " << endl;
		for (int i = 1; i <= LARGO_PISTA; i++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
			}
			cout << setw(2) << "|" << endl;
		}
		cout << "--1-2-3-4-5-6-7--" << endl;
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
		cout << endl;
		cout << "  - - - - - - - " << endl;
		cout << setw(posicionJugador2 * 2 + 2) << nombreJugador2 << endl;
	}
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
	diferencia = abs(posicionDestino - posicion_tenista); //
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
	if (bola_para == TENISTA1) {
		posicionBola = golpeoBola(posicionBola, tenista_golpea.habilidad, tenista_golpea.iniciales); //La posicion de la bola pasará a la posición dada por la función golpeo bola
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
		posicionBola = golpeoBola(posicionBola, tenista_golpea.habilidad, tenista_golpea.iniciales); //La posicion de la bola pasará a la posición dada por la función golpeo bola
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
			actualizarGolpes(tenista1.datosPartido, TENISTA1, posicionBola, ganaPunto);
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
			actualizarGolpes(tenista2.datosPartido, TENISTA2, posicionBola, ganaPunto);
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

	while (actualizarMarcador(ganadorPunto, tenista1.datosPartido, tenista2.datosPartido, juegos1, juegos2) == NADIE) // Se juegan los puntos hasta que actualizarMarcador devuelva o TENISTA1 o TENISTA2
	{
		tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido & datos_t1, tDatosPartido & datos_t2)

		pintarMarcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, servicio); //Muestra el marcador
		ganadorPunto = jugarPunto(servicio, nombre1, habilidad1, velocidad1, golpes1, golpesGanados1, nombre2, habilidad2, velocidad2, golpes2, golpesGanados2);
	}

	pintarMarcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, servicio);
	mostrarEstadisticas(nombre1, nombre2, golpes1, golpes2, golpesGanados1, golpesGanados2); //Al final de cada juego muestra las estadísticas


	if (ganadorPunto == TENISTA1)// Si el juego lo gana el j1
	{
		return TENISTA1;
	}
	else // Si el juego lo gana el j2
	{
		return TENISTA2;
	}
}
void actualizarGolpes(tDatosPartido& datos_partido, tTenista servicio, int posicionBola, tTenista ganador)
{
	datos_partido.golpes[posicionBola]++; //Se suma un golpe en la dirección a la que haya ido la bola
	if (servicio == ganador)
	{
		datos_partido.golpesGanadores++; //Si el que golpea la bola gana el punto se suma uno a golpes ganados
	}
}

int contarGolpesTotales(tDatosPartido datos_partido)
{
	int sumaDeGolpes = 0;
	for (int i = 0; i < DIM_ARRAY_GOLPES; i++)
	{
		sumaDeGolpes = sumaDeGolpes + datos_partido.golpes[i];
	}
	return sumaDeGolpes;
}


int contarGolpesFallidos(tDatosPartido datos_partido)
{
	int golpesTotales = contarGolpesTotales(datos_partido), sumaDeGolpesDentro = 0;
	for (int i = 1; i < ANCHO_PISTA + 1; i++)
	{
		sumaDeGolpesDentro = sumaDeGolpesDentro + datos_partido.golpes[i];
	}
	return (golpesTotales - sumaDeGolpesDentro);
}

int porcentajeDeAcierto(tDatosPartido datos_partido, int golpesTotales, int calle)
{
	double golpesCalle = datos_partido.golpes[calle];
	double porcentaje;
	porcentaje = (golpesCalle / golpesTotales) * 100;
	return porcentaje;
}
