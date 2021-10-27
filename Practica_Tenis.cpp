#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
using namespace std;





int golpeoBola(int posicion_tenista, int habilidad, int ANCHO_PISTA, int LIM_INF_HAB) {
	int absoluto, posicion_randm, acierto;
	double probabilidad_exito;
	acierto = rand() % 100; // número aleatorio 0 - 100 
	 // indica la distancia entre la posición del jugador que golpea y la posición destino de la bola
	posicion_randm = rand() % (ANCHO_PISTA + 1); // posición destino de la bola
	absoluto = abs(posicion_randm - posicion_tenista);
	return probabilidad_exito = (100 - ((posicion_randm - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB) * 100)); // porcentaje de acierto

}

int partido(int posicionJug1, int posicionJug2, int posicionBola) {
	
	int posicion_tenista, habilidad, ANCHO_PISTA, LIM_INF_HAB;


	if (golpeoBola( posicion_tenista, habilidad, ANCHO_PISTA, LIM_INF_HAB) == 0) {

	}
}


int elegirSaque(string jugador1, string jugador2) {
	int num;
	srand(time(NULL));
	num = rand() % 2;
	if (num == 0) {
		cout << "Saca " << jugador1;
		return 0;
	}
	else if (num == 1) {
		cout << "Saca " << jugador2;
		return 1;
	}
}


int correTenista(int posicionJugador1, int velocidad, int posicion_bola) {
	int absoluto;
	absoluto = abs(posicion_bola - posicionJugador1);
	if (velocidad >= absoluto) {
		posicion_bola = posicionJugador1;
		return 0;// Se sigue el juego
	}
	else {
		if (posicion_bola < posicionJugador1) {
			posicionJugador1 = posicionJugador1 - velocidad;
			return 1;// Punto para el otro jugador
		}
		else if (posicion_bola > posicionJugador1) {
			posicionJugador1 = posicionJugador1 + velocidad;
			return 2;// Punto para el otro jugador
		}
	}
}


int elegirGanador(int eleccion, int posicionJug1, int posicionJug2, int posicionBola) {
	while (true) {
		if ( partido(posicionJug1, posicionJug2, posicionBola) == 1) {
			cout << "Gana jugador 1" << endl;
			return 1;
		}
		else if (partido(posicionJug1, posicionJug2, posicionBola) == 2) {
			cout << "Gana jugador 2" << endl;
			return 2;
		}
		else {
			cout << "No gana nadie" << endl;
			eleccion = rand() % 3;
		}
	}
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
//int cambiarJugador1() {
	//if (elegirSaque() == 0) {
		//return elegirSaque() == 1;

	//}
//}
//int cambiarJugador2() {
	//if (elegirSaque() == 1) {
		//return elegirSaque() == 0;
	//}
//}
int main() {
	bool juegoTerminado = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
	int LIM_INF_VEL = 1, LIM_INF_HAB = 1;
	int LIM_SUP_VEL = 3, LIM_SUP_HAB = 3;
	int ANCHO_PISTA = 7;
	int posicionBola = 4, posicionJugador1 = 4, posicionJugador2 = 4;
	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2;
	int acierto = rand() % 100, posicion_randm = rand() % (ANCHO_PISTA + 1);
	int absoluto, posicion_tenista, habilidad;
	int eleccion, posicionJug1, posicionJug2, posicionBola;
	string nombreJugador1, nombreJugador2;
	string jugador1, jugador2;


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
	//cout << "Gana " << nombreJugador2 << endl;
	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;

	string breakTest;

	absoluto = abs(posicion_randm - posicion_tenista);

	while (!juegoTerminado)
	{
		if () {
			if (golpeoBola(posicion_tenista, habilidad, ANCHO_PISTA, LIM_INF_HAB) <= acierto) {
				posicionBola = posicionJugador1;
			}
			//elegirGanador();//Devuelve 1 o 2
			else {
				if (elegirGanador(eleccion, posicionJug1, posicionJug2, posicionBola) == 1)
				{
					puntuacionJugador1++;
				}
				else if (elegirGanador(eleccion, posicionJug1, posicionJug2, posicionBola) == 2)
				{
					puntuacionJugador2++;
				}
				else {
					cout << ";";
				}
				if (golpeoBola(posicion_tenista, habilidad, ANCHO_PISTA, LIM_INF_HAB) == 1) {

				}
				//Controlar deuce
				if (puntuacionJugador1 == 4 && puntuacionJugador2 == 4)
				{
					puntuacionJugador1 = 3;
					puntuacionJugador2 = 3;
				}
			}
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


	if (elegirSaque (jugador1, jugador2) == 0) {

		cout << " saca Jugador 1: ";
	}
	else {

		cout << " saca jugador 2: ";

	}
	int cambioFilaBola(int fila_bola) {
		if (fila_bola == 1) {
			fila_bola = 0;
			return fila_bola;
		}
		else if (fila_bola == 0) {
			fila_bola = 1;
			return fila_bola;
		}
	}

	if (elegirSaque(jugador1, jugador2) == 0) {

		fila_bola == 1;
	}
	else if (elegirSaque(jugador1, jugador2) == 1) {
		fila_bola == 2;
	}


	while (!juegoTerminado) {


		if (golpeoBola(posicion_tenista, habilidad, ANCHO_PISTA, LIM_INF_HAB) == 1) { // bola punto para el que saca

			cout << " punto para: " << nombreJugador1;
		}

		if (golpeoBola(posicion_tenista, habilidad, ANCHO_PISTA, LIM_INF_HAB) == 0) { // bola no es punto

			cout << " golpea: " << nombreJugador2;
		}
	}

	cout << "El juego esta acabado" << endl;
	return 0;
}
