#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;


const int puntuacionJugador1 = 0;
const int puntuacionJugador2 = 0;
const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;
const int LIM_SUP_VEL = 3;
const int LIM_SUP_HAB = 3;
const int ANCHO_PISTA = 7;
const int posicionBola = 4;
const int posicionJugador1 = 4;
const int posicionJugador2 = 4;
const bool JUEGO_TERMMINADO = false;
const bool JUEGO_ALEATORIO = false;
const bool MODO_DEBUG = false;

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
	int puntuacionJugador1, puntuacionJugador2, gandor, filaBola, posicionJugador1, posicionJugador2, posicionBola, ganador;
	string nombreJugador1, nombreJugador2;
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
		elegirGanador();
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


}

int correTenista(int posicion_tenista, int velocidad, int posicionBola)
{
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

int golpeoBola(int posicion_tenista, int habilidad, int posicion_bola) {
	int calle, probabilidad, desvio;
	double exito;
	string direccion;
	if (JUEGO_ALEATORIO == false)
	{
		cout << "elija la calle destino deseada: ";
		cin >> calle;
	}
	else if (JUEGO_ALEATORIO == true)
	{
		srand(time(NULL));
		calle = rand() % 8; // un numero aleatorio hasta 8 ya que es el numero de calles mas una que cuenta ya como fuera

	}

	int absoluto = abs(posicion_tenista - calle);

	if (absoluto > habilidad) // en el caso en el que no llegue el tenista ya que la distancia suoera a su habilidad
	{
		exito = 100 - (calle - habilidad) * 100 / (ANCHO_PISTA - 1) - LIM_INF_HAB;
		srand(time(NULL));
		probabilidad = rand() % 100;
		if (MODO_DEBUG == true)
		{
			cout << "la pobabilidad de exito es: " << exito;
		}

		if (exito > probabilidad)
		{
			if (MODO_DEBUG == true)
			{
				cout << "le dio el hijo de puta";
			}
			posicion_bola = calle;
		}
		else if (exito < probabilidad)
		{
			srand(time(NULL));
			desvio = rand() & 2;
			if (desvio == 0) // desvio de bola hacia la izquierda
			{
				direccion = "izquierda";
				posicion_bola = calle - 1;
			}
			else (desvio == 1) // desvio hacia la derecha
			{
				direccion = "derecha";
				posicion_bola = calle + 1;
			}
			if (MODO_DEBUG == true)
			{
				cout<<"la bola se ha desviado hacia la "
			}
		}

	}
	else if (absoluto <= habilidad)// en el caso en el que vaya a llegar si o si a golpear la bola 
	{
		posicion_bola = calle;

		if (MODO_DEBUG == true) 
		{
			cout << "la bola es golpeada con facilidad";
		}
			return posicion_bola;
	}

}

int partido(string nombreJugador1, string nombreJugador2, int ganador, int filaBola, int posicionJugador1, int posicionJugador2, int posicionBola, int velocidadJugador1, int habilidadJugador1, int habilidadJugador2) {
	while (ganador != 1 || ganador != 2)
	{
		if (filaBola == 1)
		{
			cout << "Saca " << nombreJugador1 << endl;
			posicionBola = golpeoBola(posicion_tenista, habilidad, posicion_bola);

			if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1))
			{
				cout << "Bola fuera" << endl;
				return 2;
				if (MODO_DEBUG = true)
				{
					cout << nombreJugador2 << "ha passado los limites del campo";
				}
			}
			else if (posicionBola > 0 || posicionBola < (ANCHO_PISTA + 1))
			{
				posicionJugador2 = correTenista(posicionJugador2, velocidad, posicion_tenista, nombreJugador2);
					if (posicionJugador2 = posicionBola)
					{

						filaBola = 2;

					}
					else (posicionJugador2 != posicionBola)
					{

						if (posicionJugador2 < posicionBola)
						{
							posicionJugador2 = posicionJugador2 + velocidad;
							ganador = 2;

						}
						else if (posicionJugador2 > posicionBola)
						{
							posicionJugador2 = posicionJugador2 - velocidad;
							ganador = 2;
						}
					}
			}
		}
		else if (filaBola == 2)
		{
			cout << "Saca " << nombreJugador2 << endl;
			posicionBola = golpeoBola();

			if (posicionBola <= 0 || posicionBola >= (ANCHO_PISTA + 1)) {
				cout << "Bola fuera" << endl;
				return 1;
			}
			else if (posicionBola > 0 || posicionBola < (ANCHO_PISTA + 1)) {
				posicionJugador1 = correTenista(posicionJugador1, velocidad, posicion_tenista, nombreJugador1);
					if (posicionJugador1 = posicionBola) {

						filaBola = 1;

					}
					else (posicionJugador1 != posicionBola)
					{

						if (posicionJugador1 < posicionBola)
						{
							posicionJugador1 = posicionJugador1 + velocidad;
							ganador = 1;

						}
						else if (posicionJugador1 > posicionBola)
						{
							posicionJugador1 = posicionJugador1 - velocidad;
							ganador = 1;
						}
					}
			}
		}


	}
}



	
