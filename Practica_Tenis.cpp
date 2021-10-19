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


string marcador(int puntuacion_jug_1, int puntuacion_jug_2) {
	if (puntuacion_jug_1 == 0) {
		cout << "00";
	}
	else if (puntuacion_jug_1 == 1) {
		cout << "15";
	}
	else if (puntuacion_jug_1 == 2) {
		cout << "30";
	}
	else if (puntuacion_jug_1 == 3) {
		cout << "40";
	}
	else if (puntuacion_jug_1 == 4) {
		cout << "[Ventaja]";
	}
	if (puntuacion_jug_2 == 0) {
		cout << "00";
	}
	else if (puntuacion_jug_2 == 1) {
		cout << "15";
	}
	else if (puntuacion_jug_2 == 2) {
		cout << "30";
	}
	else if (puntuacion_jug_2 == 3) {
		cout << "40";
	}
	else if (puntuacion_jug_2 == 4) {
		cout << "[Ventaja]";
	}
}
void elegirGanador(string jugador1, string jugador2, int puntuacion_jug_1, int puntuacion_jug_2) {
	int eleccion;
	eleccion = rand() % 3;
	while (eleccion != 0) {
		if (eleccion == 1) {
			cout << "Gana " << jugador1 << endl;
			puntuacion_jug_1++;
			cout << puntuacion_jug_1 << "||" << puntuacion_jug_2 << endl;
		}
		else if (eleccion == 2) {
			cout << "Gana " << jugador2 << endl;
			puntuacion_jug_2++;
			cout << puntuacion_jug_1 << "||" << puntuacion_jug_2 << endl;
		}
		else if (eleccion == 0) {
			cout << "No gana nadie" << endl;
			cout << puntuacion_jug_1 << "||" << puntuacion_jug_2 << endl;
		}
	}
}
int golpeoBola(int posicion_tenista, int habilidad) {
	int absoluto, posicion_randm, acierto;
	double probabilidad_exito;
	acierto = rand() % 100;
	posicion_randm = rand() % (ANCHO_PISTA - posicion_tenista);
	absoluto = abs(posicion_tenista - habilidad);
	if (posicion_randm > habilidad) {
		probabilidad_exito = (100 - ((posicion_randm - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB) * 100));
		if (acierto < probabilidad_exito) {
			cout << "Acierto";
			return 0;
		}
		else {
			cout << "Error";
			return 0;
		}
	}
	else {
		return 0;
	}
}
void elegirSaque(string jugador1, string jugador2) {

	int num;

	srand(time(NULL));

	num = rand() % 100;

	if (num <= 50) {

		cout << "Saca " << jugador1;

	}

	else{

		cout << "Saca " <<jugador2;
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
