#include <iostream>
#include <tuple>
using namespace std;

//функции общего назначения

/*
ввод ширины N и высоты M
первое значение - ширина, второе -  высота
*/
tuple<int, int> WH();
//выделение памяти по заданной ширине и высоте
int** memory_allocator(int N, int M);
//смена номера задания
void num_changer(int* N);
//вывод для двумерного массива N - строки, M - столбцы
void output_2D(int** A, int N, int M);

//функции для задания 1

//создание поля брани для "Игра жизнь"
void field_creator(int **A, int N, int M);
//тоже вывод 2D массива но конкретно для поля (просто не выводит мертвую зону)
void field_out(int** A, int N, int M);
//естественный отбор
void darvin_process(int **field, int **afterfield, int N, int M);
/*
осмотр соседей клетки: возвращает количество живых клеток вокруг проверяемой
если проверяется живая клетка, выводит (количество - 1), т.к. саму клетку мы не считаем
если мертвая, то она не увеличивает количество, пожтому просто выводим его
*/
int scan(int** field, int N, int M, int x, int y);

int main() {
	int number;
	cout << "Enter the number, 0 to close - "; cin >> number;
	while (number) {
		if (number == 1) {
			int N, M; tie(N, M) = WH(); N+=2, M+=2; //увеличиваем оба значения на 2 для создания мертвой зоны, которая потом не заполняется и не выводится
			int **field = memory_allocator(N, M);
			int **afterfield = memory_allocator(N, M);
			field_creator(field, N, M);
			field_out(field, N, M);
			cout << scan(field, N, M, 2, 2) << endl;
		}
		num_changer(&number);
	}
	return 0;
}

tuple<int, int> WH() {
	int N, M;
	cout << "Enter array's width - "; cin >> N;
	cout << "Enter array's height - "; cin >> M;
	return make_tuple(N, M);
}

int** memory_allocator(int N, int M) {
	int **A = new int *[N];
	for (int i = 0; i < M; i++) A[i] = new int[M];
	return A;
}

void num_changer(int* N) {
	cout << "Enter the number, 0 to close - " << endl;
	cin >> *N;
}

void output_2D(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%i ", A[i][j]);
			if (j == N - 1) cout << endl;
		}
	}
}

void field_creator(int** A, int N, int M) {
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			A[i][j] = rand() % 2;
		}
	}
}

void field_out(int **A, int N, int M) {
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			printf("%i ", A[i][j]);
			if (j == N - 2) cout << endl;
		}
	}
}

void darvin_process(int **field, int **afterfield, int N, int M) {
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++){

		}
	}
}

int scan(int **field, int N, int M, int x, int y) {
	int quantity = 0;
	x++, y++;
	for(int i = x - 1; i <= x + 1; i++){
		for(int j = y - 1; j <= y + 1; j++){
			if (field[i][j] == 1) quantity++;
		}
	}
	if (field[x][y] == 1) return quantity - 1;
	else return quantity;
}