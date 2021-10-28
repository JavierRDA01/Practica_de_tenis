#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
using namespace std;





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


}
int main() {
	bool juegoTerminado = false, JUEGO_ALEATORIO = false;
	int puntuacionJugador1 = 0, puntuacionJugador2 = 0;
	int LIM_INF_VEL = 1, LIM_INF_HAB = 1;
	int LIM_SUP_VEL = 3, LIM_SUP_HAB = 3;
	int ANCHO_PISTA = 7;
	int posicionBola = 4, posicionJugador1 = 4, posicionJugador2 = 4;
	int velocidadJugador1, habilidadJugador1, velocidadJugador2, habilidadJugador2;
	string nombreJugador1, nombreJugador2;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");

	introducirDato();
	
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
	int correTenista(int posicion_tenista, int velocidad, int posicionBola) {
		int absoluto;
		absoluto = abs(posicionBola - posicion_tenista);
		if (velocidad >= absoluto) {
			posicionBola = posicion_tenista;
			return posicion_tenista;
		}
		else {
			if (posicionBola < posicion_tenista) {
				return posicion_tenista;// Punto para el otro jugador
			}
			else if (posicionBola > posicion_tenista) {
				return posicion_tenista;// Punto para el otro jugador
			}
		}
	}
	int partido(string nombreJugador1, string nombreJugador2, int ganador, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int habilidadJugador2) {
		while (ganador != 1 || ganador != 2)
		{
			if (filaBola == 1) {
				cout << "Saca " << nombreJugador1 << endl;
				posicionBola = golpeoBola();

				if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) {
					cout << "Bola fuera" << endl;
					return 2;
				}
				else if (posicionBola > 0 || posicionBola < (ANCHO_PISTA + 1) 
				{
					posicionJugador2 = correTenista(posicionJugador2, velocidad2, posicion_jugador, nombreJugador2);
						if (posicionJugador2 = posicionBola) {
							
							filaBola = 2;

						}
						else (posicionJugador2 != posicionBola) {

							if (posicionJugador2 < posicionBola) {
								posicionJugador2 = posicionJugador2 + velocidad;
								ganador = 2;
								
							}
							else if(posicionJugador2 > posicionBola) {
								posicionJugador2 = posicionJugador2 - velocidad;
								ganador = 2;
							}

				}		
			else if (filaBola == 2) {
					cout << "Saca " << nombreJugador2 << endl;
					posicionBola = golpeoBola();

					if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) {
						cout << "Bola fuera" << endl;
						return 1;
					}
					else if (posicionBola > 0 || posicionBola < (ANCHO_PISTA + 1) {
						posicionJugador1 = correTenista(posicionJugador1, velocidad1, posicion_jugador, nombreJugador1);
							if (posicionJugador1 = posicionBola) {

								filaBola = 1;

							}
							else (posicionJugador1 != posicionBola) {

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

			}
		}
	cout << "El juego esta acabado" << endl;
	return 0;

}
	
