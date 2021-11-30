//Rishi Pursnani Mirpuri y Javier Ramírez de Andrés
//version 2
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;
const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;
const int LIM_SUP_VEL = 3;
const int LIM_SUP_HAB = 3;
const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;
const int JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
bool JUEGO_ALEATORIO = false;
bool MODO_DEBUG = false;


string introducirNombre(string numeroJugador);

int introducirDato(string nombreJugador, int habilidadJugador, int velocidadJugador);

int elegirSaque(string jugador1, string jugador2);

void mostrarMarcadorActual(int puntuacionJugador1, int puntuacionJugador2, string nombreJugador1, string nombreJugador2);

int juegoEstaTerminado(int puntuacion1, int puntuacion2);

int correTenista(int posicion_tenista, int velocidad, int posicionBola, string nombreJugador);

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeador);

enum tTenista { NADIE, TENISTA1, TENISTA2 };

enum tPuntosJuego { NADA, QUINCE, TREINTA, CUARENTA, VENTAJA };

typedef int tConteoGolpes[DIM_ARRAY_GOLPES];

int partido(string nombreJugador1, string nombreJugador2, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int velocidadJugador2, int habilidadJugador2);//Funcion que devuelva quien es el ganador del punto

void pintarMarcador(string nombreJugador1, string nombreJugador2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para);

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador);

void introducirTenista(string& iniciales, int& habilidad, int& velocidad);

void pintarMarcador(string nombreJugador1, string nombreJugador2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para);

string puntosAstring(tPuntosJuego puntuacion);

tTenista jugarJuego(tTenista servicio, string nombre1, int habilidad1, int velocidad1, int& juegos1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int& juegos2, tConteoGolpes golpes2, int& golpes_ganados2);

tTenista actualizarMarcador(tTenista ganador_punto, tPuntosJuego& puntos1, tPuntosJuego& puntos2, int& juegos1, int& juegos2);

tTenista lance(tTenista tenista_golpea, string nombreJugador1, string nombreJugador2, int habilidad, tConteoGolpes golpes, int& golpes_ganados, int velocidad, int& pos_recibe, int& posicionBola);

void arrayReset(tConteoGolpes& array);

void mostrarEstadisticas(string nombreJugador1, string nombreJugador2, tConteoGolpes golpes1, tConteoGolpes golpes2, int golpes_ganados1, int golpes_ganados2);

int main()
{
	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2, juegos1 = 0, juegos2 = 0, habilidad, velocidad;
	int punto = 0, jugadorTurno;
	string nombreJugador1, nombreJugador2, breakTest, iniciales;
	tTenista bola_jugador, servicio_para, ganador_punto, tenista_golpea;
	tPuntosJuego puntos1, puntos2, puntuacion;
	tConteoGolpes golpes1 = { 0 }, golpes2 = { 0 };
	bool JUEGO_TERMINADO = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
	int golpes_ganados1 = 0, pos_recibe = 4, golpes_ganados2 = 0;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
	cout << "¡Bienvenido al simulador de partidos de tenis!" << endl;
	cout << "Introduzca los datos del jugador 1: " << endl;
	introducirTenista(inicialesJugador1, habilidadJugador1, velocidadJugador1);
	cout << "Introduzca los datos del jugador 2: " << endl;
	introducirTenista(inicialesJugador2, habilidadJugador2, velocidadJugador2);
	
	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;


	jugadorTurno = elegirSaque(nombreJugador1, nombreJugador2);
	cout << endl;
	if (jugadorTurno == 1)
	{
		tenista_golpea = TENISTA1;
		servicio_para = TENISTA1;
		bola_jugador = TENISTA1;
	}
	else
	{
		tenista_golpea = TENISTA2;
		servicio_para = TENISTA2;
		bola_jugador = TENISTA2;
	}



	while (((juegos1 - juegos2) <= 2 || (juegos2 - juegos1) <= 2) && (juegos1 <= 3 && juegos2 <= 3))
	{
		jugarJuego(servicio_para, nombreJugador1, habilidadJugador1, velocidadJugador1, juegos1,  golpes1, golpes_ganados1,  nombreJugador2, habilidadJugador2, velocidadJugador2, juegos2, golpes2,  golpes_ganados2);
		system("pause");
	}
	
	mostrarEstadisticas(nombreJugador1, nombreJugador2, golpes1, golpes2, golpes_ganados1, golpes_ganados2);
	exit(EXIT_SUCCESS);
	return 0;
}

string introducirNombre(string numeroJugador)
{
	string nombreJugador;
	cout << "Introduce las iniciales del jugador " << numeroJugador << ": ";
	cin >> nombreJugador;
	return nombreJugador;
}
void introducirTenista(string& iniciales, int& habilidad, int& velocidad)
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
		cout << "Valores incorrectos, introduzca de nuevo la habilidad del jugador: ";
		cin >> habilidad;
	}
	cout << "Introduce la velocidad del jugador (Intervalo 1-3): ";
	cin >> velocidad;
	while (velocidad < 1 || velocidad > 3)
	{
		cout << "Valores incorrectos, introduzca de nuevo la velocidad del jugador: ";
		cin >> velocidad;
	}
}

int elegirSaque(string jugador1, string jugador2)
{
	int saque;
	saque = rand() % 2;
	if (saque == 0)
	{
		cout << "Servicio para " << jugador1 << endl;
		return 1;
	}
	else if (saque == 1)
	{
		cout << "Servicio para " << jugador2 << endl;
		return 2;
	}
}

int introducirDato(string tipoDato, int limiteInferior, int limiteSuperior)
{
	int datoNumerico;
	cout << "Introduce su " << tipoDato << "(Intervalo (" << limiteInferior << " - " << limiteSuperior << ")";
	cin >> datoNumerico;
	while (datoNumerico > limiteSuperior || datoNumerico < limiteInferior)
	{
		cout << "Datos introducidos incorrectamente, vuelva a introducir los datos entre los valores " << limiteInferior << " y " << limiteSuperior;
		cin >> datoNumerico;
	}
	return datoNumerico;
}

void pintarMarcador(string nombreJugador1, string nombreJugador2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para)
{
	if (servicio_para == 1)
	{
		cout << setw(5) << nombreJugador1 << setw(2) << juegos1 << " : " << puntos1 << "*" << endl;
		cout << setw(5) << nombreJugador2 << setw(2) << juegos2 << " : " << puntos2 << endl;
	}
	else
	{
		cout << setw(5) << nombreJugador1 << setw(2) << juegos1 << " : " << puntos1 << endl;
		cout << setw(5) << nombreJugador2 << setw(2) << juegos2 << " : " << puntos2 << "*" << endl;
	}
}

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador)
{
	if (bola_jugador == 1)
	{
		cout << setw(posicionJugador1 * 2 + 2) << nombreJugador1 << endl;
		cout << "  - - - - - - - " << endl;
		for (int a = 1; a <= LARGO_PISTA; a++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
				if (i == posicionBola && a == LARGO_PISTA)
				{
					cout << setw((posicionBola + 1) - posicionBola) << "o|";
				}
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
		cout << setw(posicionJugador2 * 2 + 2) << nombreJugador2 << endl;
	}
	else if (bola_jugador == 2)
	{
		cout << setw(posicionJugador1 * 2 + 2) << nombreJugador1 << endl;
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
		for (int a = 1; a <= LARGO_PISTA; a++)
		{
			for (int i = 1; i <= ANCHO_PISTA; i++)
			{
				cout << setw(2) << "|";
				if (i == posicionBola && a == LARGO_PISTA)
				{
					cout << setw((posicionBola + 1) - posicionBola) << "o|";
				}
			}
			cout << setw(2) << "|" << endl;
		}
		cout << "  - - - - - - - " << endl;
		cout << setw(posicionJugador2 * 2 + 2) << nombreJugador2 << endl;
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

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador)
{
	int diferencia, diferenciaCasillas;
	diferencia = abs(posicionBola - posicionTenista);
	if (velocidad >= diferencia)
	{
		if (MODO_DEBUG == true)
		{
			cout << nombreJugador << " llega sin problemas" << endl;
		}
		posicionTenista = posicionBola;
		return posicionTenista;
	}
	else //En el caso de que la velocidad fuera menor que el diferencia
	{
		if (posicionBola < posicionTenista) {
			if (MODO_DEBUG == true)
			{
				diferenciaCasillas = posicionTenista - posicionBola;
				cout << nombreJugador << " intenta llegar por la derecha pero se queda en la posicion " << posicionTenista << " a " << diferenciaCasillas << " de su objetivo y pierde el punto" << endl;
			}
			posicionTenista = posicionTenista - velocidad;
			return posicionTenista;// Posición adelantada
		}
		else if (posicionBola > posicionTenista) {
			if (MODO_DEBUG == true)
			{
				diferenciaCasillas = posicionBola - posicionTenista;
				cout << nombreJugador << " intenta llegar por la izquierda pero se queda en la posicion " << posicionTenista << " a " << diferenciaCasillas << " de su objetivo y pierde el punto" << endl;
			}
			posicionTenista = posicionTenista + velocidad;
			return posicionTenista;// Posición atrasada
		}
		else {
			if (posicionBola < posicionTenista) {
				return posicionTenista;// Punto para el otro jugador
			}
		}
	}
}

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeadorBola) {
	int diferencia, posicionDestino, acierto, desvio;
	double probabilidadExito;
	string nombreJugador1, nombreJugador2;
	desvio = rand() % 2;
	acierto = rand() % 100; // número aleatorio 0 - 100 
	cout << "Golpea " << nombreGolpeadorBola << "!" << endl;


	if (JUEGO_ALEATORIO == true) {
		cout << "Introduzca la posición destino: ";
		cin >> posicionDestino;
	}
	else
	{
		posicionDestino = rand() % (ANCHO_PISTA + 1); // posición destino de la bola
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
	else if (diferencia > habilidad) // Si la diferencia entre la posicion del tenista y la posicion de destino de la bola es mayor que la habilidad 
	{
		probabilidadExito = (100.0 - ((posicionDestino - habilidad) / ((ANCHO_PISTA - 1.0) - LIM_INF_HAB) * 100.0)); // porcentaje de acierto
		if (MODO_DEBUG == true)
		{
			if (acierto <= probabilidadExito)
			{
				if (MODO_DEBUG == true)
				{
					cout << nombreGolpeadorBola << " lanza la bola a " << posicionDestino << endl;
				}
				return posicionDestino;
			}
			else if (acierto > probabilidadExito)
			{
				if (desvio == 0)
				{
					if (MODO_DEBUG == true)
					{
						cout << nombreGolpeadorBola << " lanza la bola a " << posicionDestino << " pero se desvía a la derecha y acaba en la posición " << posicionDestino + 1 << endl;
					}
					return posicionDestino + 1; // Desvío a la derecha
				}
				else if (desvio == 1)
				{
					if (MODO_DEBUG == true)
					{
						cout << nombreGolpeadorBola << " lanza la bola a " << posicionDestino << " pero se desvía a la izquierda y acaba en la posicion " << posicionDestino - 1 << endl;
					}
					return posicionDestino - 1; // Desvío a la izquierda
				}
			}
		}
	}
}

void arrayReset(tConteoGolpes& array)
{
	for (int i = 0; i < DIM_ARRAY_GOLPES; i++)
	{
		array[i] = 0;
	}
}

tTenista actualizarMarcador(tTenista ganador_punto, tPuntosJuego& puntos1, tPuntosJuego& puntos2, int& juegos1, int& juegos2)
{
	if (ganador_punto == TENISTA1)
	{
		if (puntos1 == NADA)
		{
			puntos1 = QUINCE;
		}
		else if (puntos1 == QUINCE)
		{
			puntos1 = TREINTA;
		}
		else if (puntos1 == TREINTA)
		{
			puntos1 = CUARENTA;
		}
		return TENISTA1;
	}
	else if (ganador_punto == TENISTA2)
	{
		if (puntos2 == NADA)
		{
			puntos2 = QUINCE;
		}
		else if (puntos2 == QUINCE)
		{
			puntos2 = TREINTA;
		}
		else if (puntos2 == TREINTA)
		{
			puntos2 = CUARENTA;
		}
		return TENISTA2;
	}
	if (puntos1 == CUARENTA && puntos2 == CUARENTA)
	{
		if (ganador_punto == TENISTA1)
		{
			puntos1 = VENTAJA;
		}
		else if (ganador_punto == TENISTA2)
		{
			puntos2 = VENTAJA;
		}
		return NADIE;
	}
	else
	{
		if (ganador_punto == TENISTA1)
		{
			if (puntos1 == CUARENTA)
			{
				puntos1 = NADA;
				juegos1++;
			}
			return TENISTA1;
		}
		else
		{
			if (puntos2 == CUARENTA)
				if (puntos2 == CUARENTA)
				{
					puntos2 = NADA;
					juegos2++;
				}
			return TENISTA2;
		}
	}
}

tTenista lance(tTenista tenista_golpea, string nombreJugador1, string nombreJugador2, int habilidad, tConteoGolpes golpes, int& golpes_ganados, int velocidad, int& pos_recibe, int& posicionBola)
{
	if (tenista_golpea == TENISTA1) {
		posicionBola = golpeoBola(posicionBola, habilidad, nombreJugador1); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
			posicionBola = golpeoBola(posicionBola, habilidad, nombreJugador1); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
		{
			golpes_ganados++;
			golpes++;
			return TENISTA2; //Gana el otro jugador
		}
		else
		{
			pos_recibe = correTenista(pos_recibe, velocidad, posicionBola, nombreJugador2);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (pos_recibe == posicionBola)//Si el jugador que recibe llega
				pos_recibe = correTenista(pos_recibe, velocidad, posicionBola, nombreJugador2);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (pos_recibe == posicionBola)//Si el jugador que recibe llega
			{
				return NADIE; //Se sigue el punto
			}
			else //El jugador que recibe no llega a la bola
			{
				golpes_ganados++;
				golpes++;
				return TENISTA1; //Gana el jugador que golpea
			}
		}
	}
	else
	{
		posicionBola = golpeoBola(posicionBola, habilidad, nombreJugador2); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
			posicionBola = golpeoBola(posicionBola, habilidad, nombreJugador2); //La posicion de la bola pasará a la posición dada por la función golpeo bola
		if (posicionBola <= 0 || posicionBola >= ANCHO_PISTA + 1) // Si tira la bola fuera
		{
			golpes_ganados++;
			golpes++;
			return TENISTA1; //Gana el otro jugador
		}
		else
		{
			pos_recibe = correTenista(pos_recibe, velocidad, posicionBola, nombreJugador1);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (pos_recibe == posicionBola)//Si el jugador que recibe llega
				pos_recibe = correTenista(pos_recibe, velocidad, posicionBola, nombreJugador1);//La posicion del jugador que recibe pasará a la posición dada por la función correTensita
			if (pos_recibe == posicionBola)//Si el jugador que recibe llega
			{
				return NADIE; //Se sigue el punto
			}
			else //El jugador que recibe no llega a la bola
			{
				golpes_ganados++;
				golpes++;
				return TENISTA2; //Gana el jugador que golpea
			}
		}
	}
}

//tTenista jugarPunto(tTenista servicio, string nombre1, int habilidad1, int velocidad1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, tConteoGolpes golpes2, int& golpes_ganados2)
tTenista jugarPunto(tTenista servicio, string nombre1, int habilidad1, int velocidad1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, tConteoGolpes golpes2, int& golpes_ganados2)
{
	int pos_jugador1 = 4, pos_jugador2 = 4, posicionBola = 4;
	tTenista ganaPunto = NADIE;
	while (ganaPunto == NADIE) {
		if (servicio == TENISTA1)
		{
			ganaPunto = lance(servicio, nombre1, nombre2, habilidad1, golpes1, golpes_ganados1, velocidad2, pos_jugador2, posicionBola);
			if (ganaPunto == TENISTA1)
			{
				pintarPeloteo(nombre1, nombre2, pos_jugador1, pos_jugador2, posicionBola, servicio);
				return TENISTA1;
			}
			else if (ganaPunto == TENISTA2)
			{
				pintarPeloteo(nombre1, nombre2, pos_jugador1, pos_jugador2, posicionBola, servicio);
				return TENISTA2;
			}
			else
			{
				pintarPeloteo(nombre1, nombre2, pos_jugador1, pos_jugador2, posicionBola, servicio);
				servicio == TENISTA2;
			}
		}
		else if (servicio == TENISTA2)
		{
			ganaPunto = lance(servicio, nombre1, nombre2, habilidad2, golpes2, golpes_ganados2, velocidad1, pos_jugador1, posicionBola);
			if (ganaPunto == TENISTA1)
			{
				pintarPeloteo(nombre1, nombre2, pos_jugador1, pos_jugador2, posicionBola, servicio);
				return TENISTA1;
			}
			else if (ganaPunto == TENISTA2)
			{
				pintarPeloteo(nombre1, nombre2, pos_jugador1, pos_jugador2, posicionBola, servicio);
				return TENISTA2;
			}
			else
			{
				pintarPeloteo(nombre1, nombre2, pos_jugador1, pos_jugador2, posicionBola, servicio);
				servicio == TENISTA1;
			}
		}
	}
}

tTenista jugarJuego(tTenista servicio, string nombre1, int habilidad1, int velocidad1, int& juegos1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int& juegos2, tConteoGolpes golpes2, int& golpes_ganados2, tPuntosJuego& puntos1, tPuntosJuego& puntos2)
{
	tTenista ganadorJuego = actualizarMarcador(jugarPunto(servicio, nombre1, habilidad1, velocidad1, golpes1, golpes_ganados1, nombre2, habilidad2, velocidad2, golpes2, golpes_ganados2), puntos1, puntos2, juegos1, juegos2);


	while (ganadorJuego == NADIE)
	{
		actualizarMarcador(jugarPunto(servicio, nombre1, habilidad1, velocidad1, golpes1, golpes_ganados1, nombre2, habilidad2, velocidad2, golpes2, golpes_ganados2), puntos1, puntos2, juegos1, juegos2);
		pintarMarcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, servicio);
	}
	if (ganadorJuego == TENISTA1)
	{
		return TENISTA1;
	}
	else if (ganadorJuego == TENISTA2)
	{
		return TENISTA2;
	}
}

void mostrarEstadisticas(string nombreJugador1, string nombreJugador2, tConteoGolpes golpes1, tConteoGolpes golpes2, int golpes_ganados1, int golpes_ganados2)
{
	cout << "Estadisticas de " << nombreJugador1;
	cout << setw(3) << "Golpes totales: "<<golpes1;
	cout << setw(3) << "Golpes ganadores: " << golpes_ganados1;
	cout << setw(3) << "Errores no forzados: ";
	cout << setw(3) << "Distribucion de los golpes en la pista";
	cout << setw(6) << "Calle" << setw(6) << "0"<<setw(6) << "1" << setw(6) << "2" << setw(6) << "3" << setw(6) << "4" << setw(6) << "5" << setw(6) << "6" << setw(6) << "7" << setw(6) << "8";
	cout << setw(10) << "%";

	cout << "Estadisticas de " << nombreJugador2;
	cout << setw(3) << "Golpes totales: " << golpes2;
	cout << setw(3) << "Golpes ganadores: " << golpes_ganados2;
	cout << setw(3) << "Errores no forzados: ";
	cout << setw(3) << "Distribucion de los golpes en la pista";
	cout << setw(6) << "Calle" << setw(6) << "0" << setw(6) << "1" << setw(6) << "2" << setw(6) << "3" << setw(6) << "4" << setw(6) << "5" << setw(6) << "6" << setw(6) << "7" << setw(6) << "8";
	cout << setw(10) << "%";


}
