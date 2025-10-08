#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//tamaño del tablero
#define TAB 8
//Posibles movimientos del caballo en sentido x y y y en forma de L
int movX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int movY[8] = {1, 2, 2, 1, -1, -2, -2, -1};
//Función para mostrarr el tablero
void mostrarTablero(int tablero[TAB][TAB], int x, int y) {
	for (int i = 0; i < TAB; i++) {
		for (int j = 0; j < TAB; j++) {
			if (i == x && j == y)
				printf(" 🐴 "); //caballo
			else if (tablero[i][j] == 0)
				printf(" ▢ ") ;//Casilla vacía
			else
				printf("%2d ", tablero[i][j]); //orden y número de casilla visitada
		}
		printf("\n");
	}
} //Función que verifica que el movimiento no se salga del tablero y que no se haya visitado esa casilla anteriormente.
int movValido(int x, int y, int tablero[TAB][TAB]) { 
	return(x >= 0 && x < TAB && y >= 0 && y < TAB && tablero[x][y] == 0);
}
int movimientosPosibles(int x, int y, int tablero[TAB][TAB]) {
	int valido = 0 ;
	printf("\nMovimientos que puedes realizar:\n"); //Evalúa las posibilidades y si estas se salen o no del tablero
	for (int i = 0; i < 8; i++) {
		int nx = x + movX[i];
		int ny = y + movY[i];
		if (movValido(nx, ny, tablero)) {
			valido++;
			printf("%d) (%d, %d)\n", i + 1, nx, ny);
		} else {
			printf("%d) No válido\n", i + 1);
		}
	}
	return valido;
}
	int main() {
		setbuf(stdout, NULL) ;

		int tablero[TAB][TAB]= {0}; //Se crea el tamaño del tablero establecido por TAB o sea 8
		int x, y, movimientos = 1;
		srand(time(NULL)); //Posición aleatoria en el tablero

		x = rand() % TAB; //rand para obtener posición aleatoria tanto en x como en y 
		y = rand() % TAB;
		tablero[x][y] = movimientos;

		printf("( ﾉ ﾟｰﾟ)ﾉ Bienvenido al problema del caballo. ¿Podrás resolverlo?\n");
		printf("Inicias en la posición (%d, %d)\n", x, y);

		while (1) { //se repite hasta el break o ya que se consiga la victoria o derrota.
			mostrarTablero(tablero, x, y);
			int posibles = movimientosPosibles(x, y, tablero);
//Si ya no hay movimientos
			if (posibles == 0) {
				printf("\nTe quedaste sin movimientos!.\n");
				printf("Visitaste %d casillas.\n", movimientos);
			break;
			}
//Scan para que el usuario ingrese el movimiento que quiere
			int opcion;
			printf("\n Selecciona tu siguiente movimiento (elige un número del 1 al 8)\n");
			scanf("%d", &opcion);
//valida que no sea un número no permitido
			if (opcion < 1 || opcion > 8) {
				printf("No puedes hacer este movimiento. `(*>﹏<*)′\n");
				continue ;
			}
//Calcula la nueva posición del caballo, se utiliza -1 por que los arreglos empiezan en 0
			int nx = x + movX[opcion - 1];
			int ny = y + movY[opcion - 1];

			if (!movValido(nx, ny, tablero)) {
				printf("No puedes hacer este movimiento. `(*>﹏<*)′\n");
				continue;
			}
//Incrementa el contador de movimientos y actualiza la ubicación del caballo en el tablero
			x = nx;
			y = ny;
			movimientos++;
			tablero[x][y] = movimientos;
//Establece que si se llega a 64 movimientos se toma como victoria
			if (movimientos == TAB * TAB) {
				mostrarTablero(tablero, x, y);
				printf("\nRecorriste todas las casillas, ¡Felicidades! Venciste el juego.\n");
				break;
			}
		}

	return 0;
	}
