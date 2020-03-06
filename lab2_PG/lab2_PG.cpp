#include <iostream>
#include <cstring>
using namespace std;

void field_creator(int** A, int N, int M);
void A_output(int **A, int N, int M);

int main() {
	int N, M; cout << "Enter field's width - "; cin >> N; //вводим ширину поля
	cout << "Enter field's height - "; cin >> M; //вводим высоту поля
	int** field = new int* [N];
	for (int i = 0; i < M; i++) field[i] = new int[M];
	field_creator(field, N, M);
	A_output(field, N, M);
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
void A_output(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%i\t", A[i][j]);
			if(j == N - 1) cout << endl;
		}
	}
}
