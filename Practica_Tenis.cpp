#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

const int LIM_INF_VEL = 1;
const int LIM_INF_HAB = 1;

void marcador(int PUN_JUG_1, int PUN_JUG_2, string jugador1, string jugador2, bool b) {
	if (PUN_JUG_1 == 0) {
		if (PUN_JUG_2 == 0) {
			cout << "00 00";
			b = false;
		}
		else if (PUN_JUG_2 == 1) {
			cout << "00 15";
			b = false;
		}
		else if (PUN_JUG_2 == 2) {
			cout << "00 30";
			b = false;
		}
		else if (PUN_JUG_2== 3) {
			cout << "00 40";
			b = false;
		}
	}
	else if (PUN_JUG_1 == 1) {
		if (PUN_JUG_2 == 0) {
			cout << "15 00";
			b = false;
		}
		else if (PUN_JUG_2 == 1) {
			cout << "15 15";
			b = false;
		}
		else if (PUN_JUG_2 == 2) {
			cout << "15 30";
			b = false;
		}
		else if (PUN_JUG_2 == 3) {
			cout << "15 40";
			b = false;
		}
	}
	else if (PUN_JUG_1 == 2) {
		if (PUN_JUG_2 == 0) {
			cout << "30 00";
			b = false;
		}
		else if (PUN_JUG_2 == 1) {
			cout << "30 15";
			b = false;
		}
		else if (PUN_JUG_2 == 2) {
			cout << "30 30";
			b = false;
		}
		else if (PUN_JUG_2 == 3) {
			cout << "30 40";
			b = false;
		}
	}
	else if (PUN_JUG_1 == 3) {
		if (PUN_JUG_2 == 0) {
			cout << "40 00";
			b = false;
		}
		else if (PUN_JUG_2 == 1) {
			cout << "40 15";
			b = false;
		}
		else if (PUN_JUG_2 == 2) {
			cout << "40 30";
			b = false;
		}
		else if (PUN_JUG_2 == 3) {
			cout << "40 40";
			b = false;
		}
	}
	else if (PUN_JUG_1 == 4 && PUN_JUG_2 == 3) {
		cout << "[Ventaja] 40";
		b = false;
		}
	else if (PUN_JUG_1 == 3 && PUN_JUG_2 == 4) {
		cout << "40 [Ventaja]";
		b = false;
	}
	else if (PUN_JUG_1 == 5 || (PUN_JUG_1 == 4 && PUN_JUG_2 < 3)){
		cout << "Gana " << jugador1;
		b = true;
	}
	else if (PUN_JUG_2 == 5 || (PUN_JUG_2 == 4 && PUN_JUG_1 < 3)) {
		cout << "Gana " << jugador2;
		b = true;
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

void servicio(string jugador1, string jugador2) {
	int serv;

}
int main() {
	int LIM_SUP_VEL, LIM_SUP_HAB, PUN_JUG_1, PUN_JUG_2;
	string jugador1, jugador2;
	bool b = false;
	srand(time(NULL));
	system("chcp 1252");
	system("cls");
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
	elegirSaque(jugador1, jugador2);
	marcador(PUN_JUG_1, PUN_JUG_2, jugador1, jugador2, b);
	while (b == true) {
		marcador(PUN_JUG_1, PUN_JUG_2, jugador1, jugador2, b);
	}
	return 0;
}
