#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
using namespace std;

//функции общего назначения

//просто перенос строки
void ss();
//просто табуляция
void tab();
//ДЛИИИИИИИИИИИИИИИИИИИИИИИИИИИННАЯ ЛИНИЯ
void line();
/*
ввод ширины N и высоты M
первое значение - ширина, второе -  высота
*/
tuple<int, int> WH(int number);
//выделение памяти с помощью malloc для дальнейшего изменения размерностей
int **int_malloc(int N, int M);
//выделение памяти по заданной ширине и высоте (number влияет только на вывод)
int **int_memory_allocator(int N, int M);
//тоже выделение только для типа double
double **double_memory_allocator(int N, int M);
//смена номера задания
void num_changer(int *N);
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
если мертвая, то она не увеличивает количество, поэтому просто выводим его
*/
int scan(int** field, int x, int y);
//подсчет живых и мертвых, возвращает кортеж из значений
tuple<int, int> counter(int **field, int N, int M);

//функции для задания 2

//действия для задания 2
void task_2(double **matrix, int N, string matrix_name);
//проверка на нули на диагонали
bool curse_check(double **matrix, int N);
//ввод размерности матрицы
int matrix_size();
//создание 4 типов матрицы для теста (кроме заданной случайно)
void matrixes_creator(double **input_matrix, double **collin_matrix, double **zero_matrix, double **Gilbert_matrix, int N);
//заполнение матрицы случайным образом
void random_input(double **matrix, int N);
//нахождение определителя раскладываением по строке
double det(double** matrix, int N, int col = 0);
//прямой ход метода Гаусса
void gauss_str_step(double **matrix, int N);
//обратный ход Гаусса
void gauss_back_step(double **matrix, double *x_vect, int N);
//нахождение определителя по диагональным элементам
double diag_det(double **matrix, int N);
//вычисление навязки
void checker(double **matrix, double *x_vect, int N);
//вывод для матриц
void matrix_output(double **A, int N, int M);
//копирование матрицы
void matrix_copy(double **matrix_1, double **matrix_2, int N);

//функции для задания 3

//функция выводящая выстрелы в виде таблицы и заполняющая табло общих результатов
void shots(int **results, int N, int M);
//вывод специально для таблички results
void tab_out(int **results, int N);
//подсчет и вывод результатов
void res_out(int **results, int N);

//функции для задания 1 ВАРИАНТ 12 (в программе - заданние 4)

//функция заполнения матрицы
void matrix_creator(int **matrix, int N);
//действия с матрицой из задания 4
void task_4(int **matrix, int N);

//функции для задания 2 ВАРИАНТ 12 (в программе - заданние 5)

//заполнение файла случайными числами
void random_numbers();
//умножение матрицы на число(вектора тоже можно умножать, просто соответствующая размерность = 1)
void matrix_x_number(int **matrix, int num, int N, int M);
//сумма или разность матрицы 1 и 2, изменяет первую матрицу(и возвращает её), последним числом ввести 1 для суммы и 0 для разности
int** matrix_sum_diff(int** matrix_1, int** matrix_2, int N, int M, bool sign);
//произведение матрицы на матрицу(аналогично вектор на вектор, просто одна из размерностей - 1)
int **matrix_product(int **matrix_1, int **matrix_2, int N1, int M1, int N2, int M2);
//ввод матрицы(аналогично вектора) из файла
void file_input(int **matrix, int N, int M, ifstream& numbers);
//транспонирование
int **transpon(int **matrix, int N, int M);
//подсчет произведения строки i первой матрицы на столбец j второй(для произведения матриц)
int result_calc(int **matrix1, int **matrix2, int M1, int N2, int I, int J);

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
			for (int i = 0; i < N; i++) {
				delete[] afterfield[i];
				delete[] field[i];
			}
			delete[] afterfield;
			delete[] field;
		}
		if (number == 2) {
			int N = matrix_size(), M = N + 1;
			double **input_matrix = double_memory_allocator(N, M);
			double **collin_matrix = double_memory_allocator(N, M);
			double **zero_matrix = double_memory_allocator(N, M);
			double **Gilbert_matrix = double_memory_allocator(N, M);
			matrixes_creator(input_matrix, collin_matrix, zero_matrix, Gilbert_matrix, N);
			task_2(input_matrix, N, "INPUT MATRIX");
			task_2(collin_matrix, N, "COLLIN MATRIX");
			task_2(zero_matrix, N, "ZERO MATRIX");
			task_2(Gilbert_matrix, N, "GILBERT MATRIX");
		}
		if (number == 3) {
			int N, M; tie(M, N) = WH(number);
			int **results = int_memory_allocator(N, 2); //доска результатов, ширина всегда 2
			shots(results, N, M);
            tab_out(results, N);
            res_out(results, N);
			for (int i = 0; i < M; i++) {
				delete[] results[i];
			}
            delete[] results;
        }
		if (number == 4) {
			int N = matrix_size();
			int **matrix = int_memory_allocator(N, N);
			matrix_creator(matrix, N);
			output_2D(matrix, N, N);
			task_4(matrix, N);
			for (int i = 0; i < N; i++) {
				delete[] matrix[i];
			}
            delete[] matrix;
		}
		if (number == 5) {
			ifstream numbers;
			numbers.open("numbers.txt");

			int N, M; tie(N, M) = WH(number);
			int **matrix_A = int_malloc(N, N);
			int **matrix_C = int_malloc(M, N);
			int **vector_B = int_malloc(N, 1);
			int **vector_D = int_malloc(M, 1);
			int **result_matrix;
			random_numbers();

			file_input(matrix_A, N, N, numbers);
			file_input(matrix_C, M, N, numbers);
			file_input(vector_B, N, 1, numbers);
			file_input(vector_D, M, 1, numbers);

			printf("\tMATRIX_A - %ix%i\n\n", N, N);
			output_2D(matrix_A, N, N);
			printf("\tMATRIX_C - %ix%i\n\n", M, N);
			output_2D(matrix_C, M, N);
			printf("\tVECTOR_B - %ix%i\n\n", N, 1);
			output_2D(vector_B, N, 1);
			printf("\tVECTOR_D - %ix%i\n\n", M, 1);
			output_2D(vector_D, M, 1);

			printf("\tMATRIX_A x -2\n\n");
			matrix_x_number(matrix_A, -2, N, N);
			output_2D(matrix_A, N, N);

			printf("\tT_VECTOR_D - %ix%i\n\n", 1, M);
			vector_D = transpon(vector_D, M, 1);
			output_2D(vector_D, 1, M);

			result_matrix = matrix_product(vector_B, vector_D, N, 1, 1, M);
			printf("\tVECTOR_B * T_VECTOR_D - %ix%i\n\n", N, M);
			output_2D(result_matrix, N, M);

			result_matrix = matrix_product(result_matrix, matrix_C, N, M, M, N);
			printf("\tVECTOR_B * T_VECTOR_D * MATRIX_C - %ix%i\n\n", N, N);
			output_2D(result_matrix, N, N);

			printf("\tMATRIX_A x -2 - (VECTOR_B * T_VECTOR_D) * MATRIX_C - %ix%i\n\n", N, N);
			output_2D(matrix_sum_diff(matrix_A, result_matrix, N, N, 0), N, N);

			numbers.close();
			for (int i = 0; i < N; i++) {
				free(matrix_A[i]);
			}
			free(matrix_A);
			for (int i = 0; i < M; i++) {
				free(matrix_C[i]);
			}
			free(matrix_C);
			for (int i = 0; i < N; i++) {
				delete[] result_matrix[i];
			}
			delete[] result_matrix;
		}
		num_changer(&number);
	}
	return 0;
}

void ss() {
	printf("\n");
}

void tab() {
	printf("\t");
}

void line() {
	printf("-------------------------------------------------------------------------------------------------\n\n");
}

tuple<int, int> WH(int number) {
	int N, M;
	string arr_type = "matrix", width = "width", height = "height";
	if (number == 1) arr_type = "field";
	if (number == 3) {
        width = "shots";
        height = "shooters";
        arr_type = "scoreboard";
    }
	ss();
	tab();
	cout << "Enter the " + arr_type + "'s " + width + " - "; cin >> N;
    while (N < 1) {
		tab();
		cout << "ERROR. Enter the positive " + arr_type + "'s " + width + " - "; cin >> N;
	}
	tab();
	cout << "Enter the " + arr_type + "'s " + height +  " - ";
	cin >> M;
	while (M < 1) {
		tab();
		cout << "ERROR. Enter the positive " + arr_type + "'s " + height + " - "; cin >> M;
	}
	ss();
	return make_tuple(N, M);
}

int** int_malloc(int N, int M) {
	int **matrix = (int**)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		matrix[i] = (int*)malloc(M * sizeof(int));
	return matrix;
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
	ss(); tab();
	cout << "Enter the number or 0 to close - ";
	cin >> *N;
}

void output_2D(int** A, int N, int M) {
	for (int i = 0; i < N; i++) {
		tab();
		for (int j = 0; j < M; j++) printf("%6i", A[i][j]);
		ss();
	}
	ss();
}

void matrix_output(double** A, int N, int M) {
	ss();
	for (int i = 0; i < N; i++) {
		tab();
		for (int j = 0; j < M; j++) {
			if (j < M - 1) printf("%8.2lf\t ", A[i][j]);
			else printf("= %8.2lf\t ", A[i][j]);
		}
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
        tab();
        for (int j = 1; j < M - 1; j++) printf("%i ", field[i][j]);
		ss();
	}
	ss();
}

void darvin_process(int **field, int **afterfield, int N, int M) {
	int lifes, cycles, tick = 0;
	ss(); tab();
	cout << "Enter the quantity of life cycles - "; cin >> cycles;
	while(cycles < 0){
		cout << "ERROR. Enter the positive quantity of life cycles - "; cin >> cycles;
	}
	ss();
	N--, M--;
	while (cycles) {
		int alive, deceased;
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
		tie(alive, deceased) = counter(field, N + 1, M + 1);
		printf("\tFIELD %3i \tALIVE:%3i | DECEASED:%3i", tick, alive, deceased);
		ss();
		tie(alive, deceased) = counter(afterfield, N + 1, M + 1);
		printf("\tAFTERFIELD %3i \tALIVE:%3i | DECEASED:%3i\n", tick, alive, deceased);
		ss();
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < M + 1; j++) {
				field[i][j] = afterfield[i][j];
			}
		}
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

tuple<int, int> counter(int** field, int N, int M) {
	int alive = 0, deceased = 0;
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			if (field[i][j] == 0) deceased += 1;
			else alive += 1;
		}
	}
	return make_tuple(alive, deceased);
}

void matrixes_creator(double **input_matrix, double **collin_matrix, double **zero_matrix, double **Gilbert_matrix, int N) {
	int zero_line = rand() % N, collin_line = N - 2, input;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//printf("Input to index %2i|%2i  - ", i, j); cin >> input;
			input_matrix[i][j] = double(rand() % 2800 - 1400);

			collin_matrix[i][j] = double(rand() % 2800 - 1400);
			if (i == collin_line + 1) collin_matrix[i][j] = collin_matrix[i - 1][j] * 2;

			zero_matrix[i][j] = double(rand() % 2800 - 1400);
			if (i == zero_line) zero_matrix[i][j] = 0.00;

			Gilbert_matrix[i][j] = 1.00 / double(i + j + 1);
		}
		//printf("Side - "); cin >> input;
		input_matrix[i][N]   = double(rand() % 2800 - 1400);
		collin_matrix[i][N]  = double(rand() % 2800 - 1400);
		zero_matrix[i][N]    = double(rand() % 2800 - 1400);
		Gilbert_matrix[i][N] = double(rand() % 2800 - 1400);
	}
}

void task_2(double **matrix, int N, string matrix_name) {
	double **tempo_copy = double_memory_allocator(N, N + 1);
	matrix_copy(matrix, tempo_copy, N);

	double *x_vect = new double[N];
	double deter = det(matrix, N);
	printf("\t%s\tdet = %lf\n", matrix_name.c_str(), deter);
	matrix_output(matrix, N, N + 1);
	if (deter != 0) {
		gauss_str_step(matrix, N);
		printf("\tGAUSSED %s\tdet = %lf\n", matrix_name.c_str(), diag_det(matrix, N));
		matrix_output(matrix, N, N + 1);
		printf("\tBACKSTEPPED %s\t\n", matrix_name.c_str());
		gauss_back_step(matrix, x_vect, N);
		matrix_output(matrix, N, N + 1);
		for (int i = 0; i < N; i++)
			printf("\tx%i = %2.2lf   ", i + 1, x_vect[i]);
		ss();
		ss();
		printf("\t%s WITH CHECK\t\n", matrix_name.c_str());
		checker(tempo_copy, x_vect, N);
		ss();
	}
	else printf("\tNO SOLUTION IN THIS CURSED MATRIX EXISTS\n");

	delete[] x_vect;
	for (int i = 0; i < N; i++)
	{
		delete[] tempo_copy[i];
		delete[] matrix[i];
	}
	delete[] tempo_copy;
	delete[] matrix;
	line();
}

bool curse_check(double **matrix, int N) {
	for (int i = 0; i < N; i++) {
		if (matrix[i][i] == 0)
			return false;
	}
	return true;
}

int matrix_size() {
    int N;
	tab();
    cout << "Enter the matrix size - "; cin >> N;
    while (N < 2) {
		cout << "ERROR. Enter the appropriate matrix size - "; cin >> N;
	}
	ss();
	return N;
}

void random_input(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = double(rand() % 2800 - 1400);
        }
    }
}

double det(double **matrix, int N, int col) {
	double deter = 0;
	if (N == 2) deter = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	if (N == 3)
	{
		deter = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[2][0] * matrix[0][1] * matrix[1][2]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[2][0] * matrix[1][1] * matrix[0][2] 
		- matrix[1][0] * matrix[0][1] * matrix[2][2] 
		- matrix[2][1] * matrix[1][2] * matrix[0][0];
	}
	if (N > 3) {
		double** minor_matrix = double_memory_allocator(N - 1, N - 1);
		for (int i = 0; i < N; i++) {
			for (int j = 1; j < N; j++) {
				for (int k = 0, p = 0; k < N; k++) {
					if (k != i) {
						minor_matrix[j - 1][p] = matrix[j][k];
						p++;
					}
				}
			}
			deter -= pow(-1, 2+i) * matrix[0][i] * det(minor_matrix, N - 1, i);
		}
		for (int i = 0; i < N - 1; i++) {
			delete[] minor_matrix[i];
		}
		delete[] minor_matrix;
	}
	return deter;
}

void gauss_str_step(double **matrix, int N) {
	//снять все комментарии для dev-режима(чтобы лучше понять, что тут происходит)
	double nullifier;
	bool cursed = false;
	for (int LEAD = 0; LEAD < N - 1; LEAD++) {
		for (int i = LEAD + 1; i < N; i++) {
			nullifier = matrix[i][LEAD] / matrix[LEAD][LEAD];
		    //cout << nullifier << endl;
			for (int j = LEAD; j < N + 1; j++) {
				//cout << " on i = " << i << " and " << "on j = " << j << ":   " << matrix[i][j] << " -= " << nullifier << " * " << matrix[LEAD][j] << endl;
				matrix[i][j] -= nullifier * matrix[LEAD][j];
			}
			/*
			ss();
			matrix_output(matrix, N, N + 1);
			ss();
			*/
		}
	}
}

void gauss_back_step(double **matrix, double *x_vect, int N) {
	x_vect[N - 1] = matrix[N - 1][N] / matrix[N - 1][N - 1];
	for (int i = N - 2; i >= 0; i--) {
		for (int j = i + 1; j < N; j++) {
			matrix[i][N] -= x_vect[j] * matrix[i][j];	
		}
		x_vect[i] = matrix[i][N] / matrix[i][i];
	}
}

double diag_det(double **matrix, int N) {
	double det = 1.0;
	for (int i = 0; i < N; i++) {
		det *= matrix[i][i];
	}
	return det;
}

void checker(double **matrix, double *x_vect, int N) {
	ss();
	double result, diff_med = 0, counter = 0, eps = 1.e-8;
	for (int i = 0; i < N; i++) {
		result = 0.0;
		tab();
		for (int j = 0; j <= N; j++) {
			if (j < N) {
				printf("%8.2lf\t ", matrix[i][j]);
				result += matrix[i][j] * x_vect[j];
			}
			else printf("= %8.2lf ", matrix[i][j]);
		}
		printf("|%8.2lf | diff = %8.15lf\n", result, abs(result - matrix[i][N]));
		diff_med += abs(result - matrix[i][N]);
		counter += 1;
	}
	printf("\n\tMEAN DIFF = %8.15lf ", diff_med /= counter);
	if (diff_med < eps) printf("ITS OK\n");
	else printf("NOT OK\n");
}

void matrix_copy(double **matrix_1, double **matrix_2, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N; j++) {
			matrix_2[i][j] = matrix_1[i][j];
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
    string champion = "SHOOTER 1", IsAre = " IS";
    for (int i = 1; i < N; i++) {
		if (results[i][0] == maxshot) champs++;
        if (results[i][0] > maxshot) {
			maxsum = results[i][1];
			IsAre = " IS";
            maxshot = results[i][0];
            champion = "SHOOTER " + to_string(i + 1);
            champs = 1;
        }
    }
    if (champs != 1) {
		champion = "";
		for (int i = 0; i < N; i++) {
            if (maxsum == results[i][1] && results[i][0] == maxshot) {
                IsAre = "S ARE:";
                champion += "SHOOTER " + to_string(i + 1) + " ";
            }
			if (maxsum < results[i][1] && results[i][0] == maxshot) {
				IsAre = " IS";
                maxsum = results[i][1];
                champion = "SHOOTER " + to_string(i + 1) + " ";
            }
        }
    }
    printf("\n\tOUR WINNER%s %s\n\n", IsAre.c_str(), champion.c_str());
}

void matrix_creator(int **matrix, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = rand() % 28 - 14;
		}
	}
}

void task_4(int **matrix, int N) {
	int *max = new int[3];
	int *min = new int[3];

	for (int i = 0; i < N / 2; i++) {
		for (int j = i + 1; j < N - i - 1; j++) {
			if (matrix[i][j] < 0 && matrix[i][j] > max[0]) {
				max[0] = matrix[i][j];
				max[1] = i;
				max[2] = j;
			}
		}
	}
	printf("\tMAX NEGATIVE ELEMENT: %i ON %i|%i\n", max[0], max[1], max[2]);

	for (int i = N / 2 + 1; i < N; i++) {
		for (int j = N - i; j < i; j++) {
			if (matrix[i][j] > -1 && matrix[i][j] < abs(min[0])) {
				min[0] = matrix[i][j];
				min[1] = i;
				min[2] = j;
			}
		}
	}
	printf("\tMIN POSITIVE ELEMENT: %i ON %i|%i\n", min[0], min[1], min[2]);
	int tempo = matrix[max[1]][max[2]];
	matrix[max[1]][max[2]] = matrix[min[1]][min[2]];
	matrix[min[1]][min[2]] = tempo;
	output_2D(matrix, N, N);
	delete[] max;
	delete[] min;
}

void random_numbers() {
	ofstream numbers;
	numbers.open("numbers.txt", ios::out);
	for (int i = 0; i <= 100000; i++) {
		numbers << rand() % 15 - 10 << endl;
	}
	numbers.close();
}

void matrix_x_number(int **matrix, int num, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			matrix[i][j] *= num;
		}
	}
}

int** matrix_sum_diff(int **matrix_1, int **matrix_2, int N, int M, bool sign) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (sign) matrix_1[i][j] += matrix_2[i][j];
			else matrix_1[i][j] -= matrix_2[i][j];
		}
	}
	return matrix_1;
}

int** matrix_product(int **matrix_1, int**matrix_2, int N1, int M1, int N2, int M2) {
	int **result = int_memory_allocator(N1, M2);
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < M2; j++) {
			result[i][j] = result_calc(matrix_1, matrix_2, M1, N2, i, j);
		}
	}
	return result;
}

void file_input(int **matrix, int N, int M, ifstream& numbers) {
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			numbers >> matrix[i][j];
		}
	}
}

int** transpon(int** matrix, int N, int M) {
	int **T_matrix = int_malloc(M, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			T_matrix[j][i] = matrix[i][j];
		}
	}
	return T_matrix;
}

int result_calc(int **matrix1, int **matrix2, int M1, int N2, int I, int J) {
	int res;
	for (int i = 0; i < M1; i++) {
		res = 0;
		for (int j = 0; j < N2; j++) {
			res += matrix1[I][i] * matrix2[j][J];
		}
	}
	return res;
}