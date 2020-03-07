﻿#include <iostream>
#include <tuple>
#include <string>
using namespace std;

//функции общего назначения

//просто перенос строки(их много) - string skip, временная для удобства
//потом заменю все ss(); на printf("\n");
void ss();
/*
ввод ширины N и высоты M
первое значение - ширина, второе -  высота
*/
tuple<int, int> WH(int number);
//выделение памяти по заданной ширине и высоте (number влияет только на вывод)
int** int_memory_allocator(int N, int M);
//тоже выделение только для типа double
double **double_memory_allocator(int N, int M);
//смена номера задания
void num_changer(int *N);
//вывод для двумерного массива N - строки, M - столбцы
void output_2D(int** A, int N, int M);
//вывод для типа double
void double_output_2D(double** A, int N, int M);

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
если мертвая, то она не увеличивает количество, поэтому просто выводим его
*/
int scan(int** field, int x, int y);

//функции для задания 2

//ввод размерности матрицы
int matrix_size();
//создание 4 типов матрицы для теста (кроме заданной случайно)
void matrixes_creator(double **input_matrix, double **collin_matrix, double **zero_matrix, double **Gilbert_matrix, int N);
//заполнение матрицы случайным образом
void random_input(double **matrix, int N);

//функции для задания 3

//функция выводящая выстрелы в виде таблицы и заполняющая табло общих результатов
void shots(int **results, int N, int M);
//вывод специально для таблички results
void tab_out(int **results, int N);
//подсчет и вывод результатов
void res_out(int **results, int N);

int main() {
	int number;
	num_changer(&number);
	while (number) {
		if (number == 1) {
			int N, M; tie(N, M) = WH(number); N+=2, M+=2;
			int **field = int_memory_allocator(N, M);
			int **afterfield = int_memory_allocator(N, M);
			field_creator(field, N, M);
			darvin_process(field, afterfield, N, M);
			delete[] field, afterfield;
		}
		if (number == 2) {
			int N = matrix_size();
			double **input_matrix = double_memory_allocator(N, N);
			double **collin_matrix = double_memory_allocator(N, N);
			double **zero_matrix = double_memory_allocator(N, N);
			double **Gilbert_matrix = double_memory_allocator(N, N);
			matrixes_creator(input_matrix, collin_matrix, zero_matrix, Gilbert_matrix, N);
			ss();
			printf("\tINPUT MATRIX\n");
			double_output_2D(input_matrix, N, N);
			printf("\tCOLLIN MATRIX\n");
			double_output_2D(collin_matrix, N, N);
			printf("\tZERO MATRIX\n");
			double_output_2D(zero_matrix, N, N);
			printf("\tGILBERT MATRIX\n");
			double_output_2D(Gilbert_matrix, N, N);
		}
		if (number == 3) {
			int N, M; tie(N, M) = WH(number);
			int **results = int_memory_allocator(N, 2); //доска результатов, ширина всегда 2
			shots(results, N, M);
            tab_out(results, N);
            res_out(results, N);
            delete[] results;
        }
		num_changer(&number);
	}
	return 0;
}

void ss() {
	printf("\n");
}

tuple<int, int> WH(int number) {
	int N, M;
	string arr_type, width = "width", height = "height";
	if (number == 1) arr_type = "field";
	if (number == 3) {
        width = "shots";
        height = "shooters";
        arr_type = "scoreboard";
    }
    cout << "Enter the " + arr_type + "'s " + width + " - "; cin >> N;
    while (N < 0) {
		cout << "ERROR. Enter the positive " + arr_type + "'s " + width + " - "; cin >> N;
	}
	cout << "Enter the " + arr_type + "'s " + height +  " - ";
	cin >> M;
	while (M < 0) {
        cout << "ERROR. Enter the positive " + arr_type + "'s " + height + " - "; cin >> M;
	}
	ss();
	return make_tuple(M, N); //необходимый костыль, не обращайте внимания
}

int** int_memory_allocator(int N, int M) {
	int **A = new int *[N];
	for (int i = 0; i < N; i++) A[i] = new int[M];
	return A;
}

double **double_memory_allocator(int N, int M) {
	double **A = new double *[N];
	for (int i = 0; i < N; i++)
		A[i] = new double[M];
	return A;
}

void num_changer(int* N) {
	cout << "Enter the number or 0 to close - ";
	cin >> *N;
}

void output_2D(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) printf("%i\t ", A[i][j]);
		ss();
	}
}

void double_output_2D(double** A, int N, int M) {
	ss();
	for (int i = 0; i < N; i++) {
		printf("\t");
		for (int j = 0; j < M; j++) printf("%8.2lf\t ", A[i][j]);
		ss();
	}
	ss();
}

void field_creator(int** field, int N, int M) {
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			field[i][j] = rand() % 2;
		}
	}
}

void field_out(int **field, int N, int M) {
	for (int i = 1; i < N - 1; i++) {
        printf("\t");
        for (int j = 1; j < M - 1; j++) printf("%i ", field[i][j]);
		ss();
	}
	ss();
}

void darvin_process(int **field, int **afterfield, int N, int M) {
	int lifes, cycles, tick = 0;
	cout << "Enter the quantity of life cycles - "; cin >> cycles;
	while(cycles < 0){
		cout << "ERROR. Enter the positive quantity of life cycles - "; cin >> cycles;
	}
	ss();
	N--, M--;
	while (cycles) {
		for (int i = 1; i < N; i++) {
			for (int j = 1; j < M; j++) {
				lifes = scan(field, i, j);
				if (field[i][j] == 1) {
					if (lifes == 2 || lifes == 3) afterfield[i][j] = 1;
					else afterfield[i][j] = 0;
				}
				if (field[i][j] == 0) {
					if (lifes == 3) afterfield[i][j] = 1;
					else afterfield[i][j] = 0;
				}
			}
		}
		cycles--; tick++;
		cout << "\tFIELD " << tick << endl;
		ss();
		field_out(field, N + 1, M + 1);
		cout << "\tAFTERFIELD " << tick << endl;
		ss();
		field_out(afterfield, N + 1, M + 1);
		memcpy(afterfield, field, sizeof(int) * (N + 1) * (N + 1));
	}
}

int scan(int **field, int x, int y) {
	int quantity = 0;
	for(int i = x - 1; i <= x + 1; i++) {
		for(int j = y - 1; j <= y + 1; j++) {
			if (field[i][j] == 1) quantity++;
		}
	}
	if (field[x][y] == 1) return quantity - 1;
	else return quantity;
}

void matrixes_creator(double **input_matrix, double **collin_matrix, double **zero_matrix, double **Gilbert_matrix, int N) {
	int zero_line = rand() % N, collin_line = rand() % N - 1, input;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//printf("Input to index %2i|%2i  - ", i, j); cin >> input;
			input_matrix[i][j] = double(j);

			collin_matrix[i][j] = double(rand() % 280 - 140);
			if (i == collin_line + 1) collin_matrix[i][j] = collin_matrix[i - 1][j] * 2;

			zero_matrix[i][j] = double(rand() % 280 - 140);
			if (i == zero_line) zero_matrix[i][j] = 0.00;

			Gilbert_matrix[i][j] = 1.00 / double(i + j + 1);
		}
	}
}

int matrix_size() {
    int N;
    cout << "Enter the matrix size - "; cin >> N;
    while (N < 0) {
        cout << "ERROR. Enter the positive matrix size - "; cin >> N;
    }
	return N;
}

void random_input(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = double(rand() % 280 - 140); //от -140 до 140
        }
    }
}

void shots(int** results, int N, int M) {
	int maxshot, shotsum, shot;
	for (int i = 0; i < N; i++) {
		shotsum = maxshot = shot = rand() % 11;
		printf("\tShooter %2i:|%2i|", i + 1, shot);
		for (int j = 1; j < M; j++) {
			shotsum += shot = rand() % 11;
			printf("%2i|", shot);
			if (shot > maxshot) maxshot = shot; 
		}
		ss();
		results[i][0] = maxshot;
		results[i][1] = shotsum;
	}
	ss();
}

void tab_out(int **results, int N) {
    for (int i = 0; i < N; i++) {
        printf("\tShooter %2i:|Best shot - %2i|Score - %2i|", i + 1, results[i][0], results[i][1]);
        ss();
    }
}

void res_out(int **results, int N) {
    int maxshot = results[0][0], maxsum = results[0][1], champs = 1;
    string champion = "1", IsAre;
    for (int i = 1; i < N; i++) {
        if (maxshot == results[i][0]) champs++;
        if (maxshot < results[i][0]) {
            IsAre = " IS";
            maxshot = results[i][0];
            champion = "SHOOTER " + to_string(i + 1);
            champs = 1;
        }
    }
    if (champs != 1) {
        champs = 1;
        for (int i = 1; i < N; i++) {
            if (maxsum == results[i][1]) {
                IsAre = "S ARE:";
                champion += "SHOOTER " + to_string(i + 1) + " ";
            }
            if (maxsum < results[i][1]) {
                IsAre = " IS";
                maxsum = results[i][1];
                champion = "SHOOTER " + to_string(i + 1) + " ";
            }
        }
    }
    printf("\n\tOUR WINNER%s %s\n\n", IsAre.c_str(), champion.c_str());
}
