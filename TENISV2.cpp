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
bool JUEGO_ALEATORIO = false;
bool MODO_DEBUG = false;

string introducirNombre(string numeroJugador);

int introducirDato(string nombreJugador, int habilidadJugador, int velocidadJugador);

string marcador(int puntuacion);

int elegirSaque(string jugador1, string jugador2);

void mostrarMarcadorActual(int puntuacionJugador1, int puntuacionJugador2, string nombreJugador1, string nombreJugador2);

int juegoEstaTerminado(int puntuacion1, int puntuacion2);

int correTenista(int posicion_tenista, int velocidad, int posicionBola, string nombreJugador);

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeador);

enum tTenista { NADIE, TENISTA1, TENISTA2 };

enum tPuntosJuego { NADA, QUINCE, TREINTA, CUARENTA, VENTAJA };

int partido(string nombreJugador1, string nombreJugador2, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int velocidadJugador2, int habilidadJugador2);//Funcion que devuelva quien es el ganador del punto

void pintarMarcador(string nombreJugador1, string nombreJugador2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para);

void pintarPeloteo(string nombreJugador1, string nombreJugador2, int posicionJugador1, int posicionJugador2, int posicionBola, tTenista bola_jugador);

void introducirTenista(string& iniciales, int& habilidad, int& velocidad);

void pintarMarcador(string nombreJugador1, string nombreJugador2, tPuntosJuego puntos1, tPuntosJuego puntos2, int juegos1, int juegos2, tTenista servicio_para);

string puntosAstring(tPuntosJuego puntuacion);

int main()
{
	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2, juegos1 = 0, juegos2 = 0, habilidad, velocidad;
	int punto = 0, jugadorTurno;
	string nombreJugador1, nombreJugador2, breakTest, iniciales;
	tTenista bola_jugador;
	tTenista servicio_para;
	tPuntosJuego puntos1, puntos2, puntuacion;
	bool JUEGO_TERMINADO = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
	int posicionJugador1 = 4;
	int posicionJugador2 = 4, posicionBola = 4;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");

	cout << "¡Bienvenido al simulador de partidos de tenis!" << endl;

	//nombreJugador1 = introducirNombre("1");
	//velocidadJugador1 = introducirDato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);
	//habilidadJugador1 = introducirDato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);

	//nombreJugador2 = introducirNombre("2");
	//velocidadJugador2 = introducirDato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);
	//habilidadJugador2 = introducirDato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);

	introducirTenista(iniciales, habilidad, velocidad);

	nombreJugador1 = iniciales;

	introducirTenista(iniciales, habilidad, velocidad);

	nombreJugador2 = iniciales;

	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;

	jugadorTurno = elegirSaque(nombreJugador1, nombreJugador2);
	cout << endl;

	servicio_para = TENISTA1;
	puntos1 = QUINCE;
	puntos2 = NADA;

	pintarMarcador(nombreJugador1, nombreJugador2, puntos1, puntos2, juegos1, juegos2, servicio_para);

	while (juegos1 - juegos2 != 2 || juegos2 - juegos1 != 2)
	{

	}

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
	string nombreJugador1, nombreJugador2;
	int habilidadJugador1, habilidadJugador2, velocidadJugador1, velocidadJugador2;

	cout << "introduzca las iniciales del jugador 1 : ";
	cin >> iniciales;
	while (iniciales.length() != 3)
	{
		iniciales = introducirNombre("1");
	}
	velocidad = introducirDato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);
	habilidad = introducirDato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);

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

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeadorBola) {
	int diferencia, posicionDestino, acierto, desvio;
	double probabilidadExito;
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

tTenista actualizarMarcador(tTenista ganador_punto, tPuntosJuego& puntos1, tPuntosJuego& puntos2, int& juegos1, int& juegos2)
{
	if (ganador_punto == 1)
	{
		ganador_punto = 0
		puntos1++;
	}
	else if (ganador_punto == 2)
	{
		ganador_punto = 0;
		puntos2++;
	}
}

tTenista lance(tTenista tenista_golpea, string nombre, int habilidad, tConteoGolpes golpes, int& golpes_ganados, int velocidad, int& pos_recibe, int& pos_bola)
{

}

tTenista jugarPunto(tTenista servicio, string nombre1, int habilidad1, int velocidad1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, tConteoGolpes golpes2, int& golpes_ganados2)
{
	if (jugadorSaque == 1)
		cout << "Saca " << nombreJugador1 << endl;
	else
		cout << "Saca " << nombreJugador2 << endl;

	int jugadorTurnoActual = jugadorSaque;
	int posicionJugadorActual, habilidadJugadorActual, velocidadJugadorActual;
	int posicionJugadorContrario, habilidadJugadorContrario, velocidadJugadorContrario;

	string nombreJugadorActual, nombreJugadorContrario;

	while (true) //Bucle que se ejecuta hasta que haya un ganador del punto
	{
		if (jugadorTurnoActual == 1)// En el caso de que la bola la empiece jugando el jugador1
		{
			posicionJugadorActual = posicionJugador1;
			habilidadJugadorActual = habilidadJugador1;
			velocidadJugadorActual = velocidadJugador1;
			nombreJugadorActual = nombreJugador1;

			posicionJugadorContrario = posicionJugador2;
			habilidadJugadorContrario = habilidadJugador2;
			velocidadJugadorContrario = velocidadJugador2;
			nombreJugadorContrario = nombreJugador2;
		}
		else
		{
			posicionJugadorActual = posicionJugador2;
			habilidadJugadorActual = habilidadJugador2;
			velocidadJugadorActual = velocidadJugador2;
			nombreJugadorActual = nombreJugador2;

			posicionJugadorContrario = posicionJugador1;
			habilidadJugadorContrario = habilidadJugador1;
			velocidadJugadorContrario = velocidadJugador1;
			nombreJugadorContrario = nombreJugador1;
		}

		posicionBola = golpeoBola(posicionJugadorActual, habilidadJugadorActual, nombreJugadorActual); //La posicion de la bola pasará a la posición dada por la función golpeo bola

		if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) //Si la bola sale fuera será punto para el jugador 2
		{
			if (MODO_DEBUG == true)
			{
				cout << nombreJugadorActual << " tira la bola fuera de la pista" << endl;
			}

			if (jugadorTurnoActual == 1)
			{
				cout << nombreJugadorContrario << " gana el punto" << endl; //Gana el contrario
				return 2;
			}
			else
			{
				cout << nombreJugadorContrario << " gana el punto" << endl; //Gana el contrario
				return 1;
			}
		}
		else if (posicionBola > 0 && posicionBola < (ANCHO_PISTA + 1)) //Si la bola cae dentro del campo vemos si sigue el juego
		{
			posicionJugadorContrario = correTenista(posicionJugadorContrario, velocidadJugadorContrario, posicionBola, nombreJugadorContrario); //La posición del Jugador2 viene dada por la función correTenista
			if (posicionJugadorContrario == posicionBola) {
				//cout << nombreJugadorContrario << " llega a la bola" << endl;
				if (jugadorTurnoActual == 1)
					jugadorTurnoActual = 2; //Llega a la bola
				else
					jugadorTurnoActual = 1; //Llega a la bola
			}
			else if (posicionJugadorContrario != posicionBola) {
				//cout << nombreJugadorContrario << " no consigue llegar a la bola" << endl;
				if (jugadorTurnoActual == 1)
				{
					cout << nombreJugadorActual << " gana el punto" << endl; //Gana el que golpea
					return 1;
				}
				else
				{
					cout << nombreJugadorActual << " gana el punto" << endl; //Gana el que golpea
					return 2;
				}
			}
		}
	}
}

tTenista jugarJuego(tTenista servicio, string nombre1, int habilidad1, int velocidad1, int& juegos1, tConteoGolpes golpes1, int& golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int& juegos2, tConteoGolpes golpes2, int& golpes_ganados2)
{

}
