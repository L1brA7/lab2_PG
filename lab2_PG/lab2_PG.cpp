#include <iostream>
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

//функции для задания 2

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
			int **field = memory_allocator(N, M);
			int **afterfield = memory_allocator(N, M);
			field_creator(field, N, M);
			darvin_process(field, afterfield, N, M);
			delete[] field, afterfield;
		}
		if (number == 2) {}
		if (number == 3) {
			int N, M; tie(N, M) = WH(number);
			int **results = memory_allocator(N, 2); //доска результатов, ширина всегда 2
			shots(results, N, M);
            tab_out(results, N);
            res_out(results, N);
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
	string arr_type;
	if (number == 1) arr_type = "field";
	if (number == 2) arr_type = "matrix";
	if (number == 3) arr_type = "scorboard";
	cout << "Enter the " + arr_type + "'s width - "; cin >> N;
	while (N < 0) {
		cout << "ERROR. Enter the positive " + arr_type + "'s width - ";
		cin >> N;
	}
	cout << "Enter the " + arr_type + "'s height - ";
	cin >> M;
	while (M < 0) {
		cout << "ERROR. Enter the positive " + arr_type + "'s height - ";
		cin >> M;
	}
	ss();
	return make_tuple(M, N); //необходимая подмена, не обращайте внимания
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
		ss();
	}
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
		cout << "field - " << tick << endl;
		field_out(field, N + 1, M + 1);
		cout << "afterfield - " << tick << endl;
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

void shots(int** results, int N, int M) {
	int maxshot, shotsum, shot;
	for (int i = 0; i < N; i++) {
		shotsum = maxshot = shot = rand() % 11;
		printf("\tShooter %2i: |%2i|", i + 1, shot);
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
        printf("\tShooter %2i:|maxshot - %2i|shotsum - %2i|", i + 1, results[i][0], results[i][1]);
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