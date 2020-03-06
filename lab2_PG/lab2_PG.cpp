#include <iostream>
#include <tuple>
using namespace std;

void num_changer(int *N);
tuple<int, int> WH();
int **memory_allocator(int N, int M);
void field_creator(int **A, int N, int M);
void output_2D(int **A, int N, int M);
int scan(int** field, int N, int M, int x, int y);
void darvin_process(int **field, int **afterfield, int N, int M);

int main() {
	int number;
	cout << "Enter the number, 0 to close - "; cin >> number;
	while (number) {
		if (number == 1) {
			int N, M; tie(N, M) = WH();
			int **field = memory_allocator(N, M);
			int **afterfield = memory_allocator(N, M);
			field_creator(field, N, M);
			output_2D(field, N, M);
			cout << scan(field, N, M, 1, 1) << endl;
			num_changer(&number);
		}
	}
	return 0;
}

/*
ввод ширины N и высоты M
первое значение - ширина, второе -  высота
*/
tuple<int, int> WH() {
	int N, M;
	cout << "Enter array's width - "; cin >> N;
	cout << "Enter array's height - "; cin >> M;
	return make_tuple(N, M);
}

//выделение памяти по заданной ширине и высоте
int** memory_allocator(int N, int M) {
	int **A = new int *[N];
	for (int i = 0; i < M; i++) A[i] = new int[M];
	return A;
}

//смена номера задания
void num_changer(int* N) {
	cout << "Enter the number, 0 to close - " << endl;
	cin >> *N;
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
			if (j == N - 1) cout << endl;
		}
	}
}

//естественный отбор
void darvin_process(int **field, int **afterfield, int N, int M) {
	
}

/*
осмотр соседей клетки: возвращает количество живых клеток вокруг проверяемой
если проверяется живая клетка, выводит (количество - 1), т.к. саму клетку мы не считаем
если мертвая, то она не увеличивает количество, пожтому просто выводим его
*/
int scan(int **field, int N, int M, int x, int y) {
	int quantity = 0;

	//цикл для "внутреполевых" клеток
	if (x > 0 && y > 0 && x < N - 1 && y < M - 1) {
		for(int i = x - 1; i <= x + 1; i++){
			for(int j = y - 1; j <= y + 1; j++){
				if (field[i][j] == 1) quantity++;
			}
		}
	}


	if (field[x][y] == 1) return quantity - 1;
	else return quantity;
}