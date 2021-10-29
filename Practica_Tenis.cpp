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
bool MODO_DEBUG = false;

int elegirGanador();

void mostrarMarcadorActual(int puntuacionJugador1, int puntuacionJugador2);

bool juegoEstaTerminado(int puntuacion1, int puntuacion2);

void introducirDato(string nombreJugador1, string nombreJugador2, int habilidadJugador1, int habilidadJugador2, int velocidadJugador1, int velocidadJugador2);

int correTenista(int posicion_tenista, int velocidad, int posicionBola);

int golpeoBola(int posicion_tenista, int habilidad, int posicion_bola);

int partido(string nombreJugador1, string nombreJugador2, int ganador, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int habilidadJugador2);

int main()
{

	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2;
	int puntuacionJugador1, puntuacionJugador2, ganador = 0, filaBola = 0;
	string nombreJugador1, nombreJugador2;
	bool JUEGO_TERMMINADO = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
	int posicionJugador1 = 4;
	int posicionJugador2 = 4, posicionBola = 4;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");

	introducirDato(nombreJugador1, nombreJugador2, habilidadJugador1, habilidadJugador2, velocidadJugador1, velocidadJugador2);

	//cout << "Gana " << nombreJugador2 << endl;
	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;

	string breakTest;



	while (JUEGO_TERMMINADO == false)
	{
		//elegirGanador();//Devuelve 1 o 2
		introducirDato(nombreJugador1, nombreJugador2, habilidadJugador1, habilidadJugador2, velocidadJugador1, velocidadJugador2);
		elegirGanador();
		ganador = partido(nombreJugador1, nombreJugador2, ganador, filaBola, posicionJugador1, posicionJugador2, posicionBola, velocidadJugador1, habilidadJugador1, habilidadJugador2);

		if (elegirGanador() == 1)
		{
			if (partido(nombreJugador1, nombreJugador2, ganador, filaBola, posicionJugador1, posicionJugador2, posicionBola, velocidadJugador1, habilidadJugador1, habilidadJugador2) == 1)
			{
				puntuacionJugador1++;
			}
		}
		else
		{
			if (partido(nombreJugador1, nombreJugador2, ganador, filaBola, posicionJugador1, posicionJugador2, posicionBola, velocidadJugador1, habilidadJugador1, habilidadJugador2) == 2)
			{
				puntuacionJugador2++;
			}
		}

		//Controlar deuce
		if (puntuacionJugador1 == 4 && puntuacionJugador2 == 4)
		{
			puntuacionJugador1 = 3;
			puntuacionJugador2 = 3;
		}

		mostrarMarcadorActual(puntuacionJugador1, puntuacionJugador2);
		JUEGO_TERMMINADO = juegoEstaTerminado(puntuacionJugador1, puntuacionJugador2);
		if (JUEGO_TERMMINADO == true)
		{
			puntuacionJugador1 = 0;
			puntuacionJugador2 = 0;
			JUEGO_TERMMINADO = false;
		}
		partido(nombreJugador1, nombreJugador2, ganador, filaBola, posicionJugador1, posicionJugador2, posicionBola, velocidadJugador1, habilidadJugador1, habilidadJugador2);
		cin >> breakTest;
	}


	cout << "El juego esta acabado" << endl;
}

void mostrarMarcadorActual(int puntuacionJugador1, int puntuacionJugador2)
{
	string marcadorJugador1, marcadorJugador2;

	if (puntuacionJugador1 == 3 && puntuacionJugador2 == 3)
	{
		cout << "Deuce" << endl;
		return;
	}

	if (puntuacionJugador1 == 0) {
		marcadorJugador1 = "00";
	}
	else if (puntuacionJugador1 == 1) {
		marcadorJugador1 = "15";
	}
	else if (puntuacionJugador1 == 2) {
		marcadorJugador1 = "30";
	}
	else if (puntuacionJugador1 == 3) {
		marcadorJugador1 = "40";
	}
	else if (puntuacionJugador1 == 4 && puntuacionJugador2 > 2) {
		marcadorJugador1 = "[Ventaja]";
	}
	else {
		marcadorJugador1 = "[Punto]";
	}

	if (puntuacionJugador2 == 0) {
		marcadorJugador2 = "00";
	}
	else if (puntuacionJugador2 == 1) {
		marcadorJugador2 = "15";
	}
	else if (puntuacionJugador2 == 2) {
		marcadorJugador2 = "30";
	}
	else if (puntuacionJugador2 == 3) {
		marcadorJugador2 = "40";
	}
	else if (puntuacionJugador2 == 4 && puntuacionJugador1 > 2) {
		marcadorJugador2 = "[Ventaja]";
	}
	else
	{
		marcadorJugador2 = "[Punto]";
	}

	cout << marcadorJugador1 << "||" << marcadorJugador2 << endl;
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
		cout << "El juego no esta acabado" << endl;
		return false;
	}
}

void introducirDato(string nombreJugador1, string nombreJugador2, int habilidadJugador1, int habilidadJugador2, int velocidadJugador1, int velocidadJugador2) {
	cout << "Introduce el nombre del jugador 1: ";
	cin >> nombreJugador1;
	cout << "Introduce el nombre del jugador 2: ";
	cin >> nombreJugador2;
	cout << "Introduce la velocidad del jugador 1 (Intervalo 1-3): ";
	cin >> velocidadJugador1;
	cout << "Introduce la habilidad del jugador 1 (Intervalo 1-3): ";
	cin >> habilidadJugador1;
	cout << "Introduce la velocidad del jugador 2 (Intervalo 1-3): ";
	cin >> velocidadJugador2;
	cout << "Introduce la habilidad del jugador 2 (Intervalo 1-3): ";
	cin >> habilidadJugador2;

	if (habilidadJugador1 > 3 || habilidadJugador1 < 1) {

		cout << "introduzca numeros entre el 1 y 3";
		exit(1);
	}
	else if (habilidadJugador2 > 3 || habilidadJugador2 < 1) {

		cout << "introduzca numeros entre el 1 y 3";
		exit(1);
	}
	else if (velocidadJugador1 > 3 || velocidadJugador1 < 1) {

		cout << "introduzca numeros entre el 1 y 3";
		exit(1);
	}
	else if (velocidadJugador2 > 3 || velocidadJugador2 < 1) {

		cout << "introduzca numeros entre el 1 y 3";
		exit(1);
	}

}

int correTenista(int posicionTenista, int velocidad, int posicionBola, string nombreJugador)
{
	int diferencia, diferenciaCasillas;
	diferencia = abs(posicionBola - posicionTenista);
	if (velocidad >= diferencia)
	{
		cout << nombreJugador << " llega sin problemas a la bola, ahora es él quien golpea" << endl;
		posicionBola = posicionTenista;

		return posicionTenista;
	}
	else //En el caso de que la velocidad fuera menor que el diferencia
	{
		if (posicionBola < posicionTenista) {
			posicionTenista = posicionTenista - velocidad;
			diferenciaCasillas = posicionBola + posicionTenista;
			cout << nombreJugador << " intenta llegar por la derecha pero se queda en la posicion " << posicionTenista << " a " << diferenciaCasillas << " de su objetivo y pierde el punto" << endl;

			return posicionTenista;// Posición adelantada
		}
		else if (posicionBola > posicionTenista) {
			posicionTenista = posicionTenista + velocidad;
			diferenciaCasillas = posicionBola - posicionTenista;
			cout << nombreJugador << " intenta llegar por la izquierda pero se queda en la posicion " << posicionTenista << " a " << diferenciaCasillas << " de su objetivo y pierde el punto" << endl;

			return posicionTenista;// Posición atrasada
		}
		else {
			if (posicionBola < posicionTenista) {
				return posicionTenista;// Punto para el otro jugador
			}
		}
	}
}

int golpeoBola(int posicion_tenista, int habilidad, int ANCHO_PISTA, int LIM_INF_HAB) {
	int diferencia, posicionDestino, acierto, desvio;
	double probabilidadExito;
	desvio = rand() % 2;
	acierto = rand() % 100; // número aleatorio 0 - 100 
	posicionDestino = rand() % (ANCHO_PISTA + 1); // posición destino de la bola
	diferencia = abs(posicionDestino - posicion_tenista); //
	if (diferencia <= habilidad)
	{
		return posicionDestino;
	}
	else if (diferencia > habilidad) // Si la diferencia entre la posicion del tenista y la posicion de destino de la bola es mayor que la habilidad 
	{
		probabilidadExito = (100 - ((posicionDestino - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB) * 100)); // porcentaje de acierto
		if (acierto <= probabilidadExito)
		{
			return posicionDestino;
		}
		else if (acierto > probabilidadExito)
		{
			if (desvio == 0) 
			{
				return posicionDestino + 1; // Desvío a la derecha
			}
			else if (desvio == 1) 
			{
				return posicionDestino - 1; // Desvío a la izquierda
			}
			}
		}
	}


int partido(string nombreJugador1, string nombreJugador2, int ganador,int velocidad, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int velocidadJugador2, int habilidadJugador2, int ANCHO_PISTA) //Funcion que devuelva quien es el ganador del punto
{
	int posicion_tenista, habilidad, posicion_bola, velocidad1, posicion_jugador;
	while (ganador != 1 || ganador != 2) //Bucle que se ejecuta hasta que haya un ganador del punto
	{
		if (filaBola == 1)// En el caso de que la bola la empiece jugando el jugador1
		{
			cout << "Saca " << nombreJugador1 << endl;
			posicionBola = golpeoBola(posicion_tenista, habilidad, posicion_bola); //La posicion de la bola pasará a la posición dada por la función golpeo bola

			if (posicionJugador2 < posicionBola) {
				posicionJugador2 = posicionJugador2 + velocidad;
				ganador = 2;

			}
			else if (posicionJugador2 > posicionBola) {
				posicionJugador2 = posicionJugador2 - velocidad;
				ganador = 2;
			}
			if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) //Si la bola sale fuera será punto para el jugador 2
			{
				cout << "Bola fuera" << endl;
				return 2;
			}
			else if (posicionBola > 0 && posicionBola < (ANCHO_PISTA + 1)) //Si la bola cae dentro del campo vemos si sigue el juego
			{
				posicionJugador2 = correTenista(posicionJugador2, velocidadJugador2, posicionBola, nombreJugador2); //La posición del Jugador2 viene dada por la función correTenista
					if (posicionJugador2 = posicionBola) {

					}
					else if (filaBola == 2) {
						cout << "Saca " << nombreJugador2 << endl;
						posicionBola = golpeoBola(posicion_tenista, habilidad, posicion_bola);
							filaBola = 2; //Si el jugador 2 llega a la bola significa que el jugador 2 pasa a golpear 

							if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) {
								cout << "Bola fuera" << endl;
								return 1;
							}
							else if (posicionBola > 0 || posicionBola < (ANCHO_PISTA + 1)) {
								posicionJugador1 = correTenista(posicionJugador1, velocidad1, posicion_jugador, nombreJugador1);
									if (posicionJugador1 = posicionBola) {

										filaBola = 1;

									}
									else if (posicionJugador1 != posicionBola) {

										if (posicionJugador1 < posicionBola) {
											posicionJugador1 = posicionJugador1 + velocidad;
												ganador = 1;

										}
										else if (posicionJugador1 > posicionBola) {
											posicionJugador1 = posicionJugador1 - velocidad;
											ganador = 1;
										}

									}

							}

							else if (posicionJugador2 != posicionBola) {
								return 1; //Si el jugador no llega a la bola es punto para el otro Jugador1
							}
					}
			}
				

			}
		}
	}
}
