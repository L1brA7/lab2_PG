#include <iostream>
#include <cstring>
using namespace std;

void field_creator(int** A, int N, int M);
void after_field(int **A, int N, int M);
void output_2D(int **A, int N, int M);
int scan(int** field, int x, int y);
void darvin_process(int **field, int **afterfield, int N, int M);

int main() {
	int number;
	cout << "Enter the number, 0 to close - "; cin >> number;
	while (number) {
		if (number == 1) {
			int N, M;
			cout << "Enter field's width - "; cin >> N; //вводим ширину поля
			cout << "Enter field's height - "; cin >> M; //вводим высоту поля

			int **field = new int *[N];     
			int **afterfield = new int *[N];
			for (int i = 0; i < M; i++) {
				field[i] = new int[M];
				afterfield[i] = new int[M];
			}

			field_creator(field, N, M);
			output_2D(field, N, M);
			cout << scan(field, 1, 1) << endl;

			cout << "Enter the number, 0 to close - " << endl; cin >> number;
		}
	}
	return 0;
}

//создание поля брани для "Игра жизнь"
void field_creator(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			A[i][j] = rand() % 2;
		}
	}
}

//вывод для двумерного массива N - строки, M - столбцы
void output_2D(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%i ", A[i][j]);
			if(j == N - 1) cout << endl;
		}
	}
}

//естественный отбор
void darvin_process(int **field, int **afterfield, int N, int M) {
	
}

/*
осмотр соседей клетки возвращает количество живых клеток вокруг проверяемой
если проверяется живая клетка, выводит количество - 1, т.к. саму клетку мы не считаем
если мертвая, то она не увеличивает количество, пожтому просто выводим его
*/
int scan(int **field, int x, int y) {
	int quantity = 0;
	for(int i = x - 1; i <= x + 1; i++){
		for(int j = y - 1; j <= y + 1; j++){
			if(field[i][j] == 1) quantity++;
		}
	}
	if(field[x][y] == 1) return quantity - 1;
	else return quantity;
}