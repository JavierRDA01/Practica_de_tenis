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

int elegirGanador() {

	int eleccion;
	eleccion = rand() % 3;
	while (true) {
		if (eleccion == 1) {
			cout << "Gana jugador 1" << endl;
			return 1;
		}
		else if (eleccion == 2) {
			cout << "Gana jugador 2" << endl;
			return 2;
		}
		else {
			cout << "No gana nadie" << endl;
			eleccion = rand() % 3;
		}
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
		cout << "El juego no esta acabado" << endl;
		return false;
	}
}

int main() {
	bool juegoTerminado = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
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
	
	if (habilidadJugador1 > 3 ||habilidadJugador1 < 1) {

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
	//cout << "Gana " << nombreJugador2 << endl;
	cout << "Empieza el partido entre " << nombreJugador1 << " y " << nombreJugador2 << endl;

	string breakTest;

	while (!juegoTerminado)
	{
		//elegirGanador();//Devuelve 1 o 2
		if (elegirGanador() == 1)
		{
			puntuacionJugador1++;
		}
		else
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
