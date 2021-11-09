//Rishi Pursnani Mirpuri y Javier Ramírez de Andrés
//Final de la versión 1
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;
const int LIM_SUP_VEL = 3;
const int LIM_SUP_HAB = 3;
const int ANCHO_PISTA = 7;
bool JUEGO_ALEATORIO = false;
bool MODO_DEBUG = true;

string introducirNombre(string numeroJugador);

int introducirDato(string nombreJugador, int habilidadJugador, int velocidadJugador);

string marcador(int puntuacion);

int elegirSaque(string jugador1, string jugador2);

void mostrarMarcadorActual(int puntuacionJugador1, int puntuacionJugador2, string nombreJugador1, string nombreJugador2);

bool juegoEstaTerminado(int puntuacion1, int puntuacion2);

int correTenista(int posicion_tenista, int velocidad, int posicionBola, string nombreJugador);

int golpeoBola(int posicion_tenista, int habilidad, string nombreGolpeador);

int partido(string nombreJugador1, string nombreJugador2, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int velocidadJugador2, int habilidadJugador2);//Funcion que devuelva quien es el ganador del punto

int main()
{
	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2;
	int punto = 0, jugadorTurno;
	string nombreJugador1, nombreJugador2, breakTest;
	bool JUEGO_TERMINADO = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
	int posicionJugador1 = 4;
	int posicionJugador2 = 4, posicionBola = 4;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
	
	cout << "¡Bienvenido al simulador de partidos de tenis!" << endl;

	nombreJugador1 = introducirNombre("1");
	velocidadJugador1 = introducirDato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);
	habilidadJugador1 = introducirDato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);
	
	nombreJugador2 = introducirNombre("2");
	velocidadJugador2 = introducirDato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);
	habilidadJugador2 = introducirDato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);

	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;

	jugadorTurno = elegirSaque(nombreJugador1, nombreJugador2);

	while (!JUEGO_TERMINADO)
	{
		punto = partido(nombreJugador1, nombreJugador2, jugadorTurno, posicionJugador1, posicionJugador2, posicionBola, velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2);

		if (punto == 1)
		{
			punto = 0;
			puntuacionJugador1++;
		}
		else if (punto == 2)
		{
			punto = 0;
			puntuacionJugador2++;
		}

		//Controlar deuce
		if (puntuacionJugador1 == 4 && puntuacionJugador2 == 4)
		{
			puntuacionJugador1 = 3;
			puntuacionJugador2 = 3;
		}

		mostrarMarcadorActual(puntuacionJugador1, puntuacionJugador2, nombreJugador1, nombreJugador2);
		JUEGO_TERMINADO = juegoEstaTerminado(puntuacionJugador1, puntuacionJugador2);
		cout << "Presione una tecla para continuar... ";

		cin >> breakTest;
	}
	cout << "El juego esta acabado" << endl;
	return 0;
}

string introducirNombre(string numeroJugador)
{
	string nombreJugador;
	cout << "Introduce el nombre del jugador " << numeroJugador << ": ";
	cin >> nombreJugador;
	return nombreJugador;
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

string marcador(int puntuacion)
{
	if (puntuacion == 0)
	{
		return "00";
	}
	else if (puntuacion == 1)
	{
		return "15";
	}
	else if (puntuacion == 2)
	{
		return "30";
	}
	else if (puntuacion == 3)
	{
		return "40";
	}
	else if (puntuacion == 4)
	{
		return "[Ventaja]";
	}
	else {
		return"";
	}
}
void mostrarMarcadorActual(int puntuacionJugador1, int puntuacionJugador2, string nombreJugador1, string nombreJugador2)
{
	string marcadorJugador1, marcadorJugador2;

	if (puntuacionJugador1 == 3 && puntuacionJugador2 == 3)
	{
		cout << "Deuce" << endl;
		return;
	}

	if (puntuacionJugador1 >= 0 && puntuacionJugador1 <= 3) {
		marcadorJugador1 = marcador(puntuacionJugador1);
	}
	else if (puntuacionJugador1 == 4 && puntuacionJugador2 > 2) {
		marcadorJugador1 = marcador(puntuacionJugador1);
	}
	else {
		marcadorJugador1 = "[Punto]";
	}

	if (puntuacionJugador2 >= 0 && puntuacionJugador2 <= 3) {
		marcadorJugador2 = marcador(puntuacionJugador2);
	}
	else if (puntuacionJugador2 == 4 && puntuacionJugador1 > 2) {
		marcadorJugador2 = marcador(puntuacionJugador2);
	}
	else
	{
		marcadorJugador2 = "[Punto]";
	}

	cout << nombreJugador1 << "  " << marcadorJugador1 << "||" << marcadorJugador2 << "  " << nombreJugador2 << endl;
}

int elegirSaque(string jugador1, string jugador2)
{
	int saque;
	saque = rand() % 2;
	if (saque == 0)
	{
		cout << "Empieza sacando " << jugador1 << endl;
		return 1;
	}
	else if (saque == 1)
	{
		cout << "Empieza sacando " << jugador2 << endl;
		return 2;
	}
}

bool juegoEstaTerminado(int puntuacion1, int puntuacion2)
{
	//El juego se da por terminado si:
	// Puntuacion de jugador es 4, pero la puntuacion del otro jugador no sea 3
	//Puntuacion es 5

	if (puntuacion1 == 4 && puntuacion2 <= 2)//Jugador 1 gana
	{
		cout << "Gana jugador 1" << endl;
		return true;
	}
	else if (puntuacion2 == 4 && puntuacion1 <= 2)//Jugador 2 gana
	{
		cout << "Gana jugador 2" << endl;
		return true;
	}
	else if (puntuacion1 == 5)//Jugador 1 gana en ventaja
	{
		cout << "Gana jugador 1 en ventaja" << endl;
		return true;
	}
	else if (puntuacion2 == 5)//Jugador 2 gana en ventaja
	{
		cout << "Gana jugador 2 en ventaja" << endl;
		return true;
	}
	else
	{
		return false;
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


int partido(string nombreJugador1, string nombreJugador2, int jugadorSaque, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int velocidadJugador2, int habilidadJugador2) //Funcion que devuelva quien es el ganador del punto
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
			cout << nombreJugadorActual << " tira la bola fuera de la pista" << endl;
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
