#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
using namespace std;




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
void introducirDato(int nombreJugador1, int nombreJugador2, int habilidadJugador1, int hablidadJugador2) {



}
int main() {
	bool juegoTerminado = false, JUEGO_ALEATORIO = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0, ganador = 0;
	int LIM_INF_VEL = 1, LIM_INF_HAB = 1;
	int LIM_SUP_VEL = 3, LIM_SUP_HAB = 3;
	int ANCHO_PISTA = 7;
	int posicionBola = 4, posicionJugador1 = 4, posicionJugador2 = 4, filaBola = 0;
	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2;
	string nombreJugador1, nombreJugador2;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
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

	//introducirDato();
	
	//cout << "Gana " << nombreJugador2 << endl;
	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;

	string breakTest;

	while (!juegoTerminado)
	{
		ganador = partido(nombreJugador1, nombreJugador2, ganador, filaBola, posicionJugador1, posicionJugador2, posicionBola, velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2, habilidadJugador2, ANCHO_PISTA);
		//elegirGanador();//Devuelve 1 o 2
		if (partido() == 1)
		{
			puntuacionJugador1++;
		}
		else if(partido() == 2)
		{
			puntuacionJugador2++;
		}

		//Controlar deuce
		if (puntuacionJugador1 == 4 && puntuacionJugador2 == 4)
		{
			puntuacionJugador1 = 3;
			puntuacionJugador2 = 3;
		}

		mostrarMarcadorActual(puntuacionJugador1, puntuacionJugador2);
		juegoTerminado = juegoEstaTerminado(puntuacionJugador1, puntuacionJugador2);
		if (juegoTerminado == true)
		{
			puntuacionJugador1 = 0;
			puntuacionJugador2 = 0;
			juegoTerminado = false;
		}
		cin >> breakTest;
	}
	cout << "El juego esta acabado" << endl;
	return 0;

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
			if (desvio == 0) {
				return posicionDestino + 1; // Desvío a la derecha
			}
			else if (desvio == 1) {
				return posicionDestino - 1; // Desvío a la izquierda
			}
		}
	}

}
int partido(string nombreJugador1, string nombreJugador2, int ganador, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int velocidadJugador2, int habilidadJugador2, int ANCHO_PISTA) //Funcion que devuelva quien es el ganador del punto
{
	while (ganador != 1 || ganador != 2) //Bucle que se ejecuta hasta que haya un ganador del punto
	{
		if (filaBola == 1)// En el caso de que la bola la empiece jugando el jugador1
		{
			cout << "Saca " << nombreJugador1 << endl;
			posicionBola = golpeoBola(); //La posicion de la bola pasará a la posición dada por la función golpeo bola

			if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) //Si la bola sale fuera será punto para el jugador 2
			{
				cout << "Bola fuera" << endl;
				return 2;
			}
			else if (posicionBola > 0 && posicionBola < (ANCHO_PISTA + 1) //Si la bola cae dentro del campo vemos si sigue el juego
			{
				posicionJugador2 = correTenista(posicionJugador2, velocidadJugador2, posicionBola, nombreJugador2); //La posición del Jugador2 viene dada por la función correTenista
					if (posicionJugador2 = posicionBola) {

						filaBola = 2; //Si el jugador 2 llega a la bola significa que el jugador 2 pasa a golpear 

					}
					else (posicionJugador2 != posicionBola) {
						return 1; //Si el jugador no llega a la bola es punto para el otro Jugador1
					}
			}
		}
		else if (filaBola == 2) {
			cout << "Saca " << nombreJugador2 << endl;
			posicionBola = golpeoBola();

			if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) { //Gana el Jugador1 por bola fuera
				cout << "Bola fuera" << endl;
				return 1;
			}
			else if (posicionBola > 0 || posicionBola < (ANCHO_PISTA + 1) {
				posicionJugador1 = correTenista(posicionJugador1, velocidadJugador1, posicionBola, nombreJugador1);
					if (posicionJugador1 = posicionBola)
					{
						filaBola = 1;
					}
					else (posicionJugador1 != posicionBola) //Gana el Jugador2 ya que el Jugador1 no llega
					{
						return 2;
					}
			}

		}
	}
}
