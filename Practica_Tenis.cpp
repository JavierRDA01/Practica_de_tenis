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

void introducirDato(string jugador1, string jugador2, int velocidad, int habilidad) {
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
	}

}

string marcador(int puntuacion) {
	if (puntuacion == 0) {
		cout << "00";
	}
	else if (puntuacion == 1) {
		cout << "15";
	}
	else if (puntuacion == 2) {
		cout << "30";
	}
	else if (puntuacion == 3) {
		cout << "40";
	}
	else if (puntuacion == 4) {
		cout << "[Ventaja]";
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
		}
		else {
			cout << "Error";
		}
	}
}
void elegirSaque(string jugador1, string jugador2) {
	int saque;
	saque = rand() % 2;
	if (saque == 0) {
		cout << "Saca " << jugador1;
	}
	else if (saque == 1) {
		cout << "Saca " << jugador2;
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
	int habilidad, velocidad, puntuacion, posicion_tenista, posicion_bola;
	string jugador1, jugador2;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
	introducirDato(jugador1, jugador2, habilidad, velocidad);
	elegirSaque(jugador1, jugador2);
	golpeoBola(habilidad, posicion_tenista);
	correTenista(posicion_tenista, posicion_bola, velocidad);
	marcador(puntuacion);
	return 0;
}
