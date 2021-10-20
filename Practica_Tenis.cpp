#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;
const int LIM_SUP_VEL = 3;
const int LIM_SUP_HAB = 3;
const int ANCHO_PISTA = 7;
int posicion_bola = 4;
int posicion_tenista = 4;


void marcador(int puntuacion_jug_1, int puntuacion_jug_2) {
	string puntuacion1, puntuacion2;
	if (puntuacion_jug_1 == 0) {
		puntuacion1 =  "00";
	}
	else if (puntuacion_jug_1 == 1) {
		puntuacion1 = "15";
	}
	else if (puntuacion_jug_1 == 2) {
		puntuacion1 = "30";
	}
	else if (puntuacion_jug_1 == 3) {
		puntuacion1 = "40";
	}
	else if (puntuacion_jug_1 == 4) {
		puntuacion1 = "[Ventaja]";
	}
	if (puntuacion_jug_2 == 0) {
		puntuacion2 = "00";
	}
	else if (puntuacion_jug_2 == 1) {
		puntuacion2 = "15";
	}
	else if (puntuacion_jug_2 == 2) {
		puntuacion2 = "30";
	}
	else if (puntuacion_jug_2 == 3) {
		puntuacion2 = "40";
	}
	else if (puntuacion_jug_2 == 4) {
		puntuacion2 = "[Ventaja]";
	}
	cout << puntuacion1 << "||" << puntuacion2;
}
void elegirGanador(string jugador1, string jugador2, int puntuacion_jug_1, int puntuacion_jug_2) {
	int eleccion;
	eleccion = rand() % 3;
	while (eleccion != 0) {
		if (eleccion == 1) {
			cout << "Gana " << jugador1 << endl;
			puntuacion_jug_1++;
		}
		else if (eleccion == 2) {
			cout << "Gana " << jugador2 << endl;
			puntuacion_jug_2++;
		}
		else if (eleccion == 0) {
			cout << "No gana nadie" << endl;
		}
	}
}

int golpeoBola(int posicion_tenista1, int posicion_tenista2, int habilidad, int posicion_bola, int velocidad) {
	int absoluto, acierto;
	double probabilidad_exito;
	acierto = rand() % 100; // número aleatorio 0 - 100 
	posicion_bola = rand() % (ANCHO_PISTA + 1); posición destino de la bola
	absoluto = abs(posicion_tenista - habilidad);  // indica la distancia entre la posición del jugador que golpea y la posición destino de la bola

if (posicion_bola > habilidad) { // Si la distancia es mayor que la habilidad, entonces habrá un porcentaje de acierto
		probabilidad_exito = (100 - ((posicion_bola - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB) * 100));
		if (acierto < probabilidad_exito) {
			cout << "Acierto";
		}
		else {
			cout << "Error";
		}
	}

if (posicion_bola > ANCHO_PISTA) { // en caso de que la bola de salga del campo

	cout << "punto para el receptor";

}
	if (posicion_bola = posicion_tenista1) { // en el caso en el que el jugador1 hay allegado a golpear la bola

		posicion_tenista1 = posicion_bola;
	}

	else if (posicion_bola = posicion_tenista2) {

		posicion_tenista2 = posicion_bola;
	}



	else if (posicion_tenista1 != posicion_bola) {

		correTenista(posicion_tenista, posicion_bola, velocidad);

		posicion_tenista1 = posicion_bola - velocidad;

		cout << "punto para el que golpeo";
	}

	else if (posicion_tenista2 != posicion_bola) {

		correTenista(posicion_tenista, posicion_bola, velocidad);

		posicion_tenista2 = posicion_bola - velocidad;

		cout << "punto para el que golpeo";
	}
}

void elegirSaque(string jugador1, string jugador2) {
	int num, saque;
	srand(time(NULL));
	num = rand() % 100;
	if (num <= 50) {
		cout << "Saca " << jugador1;
		saque = 0;
	}
	else {
		cout << "Saca " << jugador2;
		saque = 1;
	}
}


int correTenista(int posicion_tenista, int velocidad, int posicion_bola) {
	int absoluto;
	absoluto = abs(posicion_bola - posicion_tenista);
	if (velocidad >= absoluto) {
		posicion_bola = posicion_tenista;
		return posicion_tenista, posicion_bola;
	}
	else {
		if (posicion_bola < posicion_tenista) {
			posicion_tenista = posicion_tenista - velocidad;
			return posicion_tenista, posicion_bola;
		}
		else if (posicion_bola > posicion_tenista) {
			posicion_tenista = posicion_tenista + velocidad;
			return posicion_tenista, posicion_bola;
		}
	}
}
int main() {
	int habilidad, velocidad, puntuacion_jug_1, puntuacion_jug_2, posicion_tenista, posicion_bola;
	string jugador1, jugador2;
	puntuacion_jug_1 = 0;
	puntuacion_jug_2 = 0;
	posicion_tenista = 4;
	posicion_bola = 4;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
	cout << "Introduce el nombre del jugador 1: ";
	cin >> jugador1;
	cout << "Introduce el nombre del jugador 2: ";
	cin >> jugador2;
	cout << "Introduce la velocidad del jugador (Intervalo 1-3): ";
	cin >> velocidad;
	cout << "Introduce la habilidad del jugador (Intervalo 1-3): ";
	cin >> habilidad;
	if (habilidad >= LIM_INF_HAB && habilidad <= LIM_SUP_HAB) {
		cout << "Cargando...";
	}
	else if (velocidad <= LIM_INF_VEL && velocidad <= LIM_SUP_VEL) {
		cout << "Cargando...";
	}
	else {
		cout << "Valores introducidos incorrectos, pruebe otra vez" << endl;

		exit(1);
	}
	elegirSaque(jugador1, jugador2);
	golpeoBola(habilidad, posicion_tenista);
	correTenista(posicion_tenista, posicion_bola, velocidad);
	marcador(puntuacion_jug_1, puntuacion_jug_2);
	return 0;
}
