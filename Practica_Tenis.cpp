#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;
const string m0 = "00";
const string m1 = "15";
const string m2 = "30";
const string m3 = "40";
const string m4 = "[Ventaja]";

void introducirDato() {
	int LIM_SUP_VEL, LIM_SUP_HAB;
	string jugador1, jugador2;
	cout << "Introduce el nombre del jugador 1: ";
	cin >> jugador1;
	cout << "Introduce el nombre del jugador 2: ";
	cin >> jugador2;
	cout << "Introduce la velocidad del jugador (Intervalo 1-3): ";
	cin >> LIM_SUP_VEL;
	cout << "Introduce la habilidad del jugador (Intervalo 1-3): ";
	cin >> LIM_SUP_HAB;
	if (LIM_SUP_VEL <= 3 && LIM_SUP_VEL >= 1) {
		cout << "Cargando...";
	}
	else if (LIM_SUP_HAB <= 3 || LIM_SUP_HAB >= 1) {
		cout << "Cargando...";
	}
	else {
		cout << "Valores introducidos incorrectos, pruebe otra vez" << endl;
	}
}

void marcador() {
	int puntuacion;
	cin >> puntuacion;
	if (puntuacion == 0) {
		cout << m0;
	}
	else if (puntuacion == 1) {
		cout << m1;
	}
	else if (puntuacion == 2) {
		cout << m2;
	}
	else if (puntuacion == 3) {
		cout << m3;
	}
	else if (puntuacion == 4) {
		cout << m4;
	}
}

void elegirSaque() {
	int saque;
	saque = rand() % 2;
	if (saque == 0) {
		cout << "Saca el jugador 1";
	}
	else if (saque == 1) {
		cout << "Saca el jugador 2";
	}
}
int main() {
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
	elegirSaque();
	return 0;
}