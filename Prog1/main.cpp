#include <fstream> 
#include <iostream>
#include <time.h>
#include <iomanip>//для вывода красивого в файлики
using namespace std;
double func(double x) { 
	return -x+2*cos(x);
}
int main() {
	double a = 10.0;
	double b = 30.0;
	int N = 20;
	int M = 100;
	double* arr = new double[N];//массив x-ов  разбиения N случайных
	double* arr1 = new double[N];//массив y-ков построенный по предедущему массиву с помощью функции
	double* resz = new double[N];//массив знаменателей
	double* arr2 = new double[M];//массив x-ов  разбиения сетки M
	double* Ln = new double[M];
	double* G = new double[M];//угрики по точкам М
	srand(time(NULL));
	arr[0] = a; //точки рабиения N
	arr[N - 1] = b;

	double delta = 0.01 * ((b - a) / N);
	int i = 1;       //мы же уже первый и последний элементы приравняли к а и b генерируем число и смиотри расстояние со всеми имеющимися точками, если расстояние больше дельта то добавляем в массив если меньше то генерируем новое число
	int flag = 0;
	while (i < N - 1) {
		arr[i] = a + (b - a) * rand() / (float)RAND_MAX;
		flag = 0;
		for (int j = 0; j < i; j++) {
			if (fabs(arr[i] - arr[j]) < delta) {//геенерируем в ту же ячейку 
				flag = 1;
			}
		}
		if (flag == 0) {   // новое число генерируем в новую ячейку 
			i++;
		}
	}

	//просортируем пузырьком сгенерированные точки
	double t;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				t = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = t;
			}
	}


	for (int i = 0; i < N; i++) {//значения функции в случайных точках
		arr1[i] = func(arr[i]);
	}
	//зададим равномерную сетку
	for (int i = 0; i < M; i++) {
		arr2[i] = a + i * (b - a) / (M - 1);
	}

	for (int i = 0; i < M; i++) {//значения функции в точках равномерной сетки
		G[i] = func(arr2[i]);
	}

	//самая важная часть программы считаем многочлен Лагранжа
	for (int i = 0; i < N; i++) { //вычисляем массив знаменателей
		resz[i] = 1; 
		for (int j = 0; j < N; j++) {
			if (j != i) {
				resz[i] = resz[i] * (arr[i] - arr[j]); // то есть домножим то что получилось на новую скобку
			}
		}
	}

	for (int i = 0; i < M; i++) {//всего Ln  по М точкам
		Ln[i] = 0;
		for (int j = 0; j < N; j++) {//по сумме
			double proizv = 1.0; //переменная произведения числитель
			for (int k = 0; k < N; k++) {//по произведению 
				if (j != k)
					proizv *= (arr2[i] - arr[k]);
			}
			Ln[i] += arr1[j] * proizv / resz[j];
		}
	}

	//РАБОТА С ФАЙЛАМИ
	ofstream fout0;
	fout0.open("file0.txt");
	fout0 << a << "\t" << b;
	fout0.close();

	ofstream fout; //иксы рабиения N
	fout.open("file1.txt");
	for (int i = 0; i < N; i++) {
		fout << fixed;
		fout.precision(5);
		fout.setf(ios::right);
		fout.width(10);
		fout << arr[i] << "\n";
	}
	fout.close();

	ofstream massy;
	massy.open("file2.txt"); //функции у
	for (int i = 0; i < N; i++) {
		massy << fixed;
		massy.precision(5);
		massy.setf(ios::right);
		massy.width(10);
		massy << arr1[i] << endl;
	}
	massy.close();

	ofstream fout3;
	fout3.open("file3.txt"); //иксы разбиения M
	for (int i = 0; i < M; i++) {
		fout3 << fixed;
		fout3.precision(5);
		fout3.setf(ios::right);
		fout3.width(10);
		fout3 << arr2[i] << "\n";
	}
	fout3.close();

	ofstream foutLn; //интерполяционный многочлен
	foutLn.open("file4.txt");
	for (int i = 0; i < M; i++) {
		foutLn << fixed; //Пять цифр после запятой  эти две строчки
		foutLn.precision(5);
		foutLn.setf(ios::right);//выравнивание по правой стороне две строчки
		foutLn.width(10);
		foutLn << Ln[i] << "\n";
	}
	foutLn.close();

	ofstream fout4;
	fout4.open("file5.txt"); //угрики разбиения M
	for (int i = 0; i < M; i++) {
		fout4 << fixed;
		fout4.precision(5);
		fout4.setf(ios::right);
		fout4.width(10);
		fout4 << G[i] << "\n";
	}
	fout4.close();

	delete[] arr;
	delete[] arr1;
	delete[] arr2;
	delete[] resz;
	delete[] Ln;
	delete[] G;

	std::system("python PythonApplication1.py");

	return 0;

}

