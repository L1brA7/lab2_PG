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
int scan(int** field, int x, int y);

int main() {

	int number;
	num_changer(&number);
	while (number) {
		if (number == 1) {
			int N, M; tie(N, M) = WH(); N+=2, M+=2;
			int **field = memory_allocator(N, M);
			int **afterfield = memory_allocator(N, M);
			field_creator(field, N, M);
			darvin_process(field, afterfield, N, M);
			delete[] field, afterfield;
		}
		num_changer(&number);
	}

	return 0;
}

tuple<int, int> WH() {
	int N, M;
	cout << "Enter the array's height - "; cin >> N;
	while (N < 0) {
		cout << "ERROR. Enter the positive array's height - ";
		cin >> N;
	}
	cout << "Enter the array's width - "; cin >> M;
	while (M < 0) {
		cout << "ERROR. Enter the positive array's width - ";
		cin >> M;
	}
	printf("\n");
	return make_tuple(N, M);
}

int** memory_allocator(int N, int M) {
	int **A = new int *[N];
	for (int i = 0; i < N; i++) A[i] = new int[M];
	return A;
}

void num_changer(int* N) {
	cout << "Enter the number or 0 to close - ";
	cin >> *N;
}

void output_2D(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) printf("%i\t ", A[i][j]);
		printf("\n");
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
		for (int j = 1; j < M - 1; j++) printf("%i ", A[i][j]);
		printf("\n");
	}
	printf("\n");
}

void darvin_process(int **field, int **afterfield, int N, int M) {
	int lifes, cycles, tick = 0;
	cout << "Enter the quantity of life cycles - "; cin >> cycles;
	while(cycles < 0){
		cout << "ERROR. Enter the positive quantity of life cycles - "; cin >> cycles;
	}
	N--, M--;
	while (cycles) {
		for (int i = 1; i < N; i++) {
			for (int j = 1; j < M; j++) {
				lifes = scan(field, i, j);
				if (field[i][j] == 1) {
					if (lifes == 2 || lifes == 3) afterfield[i][j] = 1;
					else afterfield[i][j] = 0;
				}
				if (field[i][j] == 0)
					if (lifes == 3) afterfield[i][j] = 1;
					else afterfield[i][j] = 0;
			}
		}
		cycles--; tick++;
		cout << "field - " << tick << endl;
		field_out(field, N + 1, M + 1);
		cout << "afterfield - " << tick << endl;
		field_out(afterfield, N + 1, M + 1);
		memcpy(afterfield, field, sizeof(int) * (N + 1) * (N + 1));
	}
}

int scan(int **field, int x, int y) {
	int quantity = 0;
	for(int i = x - 1; i <= x + 1; i++){
		for(int j = y - 1; j <= y + 1; j++){
			if (field[i][j] == 1) quantity++;
		}
	}
	if (field[x][y] == 1) return quantity - 1;
	else return quantity;
}